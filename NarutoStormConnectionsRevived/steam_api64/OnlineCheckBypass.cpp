#include "StdInc.h"
#include "OnlineCheckBypass.h"
#include "OnlineStorageBypass.h"
#include "NetworkStateBypass.h"
#include "Logger.h"
#include "HookManager.h"

namespace
{
    std::atomic<bool> g_Running{ false };
    HANDLE g_Thread = nullptr;
    std::string g_Report = "OnlineCheckBypass not initialized";

    constexpr uintptr_t kNSCDefaultImageBase = 0x140000000ull;
    constexpr uintptr_t kStateOnlineCheckA_VA = 0x141090FE0ull;
    constexpr uintptr_t kStateOnlineCheckB_VA = 0x141091140ull;

    // Diagnostic targets from current IDA map. These are logging hooks only.
    constexpr uintptr_t kNetTopInit_VA        = 0x14060A4A0ull;
    constexpr uintptr_t kNetTopUpdate_VA      = 0x14060A7A0ull;
    constexpr uintptr_t kNetTopPoll_VA        = 0x14060F720ull;
    constexpr uintptr_t kNetTopOnlinePath_VA  = 0x14060FA30ull;
    constexpr uintptr_t kNetTopOfflinePath_VA = 0x14060FD10ull;
    constexpr uintptr_t kGlobalFramework_VA   = 0x14219D7E0ull;
    constexpr uintptr_t kGlobalNetManager_VA  = 0x142188D20ull;
    constexpr uintptr_t kGlobalOnlineFlag_VA  = 0x14217AE58ull;

    // Online/FES profile gate readers found from the current IDA pass.
    // These are tiny bool getters used before the game constructs the online menu.
    constexpr uintptr_t kGateHasProfile_VA      = 0x140B53350ull; // profile +720 != 0
    constexpr uintptr_t kGateReadyProfile_VA    = 0x140B53240ull; // profile +888 != 0
    constexpr uintptr_t kGateFesInfoBusy_VA     = 0x140B531C0ull; // profile +832 != 0; must be false for ready path
    constexpr uintptr_t kGateSelectedValid_VA   = 0x140B51230ull; // selected profile/title valid
    constexpr uintptr_t kGateAltProfile_VA      = 0x140B53340ull; // profile +944 != 0 fallback

    // User-visible error dialog / online menu blocker.
    constexpr uintptr_t kShowNetworkError_VA    = 0x1408305A0ull;

    // NetBattleMainMenu lock/unlock helpers from the latest TXT.
    // sub_14079ED10 sets a1+224=1 and calls Flash netbattlemainmenu.SetLock.
    // We suppress that lock and call the unlock path when possible.
    constexpr uintptr_t kNetBattleSetLock_VA    = 0x14079ED10ull;
    constexpr uintptr_t kNetBattleSetUnlock_VA  = 0x14079F0C0ull;
    constexpr uintptr_t kNetBattleInitMenu_VA   = 0x140609F10ull;

    // Steam matchmaking pipeline found from the current IDA pass. Logging only.
    constexpr uintptr_t kAutomatchSearch_VA     = 0x1411173F0ull;
    constexpr uintptr_t kAutomatchSearchCb_VA   = 0x141116100ull;
    constexpr uintptr_t kAutomatchCreate_VA     = 0x141118C30ull;
    constexpr uintptr_t kAutomatchJoin_VA       = 0x141118DB0ull;
    constexpr uintptr_t kAutomatchCancel_VA     = 0x141117DD0ull;

    uintptr_t RvaFromVA(uintptr_t va);
    bool GetMainImage(unsigned char*& base, size_t& imageSize);

    using FnVoidState = void(__fastcall*)(__int64);
    using FnI64State = __int64(__fastcall*)(__int64);
    FnI64State g_OrigNetTopInit = nullptr;
    FnVoidState g_OrigNetTopUpdate = nullptr;
    FnI64State g_OrigNetTopPoll = nullptr;
    FnI64State g_OrigNetTopOnlinePath = nullptr;
    FnI64State g_OrigNetTopOfflinePath = nullptr;

    using FnNetMenuVoid = void(__fastcall*)(__int64);
    using FnNetMenuI64 = __int64(__fastcall*)(__int64);
    FnNetMenuI64 g_OrigNetBattleInitMenu = nullptr;
    FnNetMenuVoid g_OrigNetBattleSetLock = nullptr;
    FnNetMenuVoid g_OrigNetBattleSetUnlock = nullptr;
    std::atomic<bool> g_InUnlockCall{ false };

    using FnGateBool = __int64(__fastcall*)(__int64);
    using FnShowNetworkError = __int64(__fastcall*)(void*, const char*, unsigned int);
    using FnAutomatchSearch = __int64(__fastcall*)(__int64, __int64);
    using FnAutomatchSearchCb = __int64(__fastcall*)(__int64, unsigned int*, char);
    using FnAutomatchState = void(__fastcall*)(__int64, int);
    using FnAutomatchCancel = __int64(__fastcall*)(uint32_t*);

    FnGateBool g_OrigGateHasProfile = nullptr;
    FnGateBool g_OrigGateReadyProfile = nullptr;
    FnGateBool g_OrigGateFesInfoBusy = nullptr;
    FnGateBool g_OrigGateSelectedValid = nullptr;
    FnGateBool g_OrigGateAltProfile = nullptr;
    FnShowNetworkError g_OrigShowNetworkError = nullptr;
    FnAutomatchSearch g_OrigAutomatchSearch = nullptr;
    FnAutomatchSearchCb g_OrigAutomatchSearchCb = nullptr;
    FnAutomatchState g_OrigAutomatchCreate = nullptr;
    FnAutomatchState g_OrigAutomatchJoin = nullptr;
    FnAutomatchCancel g_OrigAutomatchCancel = nullptr;

    std::atomic<int> g_InstalledMenuTraceHooks{ 0 };
    std::atomic<uint32_t> g_LaunchForceTicks{ 0 };

    template <typename T>
    bool SafeRead(uintptr_t address, T& out)
    {
        __try
        {
            out = *reinterpret_cast<T*>(address);
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            memset(&out, 0, sizeof(out));
            return false;
        }
    }

    template <typename T>
    bool SafeWriteValue(uintptr_t address, const T& value)
    {
        __try
        {
            *reinterpret_cast<T*>(address) = value;
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

    uintptr_t MainVA(uintptr_t va)
    {
        unsigned char* base = nullptr;
        size_t imageSize = 0;
        if (!GetMainImage(base, imageSize))
            return 0;
        const uintptr_t rva = RvaFromVA(va);
        if (rva >= imageSize)
            return 0;
        return reinterpret_cast<uintptr_t>(base + rva);
    }

    uintptr_t ReadGlobalPtrVA(uintptr_t va)
    {
        uintptr_t slot = MainVA(va);
        if (!slot)
            return 0;
        uintptr_t value = 0;
        SafeRead(slot, value);
        return value;
    }

    uint32_t U32(uintptr_t p, ptrdiff_t off)
    {
        uint32_t v = 0;
        if (p)
            SafeRead(p + off, v);
        return v;
    }

    uintptr_t UPTR(uintptr_t p, ptrdiff_t off)
    {
        uintptr_t v = 0;
        if (p)
            SafeRead(p + off, v);
        return v;
    }

    std::string HexPtr(uintptr_t v)
    {
        std::ostringstream ss;
        ss << "0x" << std::hex << std::uppercase << v << std::dec;
        return ss.str();
    }

    struct MenuTraceSnapshot
    {
        uintptr_t state = 0;
        uint32_t s84 = 0, s100 = 0, s120 = 0, s212 = 0, s216 = 0, s220 = 0, s224 = 0;
        uint32_t s232 = 0, s236 = 0, s240 = 0, s244 = 0, s248 = 0, s252 = 0, s264 = 0;
        uint32_t s272 = 0, s276 = 0, s280 = 0, s288 = 0, s408 = 0;
        uintptr_t flash = 0, manager = 0, mgr1584384 = 0, mgr1584392 = 0;
        uintptr_t rootNetObj = 0, root720 = 0, root776 = 0, root832 = 0, root888 = 0, root944 = 0;
        uint32_t root964 = 0, gateHasProfile = 0, gateReadyPtr = 0, gateBusy = 0, gateOnlinePath = 0;
        uint32_t globalOnline88 = 0;
    };

    MenuTraceSnapshot MakeSnapshot(__int64 a1)
    {
        MenuTraceSnapshot t{};
        t.state = static_cast<uintptr_t>(a1);
        if (!a1)
            return t;
        uintptr_t s = static_cast<uintptr_t>(a1);
        t.s84 = U32(s, 84); t.s100 = U32(s, 100); t.s120 = U32(s, 120);
        t.s212 = U32(s, 212); t.s216 = U32(s, 216); t.s220 = U32(s, 220); t.s224 = U32(s, 224);
        t.s232 = U32(s, 232); t.s236 = U32(s, 236); t.s240 = U32(s, 240); t.s244 = U32(s, 244);
        t.s248 = U32(s, 248); t.s252 = U32(s, 252); t.s264 = U32(s, 264);
        t.s272 = U32(s, 272); t.s276 = U32(s, 276); t.s280 = U32(s, 280); t.s288 = U32(s, 288); t.s408 = U32(s, 408);
        t.flash = UPTR(s, 144);
        t.manager = ReadGlobalPtrVA(kGlobalNetManager_VA);
        if (t.manager)
        {
            t.mgr1584384 = UPTR(t.manager, 1584384);
            t.mgr1584392 = UPTR(t.manager, 1584392);
        }
        uintptr_t framework = ReadGlobalPtrVA(kGlobalFramework_VA);
        if (framework)
            t.rootNetObj = UPTR(framework, 472);
        if (t.rootNetObj)
        {
            t.root720 = UPTR(t.rootNetObj, 720);
            t.root776 = UPTR(t.rootNetObj, 776);
            t.root832 = UPTR(t.rootNetObj, 832);
            t.root888 = UPTR(t.rootNetObj, 888);
            t.root944 = UPTR(t.rootNetObj, 944);
            t.root964 = U32(t.rootNetObj, 964);
            t.gateHasProfile = t.root720 != 0;
            t.gateReadyPtr = t.root888 != 0;
            t.gateBusy = t.root832 != 0;
            t.gateOnlinePath = (t.gateHasProfile && t.gateReadyPtr && !t.gateBusy) ? 1u : 0u;
        }
        uintptr_t globalOnline = ReadGlobalPtrVA(kGlobalOnlineFlag_VA);
        if (globalOnline)
            t.globalOnline88 = U32(globalOnline, 88);
        return t;
    }

    void LogMenuSnapshot(const char* tag, __int64 a1, bool force = false)
    {
        static std::mutex m;
        static MenuTraceSnapshot last{};
        static ULONGLONG lastTick = 0;
        MenuTraceSnapshot t = MakeSnapshot(a1);
        ULONGLONG now = GetTickCount64();
        std::lock_guard<std::mutex> lock(m);
        bool changed = memcmp(&t, &last, sizeof(t)) != 0;
        if (!force && !changed && now - lastTick < 5000)
            return;
        last = t;
        lastTick = now;
        std::ostringstream ss;
        ss << "[NETMENU] " << tag
           << " state=" << HexPtr(t.state) << " ui=" << HexPtr(t.flash)
           << " s84=" << t.s84 << " s100=" << t.s100 << " s120=" << t.s120
           << " wait212=" << t.s212 << " f216=" << t.s216 << " f220=" << t.s220 << " lock224=" << t.s224
           << " has232=" << t.s232 << " ready236=" << t.s236
           << " ev240=" << t.s240 << " ev244=" << t.s244 << " ev248=" << t.s248 << " ev252=" << t.s252
           << " err264=" << t.s264 << " mode272=" << t.s272 << " sub276=" << t.s276
           << " cur280=" << t.s280 << " f288=" << t.s288 << " trans408=" << t.s408
           << " mgr=" << HexPtr(t.manager) << " backend1584384=" << HexPtr(t.mgr1584384)
           << " fes1584392=" << HexPtr(t.mgr1584392)
           << " rootNet=" << HexPtr(t.rootNetObj)
           << " p720=" << HexPtr(t.root720) << " p832=" << HexPtr(t.root832) << " p888=" << HexPtr(t.root888)
           << " p776=" << HexPtr(t.root776) << " p944=" << HexPtr(t.root944) << " region964=" << t.root964
           << " gate=" << t.gateOnlinePath << " globalOnline88=" << t.globalOnline88;
        Logger::Info(ss.str());
    }

    void ForceNetBattleMenuOpen(__int64 a1, const char* reason)
    {
        if (!a1)
            return;

        const uintptr_t s = static_cast<uintptr_t>(a1);
        SafeWriteValue<uint32_t>(s + 224, 0); // clear SetLock flag
        SafeWriteValue<uint32_t>(s + 232, 1); // has online profile
        SafeWriteValue<uint32_t>(s + 236, 1); // online ready
        SafeWriteValue<uint32_t>(s + 264, 0); // clear local error/blocked flag if present

        const uintptr_t manager = ReadGlobalPtrVA(kGlobalNetManager_VA);
        if (manager)
            SafeWriteValue<uint32_t>(manager + 1585296, 1); // global bit checked by sub_140609F10

        static ULONGLONG lastLog = 0;
        ULONGLONG now = GetTickCount64();
        if (now - lastLog > 1500)
        {
            lastLog = now;
            Logger::Info(std::string("[NETMENU-FORCE] online menu forced open reason=") + reason +
                         " state=" + HexPtr(s) + " manager=" + HexPtr(manager));
        }
    }

    void ForceLaunchOnlineState(const char* reason, bool verbose)
    {
        // Launch-level online bootstrap: keep the global online/profile objects in a ready shape
        // before the game reaches title/menu/ranking decisions. This does not remove any popup,
        // F2, or Steam feature; it only makes the existing offline Steam layer present as online-ready.
        const uintptr_t manager = ReadGlobalPtrVA(kGlobalNetManager_VA);
        if (manager)
        {
            SafeWriteValue<uint32_t>(manager + 1585296, 1);
            // These two nearby slots showed up in the trace snapshot as backend/fes objects.
            // Do not invent objects if they are already valid; only mirror manager as a safe non-null fallback.
            uintptr_t backend = UPTR(manager, 1584384);
            uintptr_t fes = UPTR(manager, 1584392);
            if (!backend) SafeWriteValue<uintptr_t>(manager + 1584384, manager);
            if (!fes) SafeWriteValue<uintptr_t>(manager + 1584392, manager);
        }

        const uintptr_t globalOnline = ReadGlobalPtrVA(kGlobalOnlineFlag_VA);
        if (globalOnline)
        {
            SafeWriteValue<uint32_t>(globalOnline + 88, 1);
            SafeWriteValue<uint32_t>(globalOnline + 92, 1);
            SafeWriteValue<uint32_t>(globalOnline + 96, 1);
        }

        const uintptr_t framework = ReadGlobalPtrVA(kGlobalFramework_VA);
        const uintptr_t root = framework ? UPTR(framework, 472) : 0;
        if (root)
        {
            const uintptr_t fallback = manager ? manager : root;
            if (!UPTR(root, 720)) SafeWriteValue<uintptr_t>(root + 720, fallback);
            if (!UPTR(root, 776)) SafeWriteValue<uintptr_t>(root + 776, fallback);
            SafeWriteValue<uintptr_t>(root + 832, 0);
            if (!UPTR(root, 888)) SafeWriteValue<uintptr_t>(root + 888, fallback);
            if (!UPTR(root, 944)) SafeWriteValue<uintptr_t>(root + 944, fallback);
            SafeWriteValue<uint32_t>(root + 964, 1);
        }

        if (verbose)
        {
            std::ostringstream ss;
            ss << "[ONLINE-LAUNCH-FORCE] reason=" << reason
               << " manager=" << HexPtr(manager)
               << " globalOnline=" << HexPtr(globalOnline)
               << " framework=" << HexPtr(framework)
               << " root=" << HexPtr(root);
            Logger::Info(ss.str());
        }
    }

    __int64 __fastcall HookNetBattleInitMenu(__int64 a1)
    {
        LogMenuSnapshot("sub_140609F10 NetBattleMainMenu INIT PRE", a1, true);
        ForceNetBattleMenuOpen(a1, "init-pre");
        __int64 r = g_OrigNetBattleInitMenu ? g_OrigNetBattleInitMenu(a1) : 0;
        ForceNetBattleMenuOpen(a1, "init-post");
        if (g_OrigNetBattleSetUnlock && !g_InUnlockCall.exchange(true))
        {
            g_OrigNetBattleSetUnlock(a1);
            g_InUnlockCall.store(false);
        }
        LogMenuSnapshot("sub_140609F10 NetBattleMainMenu INIT POST", a1, true);
        return r;
    }

    void __fastcall HookNetBattleSetLock(__int64 a1)
    {
        // This function is the repeated blocker from the TXT: it sets a1+224=1 and calls Flash SetLock.
        // Do not call original. Clear the lock and push the real unlock function instead.
        Logger::Info("[NETMENU-FORCE] suppressing sub_14079ED10 SetLock state=" + HexPtr(static_cast<uintptr_t>(a1)));
        ForceNetBattleMenuOpen(a1, "suppress-setlock");
        if (g_OrigNetBattleSetUnlock && !g_InUnlockCall.exchange(true))
        {
            g_OrigNetBattleSetUnlock(a1);
            g_InUnlockCall.store(false);
        }
    }

    void __fastcall HookNetBattleSetUnlock(__int64 a1)
    {
        if (g_OrigNetBattleSetUnlock)
            g_OrigNetBattleSetUnlock(a1);
        ForceNetBattleMenuOpen(a1, "setunlock-post");
    }

    __int64 __fastcall HookNetTopInit(__int64 a1)
    {
        LogMenuSnapshot("sub_14060A4A0 PRE", a1, true);
        ForceNetBattleMenuOpen(a1, "sub_14060A4A0-pre");
        __int64 r = g_OrigNetTopInit ? g_OrigNetTopInit(a1) : 0;
        ForceNetBattleMenuOpen(a1, "sub_14060A4A0-post");
        LogMenuSnapshot("sub_14060A4A0 POST", a1, true);
        return r;
    }
    void __fastcall HookNetTopUpdate(__int64 a1)
    {
        LogMenuSnapshot("sub_14060A7A0 PRE", a1, false);
        ForceNetBattleMenuOpen(a1, "sub_14060A7A0-pre");
        if (g_OrigNetTopUpdate) g_OrigNetTopUpdate(a1);
        ForceNetBattleMenuOpen(a1, "sub_14060A7A0-post");
        LogMenuSnapshot("sub_14060A7A0 POST", a1, false);
    }
    __int64 __fastcall HookNetTopPoll(__int64 a1)
    {
        LogMenuSnapshot("sub_14060F720 PRE", a1, true);
        ForceLaunchOnlineState("net-top-poll-pre", false);
        ForceNetBattleMenuOpen(a1, "sub_14060F720-pre");
        __int64 r = g_OrigNetTopPoll ? g_OrigNetTopPoll(a1) : 0;
        ForceLaunchOnlineState("net-top-poll-post", false);
        ForceNetBattleMenuOpen(a1, "sub_14060F720-post");
        LogMenuSnapshot("sub_14060F720 POST", a1, true);
        return r;
    }
    __int64 __fastcall HookNetTopOnlinePath(__int64 a1)
    {
        LogMenuSnapshot("sub_14060FA30 ONLINE_PATH PRE", a1, true);
        ForceLaunchOnlineState("online-path-pre", true);
        ForceNetBattleMenuOpen(a1, "sub_14060FA30-pre");
        __int64 r = g_OrigNetTopOnlinePath ? g_OrigNetTopOnlinePath(a1) : 0;
        ForceLaunchOnlineState("online-path-post", true);
        ForceNetBattleMenuOpen(a1, "sub_14060FA30-post");
        LogMenuSnapshot("sub_14060FA30 ONLINE_PATH POST", a1, true);
        return r;
    }
    __int64 __fastcall HookNetTopOfflinePath(__int64 a1)
    {
        LogMenuSnapshot("sub_14060FD10 OFFLINE_PATH PRE", a1, true);
        ForceLaunchOnlineState("offline-path-forced-online-pre", true);
        ForceNetBattleMenuOpen(a1, "sub_14060FD10-pre");
        __int64 r = g_OrigNetTopOfflinePath ? g_OrigNetTopOfflinePath(a1) : 0;
        ForceLaunchOnlineState("offline-path-forced-online-post", true);
        ForceNetBattleMenuOpen(a1, "sub_14060FD10-post");
        LogMenuSnapshot("sub_14060FD10 OFFLINE_PATH POST", a1, true);
        return r;
    }

    __int64 __fastcall HookGateHasProfile(__int64 a1)
    {
        __int64 orig = g_OrigGateHasProfile ? g_OrigGateHasProfile(a1) : 0;
        if (!orig)
            Logger::Info("[ONLINE-GATE] forcing sub_140B53350(profile +720) false->true profile=" + HexPtr(static_cast<uintptr_t>(a1)));
        return 1;
    }

    __int64 __fastcall HookGateReadyProfile(__int64 a1)
    {
        __int64 orig = g_OrigGateReadyProfile ? g_OrigGateReadyProfile(a1) : 0;
        if (!orig)
            Logger::Info("[ONLINE-GATE] forcing sub_140B53240(profile +888) false->true profile=" + HexPtr(static_cast<uintptr_t>(a1)));
        return 1;
    }

    __int64 __fastcall HookGateFesInfoBusy(__int64 a1)
    {
        __int64 orig = g_OrigGateFesInfoBusy ? g_OrigGateFesInfoBusy(a1) : 0;
        if (orig)
            Logger::Info("[ONLINE-GATE] forcing sub_140B531C0(profile +832 busy/info) true->false profile=" + HexPtr(static_cast<uintptr_t>(a1)));
        return 0;
    }

    __int64 __fastcall HookGateSelectedValid(__int64 a1)
    {
        __int64 orig = g_OrigGateSelectedValid ? g_OrigGateSelectedValid(a1) : 0;
        if (!orig)
            Logger::Info("[ONLINE-GATE] forcing sub_140B51230(selected profile/title valid) false->true profile=" + HexPtr(static_cast<uintptr_t>(a1)));
        return 1;
    }

    __int64 __fastcall HookGateAltProfile(__int64 a1)
    {
        __int64 orig = g_OrigGateAltProfile ? g_OrigGateAltProfile(a1) : 0;
        if (!orig)
            Logger::Info("[ONLINE-GATE] forcing sub_140B53340(profile +944 fallback) false->true profile=" + HexPtr(static_cast<uintptr_t>(a1)));
        return 1;
    }

    __int64 __fastcall HookShowNetworkError(void* manager, const char* messageId, unsigned int a3)
    {
        std::string id = messageId ? messageId : "<null>";
        Logger::Info("[ONLINE-ERROR] sub_1408305A0 msg=" + id + " a3=" + std::to_string(a3));
        if (id == "networkmode_452")
        {
            Logger::Info("[ONLINE-ERROR] suppressed networkmode_452 blocker");
            return 0;
        }
        return g_OrigShowNetworkError ? g_OrigShowNetworkError(manager, messageId, a3) : 0;
    }

    __int64 __fastcall HookAutomatchSearch(__int64 a1, __int64 a2)
    {
        Logger::Info("[AUTOMATCH] RequestLobbyList/search start ctx=" + HexPtr(static_cast<uintptr_t>(a1)) + " attrs=" + HexPtr(static_cast<uintptr_t>(a2)));
        __int64 r = g_OrigAutomatchSearch ? g_OrigAutomatchSearch(a1, a2) : 0;
        Logger::Info("[AUTOMATCH] RequestLobbyList/search returned " + std::to_string(r));
        return r;
    }

    __int64 __fastcall HookAutomatchSearchCb(__int64 a1, unsigned int* list, char failed)
    {
        unsigned int count = 0;
        if (list)
            SafeRead(reinterpret_cast<uintptr_t>(list), count);
        Logger::Info("[AUTOMATCH] LobbyMatchList callback ctx=" + HexPtr(static_cast<uintptr_t>(a1)) + " count=" + std::to_string(count) + " failed=" + std::to_string(static_cast<int>(failed)));
        return g_OrigAutomatchSearchCb ? g_OrigAutomatchSearchCb(a1, list, failed) : 0;
    }

    void __fastcall HookAutomatchCreate(__int64 a1, int state)
    {
        Logger::Info("[AUTOMATCH] CreateLobby state=" + std::to_string(state) + " ctx=" + HexPtr(static_cast<uintptr_t>(a1)));
        if (g_OrigAutomatchCreate) g_OrigAutomatchCreate(a1, state);
    }

    void __fastcall HookAutomatchJoin(__int64 a1, int state)
    {
        Logger::Info("[AUTOMATCH] JoinLobby state=" + std::to_string(state) + " ctx=" + HexPtr(static_cast<uintptr_t>(a1)));
        if (g_OrigAutomatchJoin) g_OrigAutomatchJoin(a1, state);
    }

    __int64 __fastcall HookAutomatchCancel(uint32_t* a1)
    {
        Logger::Info("[AUTOMATCH] Cancel/cleanup ctx=" + HexPtr(reinterpret_cast<uintptr_t>(a1)));
        return g_OrigAutomatchCancel ? g_OrigAutomatchCancel(a1) : 0;
    }

    bool InstallTraceHook(const char* name, uintptr_t va, void* detour, void** original)
    {
        void* target = reinterpret_cast<void*>(MainVA(va));
        if (!target)
        {
            Logger::Info(std::string("[NETMENU] hook target missing ") + name);
            return false;
        }
        MH_STATUS c = MH_CreateHook(target, detour, original);
        if (c != MH_OK && c != MH_ERROR_ALREADY_CREATED)
        {
            Logger::Error(std::string("[NETMENU] MH_CreateHook failed ") + name + " status=" + std::to_string(c));
            return false;
        }
        MH_STATUS e = MH_EnableHook(target);
        if (e != MH_OK && e != MH_ERROR_ENABLED)
        {
            Logger::Error(std::string("[NETMENU] MH_EnableHook failed ") + name + " status=" + std::to_string(e));
            return false;
        }
        Logger::Info(std::string("[NETMENU] hook enabled ") + name);
        return true;
    }

    int InstallMenuTraceHooks()
    {
        int expected = 0;
        if (!g_InstalledMenuTraceHooks.compare_exchange_strong(expected, -1))
            return g_InstalledMenuTraceHooks.load() > 0 ? g_InstalledMenuTraceHooks.load() : 0;
        int ok = 0;
        ok += InstallTraceHook("sub_140609F10 NetBattleMainMenuInit", kNetBattleInitMenu_VA, reinterpret_cast<void*>(&HookNetBattleInitMenu), reinterpret_cast<void**>(&g_OrigNetBattleInitMenu)) ? 1 : 0;
        ok += InstallTraceHook("sub_14079ED10 SetLock SUPPRESS", kNetBattleSetLock_VA, reinterpret_cast<void*>(&HookNetBattleSetLock), reinterpret_cast<void**>(&g_OrigNetBattleSetLock)) ? 1 : 0;
        ok += InstallTraceHook("sub_14079F0C0 SetUnlock", kNetBattleSetUnlock_VA, reinterpret_cast<void*>(&HookNetBattleSetUnlock), reinterpret_cast<void**>(&g_OrigNetBattleSetUnlock)) ? 1 : 0;
        ok += InstallTraceHook("sub_14060A4A0", kNetTopInit_VA, reinterpret_cast<void*>(&HookNetTopInit), reinterpret_cast<void**>(&g_OrigNetTopInit)) ? 1 : 0;
        ok += InstallTraceHook("sub_14060A7A0", kNetTopUpdate_VA, reinterpret_cast<void*>(&HookNetTopUpdate), reinterpret_cast<void**>(&g_OrigNetTopUpdate)) ? 1 : 0;
        ok += InstallTraceHook("sub_14060F720", kNetTopPoll_VA, reinterpret_cast<void*>(&HookNetTopPoll), reinterpret_cast<void**>(&g_OrigNetTopPoll)) ? 1 : 0;
        ok += InstallTraceHook("sub_14060FA30", kNetTopOnlinePath_VA, reinterpret_cast<void*>(&HookNetTopOnlinePath), reinterpret_cast<void**>(&g_OrigNetTopOnlinePath)) ? 1 : 0;
        ok += InstallTraceHook("sub_14060FD10", kNetTopOfflinePath_VA, reinterpret_cast<void*>(&HookNetTopOfflinePath), reinterpret_cast<void**>(&g_OrigNetTopOfflinePath)) ? 1 : 0;

        ok += InstallTraceHook("sub_140B53350 GateHasProfile", kGateHasProfile_VA, reinterpret_cast<void*>(&HookGateHasProfile), reinterpret_cast<void**>(&g_OrigGateHasProfile)) ? 1 : 0;
        ok += InstallTraceHook("sub_140B53240 GateReadyProfile", kGateReadyProfile_VA, reinterpret_cast<void*>(&HookGateReadyProfile), reinterpret_cast<void**>(&g_OrigGateReadyProfile)) ? 1 : 0;
        ok += InstallTraceHook("sub_140B531C0 GateFesInfoBusy", kGateFesInfoBusy_VA, reinterpret_cast<void*>(&HookGateFesInfoBusy), reinterpret_cast<void**>(&g_OrigGateFesInfoBusy)) ? 1 : 0;
        ok += InstallTraceHook("sub_140B51230 GateSelectedValid", kGateSelectedValid_VA, reinterpret_cast<void*>(&HookGateSelectedValid), reinterpret_cast<void**>(&g_OrigGateSelectedValid)) ? 1 : 0;
        ok += InstallTraceHook("sub_140B53340 GateAltProfile", kGateAltProfile_VA, reinterpret_cast<void*>(&HookGateAltProfile), reinterpret_cast<void**>(&g_OrigGateAltProfile)) ? 1 : 0;
        ok += InstallTraceHook("sub_1408305A0 ShowNetworkError", kShowNetworkError_VA, reinterpret_cast<void*>(&HookShowNetworkError), reinterpret_cast<void**>(&g_OrigShowNetworkError)) ? 1 : 0;

        ok += InstallTraceHook("sub_1411173F0 AutomatchSearch", kAutomatchSearch_VA, reinterpret_cast<void*>(&HookAutomatchSearch), reinterpret_cast<void**>(&g_OrigAutomatchSearch)) ? 1 : 0;
        ok += InstallTraceHook("sub_141116100 AutomatchSearchCb", kAutomatchSearchCb_VA, reinterpret_cast<void*>(&HookAutomatchSearchCb), reinterpret_cast<void**>(&g_OrigAutomatchSearchCb)) ? 1 : 0;
        ok += InstallTraceHook("sub_141118C30 AutomatchCreate", kAutomatchCreate_VA, reinterpret_cast<void*>(&HookAutomatchCreate), reinterpret_cast<void**>(&g_OrigAutomatchCreate)) ? 1 : 0;
        ok += InstallTraceHook("sub_141118DB0 AutomatchJoin", kAutomatchJoin_VA, reinterpret_cast<void*>(&HookAutomatchJoin), reinterpret_cast<void**>(&g_OrigAutomatchJoin)) ? 1 : 0;
        ok += InstallTraceHook("sub_141117DD0 AutomatchCancel", kAutomatchCancel_VA, reinterpret_cast<void*>(&HookAutomatchCancel), reinterpret_cast<void**>(&g_OrigAutomatchCancel)) ? 1 : 0;

        g_InstalledMenuTraceHooks.store(ok);
        return ok;
    }


    uintptr_t RvaFromVA(uintptr_t va)
    {
        return va - kNSCDefaultImageBase;
    }

    bool GetMainImage(unsigned char*& base, size_t& imageSize)
    {
        HMODULE module = GetModuleHandleW(nullptr);
        if (!module)
            return false;

        base = reinterpret_cast<unsigned char*>(module);
        auto* dos = reinterpret_cast<PIMAGE_DOS_HEADER>(base);
        if (dos->e_magic != IMAGE_DOS_SIGNATURE)
            return false;

        auto* nt = reinterpret_cast<PIMAGE_NT_HEADERS>(base + dos->e_lfanew);
        if (nt->Signature != IMAGE_NT_SIGNATURE)
            return false;

        imageSize = static_cast<size_t>(nt->OptionalHeader.SizeOfImage);
        return true;
    }

    bool WriteMemory(void* address, const void* data, size_t size)
    {
        if (!address || !data || size == 0)
            return false;

        DWORD oldProtect = 0;
        if (!VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &oldProtect))
            return false;

        memcpy(address, data, size);
        FlushInstructionCache(GetCurrentProcess(), address, size);

        DWORD ignored = 0;
        VirtualProtect(address, size, oldProtect, &ignored);
        return true;
    }

    bool PatchFunctionReturnInt(uintptr_t va, int value)
    {
        unsigned char* base = nullptr;
        size_t imageSize = 0;
        if (!GetMainImage(base, imageSize))
            return false;

        const uintptr_t rva = RvaFromVA(va);
        if (rva + 16 >= imageSize)
            return false;

        unsigned char* target = base + rva;

        // x64: mov eax, imm32 ; ret ; nop...
        // Works for bool/int state handlers and is safe for x64 calling convention.
        unsigned char patch[8] = { 0xB8, 0, 0, 0, 0, 0xC3, 0x90, 0x90 };
        memcpy(&patch[1], &value, sizeof(value));
        return WriteMemory(target, patch, sizeof(patch));
    }

    bool PatchMainModuleString(const char* from, const char* to)
    {
        if (!from || !to)
            return false;

        const size_t fromLen = strlen(from);
        const size_t toLen = strlen(to);
        if (fromLen == 0 || toLen > fromLen)
            return false;

        unsigned char* base = nullptr;
        size_t imageSize = 0;
        if (!GetMainImage(base, imageSize))
            return false;

        bool patched = false;
        for (size_t offset = 0; offset < imageSize;)
        {
            MEMORY_BASIC_INFORMATION mbi{};
            if (!VirtualQuery(base + offset, &mbi, sizeof(mbi)))
                break;

            auto* regionBase = static_cast<unsigned char*>(mbi.BaseAddress);
            const size_t regionSize = static_cast<size_t>(mbi.RegionSize);
            const bool readable = mbi.State == MEM_COMMIT && !(mbi.Protect & PAGE_NOACCESS) && !(mbi.Protect & PAGE_GUARD);

            if (readable)
            {
                for (size_t i = 0; i + fromLen <= regionSize; ++i)
                {
                    unsigned char* p = regionBase + i;
                    if (memcmp(p, from, fromLen) != 0)
                        continue;

                    DWORD oldProtect = 0;
                    if (!VirtualProtect(p, fromLen, PAGE_EXECUTE_READWRITE, &oldProtect))
                        continue;

                    memcpy(p, to, toLen);
                    if (toLen < fromLen)
                        memset(p + toLen, 0x20, fromLen - toLen);
                    FlushInstructionCache(GetCurrentProcess(), p, fromLen);
                    DWORD ignored = 0;
                    VirtualProtect(p, fromLen, oldProtect, &ignored);
                    patched = true;
                }
            }

            offset = static_cast<size_t>((regionBase + regionSize) - base);
        }

        return patched;
    }

    DWORD WINAPI WatchThread(LPVOID)
    {
        Logger::Info("OnlineCheckBypass watchdog started");

        while (g_Running.load())
        {
            const uint32_t tick = ++g_LaunchForceTicks;
            ForceLaunchOnlineState(tick <= 600 ? "startup-watchdog" : "steady-watchdog", tick == 1 || tick == 10 || tick == 50 || tick == 100 || tick == 300 || tick == 600);
            OnlineCheckBypass::ForceConnectedState();
            OnlineStorageBypass::Tick();
            NetworkStateBypass::Tick();
            Sleep(tick <= 600 ? 100 : 1000);
        }

        Logger::Info("OnlineCheckBypass watchdog stopped");
        return 0;
    }
}

bool OnlineCheckBypass::Init()
{
    if (g_Running.exchange(true))
        return true;

    int stringPatches = 0;
    stringPatches += PatchMainModuleString("ONLINE_ERROR", "ONLINE_CHECK") ? 1 : 0;
    stringPatches += PatchMainModuleString("OnlineError", "OnlineCheck") ? 1 : 0;
    stringPatches += PatchMainModuleString("NetError", "NetOpen ") ? 1 : 0;
    stringPatches += PatchMainModuleString("DISCONNECT_CHECK", "ONLINE_CHECK....") ? 1 : 0;
    stringPatches += PatchMainModuleString("DISCONNECT_PENALTY_WARNING", "ONLINE_CHECK................") ? 1 : 0;
    stringPatches += PatchMainModuleString("LOGINBONUS_CHECK", "ONLINE_CHECK....") ? 1 : 0;
    stringPatches += PatchMainModuleString("PLAYERGUIDE_CHECK", "ONLINE_CHECK.....") ? 1 : 0;
    stringPatches += PatchMainModuleString("IsDisconnected()", "IsConnectedOK() ") ? 1 : 0;
    stringPatches += PatchMainModuleString("IsDisconnectedFix()", "IsConnectedFixOK() ") ? 1 : 0;

    // v21 diagnostic change: do not hardpatch sub_141091140 anymore.
    // IDA confirmed it is ccNetOnlineCheck::Start(), not a bool getter.
    const bool onlineCheckA = false;
    const bool onlineCheckB = false;

    // TXT-confirmed menu gates. Hardpatch these too so direct calls and inlined-ish callers
    // do not depend on MinHook timing. 53350/53240 must be TRUE; 531C0 must be FALSE.
    const bool gateHasProfilePatch = PatchFunctionReturnInt(kGateHasProfile_VA, 1);
    const bool gateReadyPatch = PatchFunctionReturnInt(kGateReadyProfile_VA, 1);
    const bool gateBusyPatch = PatchFunctionReturnInt(kGateFesInfoBusy_VA, 0);
    const bool gateSelectedPatch = PatchFunctionReturnInt(kGateSelectedValid_VA, 1);
    const bool gateAltPatch = PatchFunctionReturnInt(kGateAltProfile_VA, 1);

    OnlineStorageBypass::Init();
    NetworkStateBypass::Init();
    ForceLaunchOnlineState("init-before-hooks", true);
    const int menuTraceHooks = InstallMenuTraceHooks();
    ForceLaunchOnlineState("init-after-hooks", true);
    ForceConnectedState();

    std::ostringstream ss;
    ss << "OnlineCheckBypass v30 LAUNCH online-force + online-menu gate + automatch trace enabled, string patches=" << stringPatches
       << " hardpatch_sub_141090FE0=" << (onlineCheckA ? "patched" : "disabled")
       << " hardpatch_sub_141091140=" << (onlineCheckB ? "patched" : "disabled")
       << " hardpatch_gates=" << gateHasProfilePatch << "/" << gateReadyPatch << "/" << gateBusyPatch << "/" << gateSelectedPatch << "/" << gateAltPatch
       << " netMenuTraceHooks=" << menuTraceHooks
       << "; storage=" << OnlineStorageBypass::Report()
       << "; networkState=" << NetworkStateBypass::Report();
    g_Report = ss.str();
    Logger::Info(g_Report);

    g_Thread = CreateThread(nullptr, 0, WatchThread, nullptr, 0, nullptr);
    return true;
}

void OnlineCheckBypass::RevalidateSignatures()
{
    ForceConnectedState();
}

void OnlineCheckBypass::ForceConnectedState()
{
    ForceLaunchOnlineState("ForceConnectedState", false);
    PatchMainModuleString("ONLINE_ERROR", "ONLINE_CHECK");
    PatchMainModuleString("OnlineError", "OnlineCheck");
    PatchMainModuleString("NetError", "NetOpen ");

    // Keep the actual runtime state warm too. This does not remove any feature; it only
    // prevents the game from seeing online profile state as missing while entering the
    // network menu. These offsets came from the TXT/log reverse map already in this build.
    const uintptr_t manager = ReadGlobalPtrVA(kGlobalNetManager_VA);
    if (manager)
        SafeWriteValue<uint32_t>(manager + 1585296, 1);

    const uintptr_t framework = ReadGlobalPtrVA(kGlobalFramework_VA);
    const uintptr_t root = framework ? UPTR(framework, 472) : 0;
    if (root)
    {
        // Make the three gate getters agree with the hardpatches: has profile, ready, not busy.
        uintptr_t fallback = root;
        if (!UPTR(root, 720)) SafeWriteValue<uintptr_t>(root + 720, fallback);
        if (!UPTR(root, 888)) SafeWriteValue<uintptr_t>(root + 888, fallback);
        SafeWriteValue<uintptr_t>(root + 832, 0);
    }
}

const char* OnlineCheckBypass::SignatureReport()
{
    return g_Report.c_str();
}

void OnlineCheckBypass::Shutdown()
{
    if (!g_Running.exchange(false))
        return;

    if (g_Thread)
    {
        WaitForSingleObject(g_Thread, 1500);
        CloseHandle(g_Thread);
        g_Thread = nullptr;
    }

    NetworkStateBypass::Shutdown();
    OnlineStorageBypass::Shutdown();
}
