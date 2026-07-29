#include "StdInc.h"
#include "HookText.h"
#include "PopupManager.h"
#include "Logger.h"

#include <Windows.h>
#include <MinHook.h>

#include <cstdint>
#include <cstring>
#include <string>
#include <sstream>
#include <unordered_map>

namespace
{
    constexpr uintptr_t kScaleformCallRVA = 0x71F390;
    constexpr uintptr_t kStringAssignRVA = 0x0B1B00;
    constexpr uintptr_t kStringAppendRVA = 0x0B3830;
    constexpr uintptr_t kDialogSetMessageRVA = 0x764220;

    using ScaleformCall_t = void(__fastcall*)(
        int64_t a1,
        int64_t swfName,
        int64_t target,
        int64_t method,
        int64_t a5,
        int64_t args,
        unsigned int argCount);

    using StringAssign_t = uint64_t * (__fastcall*)(uint64_t* dst, const void* src, size_t len);
    using StringAppend_t = uint64_t * (__fastcall*)(uint64_t* dst, const void* src, size_t len);
    using DialogSetMessage_t = int64_t(__fastcall*)(int64_t dialog, const char* text, int localized);

    ScaleformCall_t oScaleformCall = nullptr;
    StringAssign_t oStringAssign = nullptr;
    StringAppend_t oStringAppend = nullptr;
    DialogSetMessage_t oDialogSetMessage = nullptr;

    uintptr_t g_Base = 0;
    uintptr_t g_ScaleformCallAddr = 0;
    uintptr_t g_StringAssignAddr = 0;
    uintptr_t g_StringAppendAddr = 0;
    uintptr_t g_DialogSetMessageAddr = 0;

    static const std::unordered_map<std::string, std::string> g_Replacements =
    {
        { "option_name_0010", "Options 123" },
        { "option_text_0510", "Options 123" },
        { "characterselect_062", "Start 123" },
        { "option_name_0840", "Options 123" },
        { "option_name_0850", "Options 123" },

        { "option_text_0638", "Button Swap 123" },
        { "option_text_0639", "Key Config 123" },
        { "MSG_KeyConfug", "Invalid Key 123" },

        { "MSG_Yes", "Yes 123" },
        { "MSG_No", "No 123" },
        { "MSG_Back", "Back 123" },
        { "MSG_Edit", "Edit 123" },

        { "networkmode_1146", "Weekly Challenge 123" },
        { "networkmode_154", "Network Search 123" },
        { "networkmode_038", "Network Error 123" },

        { "shop_079", "Shop 123" },
        { "sub_q_05_0056", "Shop Lineup 123" },
        { "sub_q_05_0057", "Shop Lineup Special 123" },

        { "network_agreement", "Revival Network Agreement" },
        { "network_agreement_message", "You are connecting to Storm Revival." },
        { "network_agreement_ok", "Accept Revival" },
        { "network_agreement_ng", "Decline Revival" },
    };

    bool IsReadableBytes(const void* p, size_t len)
    {
        if (!p || len == 0 || len > 512)
            return false;

        const char* s = static_cast<const char*>(p);

        for (size_t i = 0; i < len; ++i)
        {
            unsigned char c = static_cast<unsigned char>(s[i]);
            if (c == 0)
                break;
            if (c < 0x20 || c > 0x7E)
                return false;
        }

        return true;
    }

    bool IsReadableString(const char* s)
    {
        if (!s)
            return false;

        for (int i = 0; i < 512; ++i)
        {
            unsigned char c = static_cast<unsigned char>(s[i]);
            if (c == 0)
                return i > 0;
            if (c < 0x20 || c > 0x7E)
                return false;
        }

        return false;
    }

    std::string MakeString(const void* p, size_t len)
    {
        if (!IsReadableBytes(p, len))
            return {};
        return std::string(static_cast<const char*>(p), len);
    }

    std::string SafeString(const char* s)
    {
        return IsReadableString(s) ? std::string(s) : std::string();
    }

    const char* FindReplacementByString(const std::string& text)
    {
        if (text.empty())
            return nullptr;

        auto it = g_Replacements.find(text);
        return it != g_Replacements.end() ? it->second.c_str() : nullptr;
    }

    const char* FindReplacementBytes(const void* src, size_t len)
    {
        return FindReplacementByString(MakeString(src, len));
    }

    const char* FindReplacementCStr(const char* src)
    {
        return FindReplacementByString(SafeString(src));
    }

    bool Contains(const std::string& text, const char* needle)
    {
        return text.find(needle) != std::string::npos;
    }

    void PatchScaleformTextArg(int64_t args, unsigned int argCount, const char* text)
    {
        if (!args || !text || argCount < 1)
            return;

        *reinterpret_cast<int*>(args + 24) = 6;
        *reinterpret_cast<const char**>(args + 32) = text;
    }

    const char* GetScaleformReplacement(const std::string& swf, const std::string& method)
    {
        if (Contains(swf, "option_button/option_button.swf"))
        {
            if (method == "SetTopTabText")
                return "<icon txt_icon_eng_s />Options 123";
            if (method == "SetTitleText")
                return "Options 123";
            if (method == "SetBottomTabText")
                return "Options 123";
        }

        return nullptr;
    }

    void __fastcall hkScaleformCall(
        int64_t a1,
        int64_t swfName,
        int64_t target,
        int64_t method,
        int64_t a5,
        int64_t args,
        unsigned int argCount)
    {
        std::string swf = SafeString(reinterpret_cast<const char*>(swfName));
        std::string fn = SafeString(reinterpret_cast<const char*>(method));

        const char* replacement = GetScaleformReplacement(swf, fn);
        if (replacement)
        {
            Logger::Info("HookText Scaleform replace " + fn + " -> " + replacement);
            PatchScaleformTextArg(args, argCount, replacement);
        }

        if (oScaleformCall)
            oScaleformCall(a1, swfName, target, method, a5, args, argCount);
    }

    uint64_t* __fastcall hkStringAssign(uint64_t* dst, const void* src, size_t len)
    {
        const char* replacement = FindReplacementBytes(src, len);

        if (replacement)
        {
            std::string oldText = MakeString(src, len);
            Logger::Info("HookText StringAssign replace '" + oldText + "' -> '" + replacement + "'");

            return oStringAssign
                ? oStringAssign(dst, replacement, std::strlen(replacement))
                : dst;
        }

        return oStringAssign ? oStringAssign(dst, src, len) : dst;
    }

    uint64_t* __fastcall hkStringAppend(uint64_t* dst, const void* src, size_t len)
    {
        const char* replacement = FindReplacementBytes(src, len);

        if (replacement)
        {
            std::string oldText = MakeString(src, len);
            Logger::Info("HookText StringAppend replace '" + oldText + "' -> '" + replacement + "'");

            return oStringAppend
                ? oStringAppend(dst, replacement, std::strlen(replacement))
                : dst;
        }

        return oStringAppend ? oStringAppend(dst, src, len) : dst;
    }

    int64_t __fastcall hkDialogSetMessage(int64_t dialog, const char* text, int localized)
    {
        const char* replacement = FindReplacementCStr(text);

        if (replacement)
        {
            std::string oldText = SafeString(text);
            Logger::Info("HookText DialogSetMessage replace '" + oldText + "' -> '" + replacement + "'");

            return oDialogSetMessage
                ? oDialogSetMessage(dialog, replacement, 0)
                : 0;
        }

        return oDialogSetMessage ? oDialogSetMessage(dialog, text, localized) : 0;
    }

    bool InstallHook(uintptr_t addr, void* detour, void** original, const char* name)
    {
        MH_STATUS status = MH_CreateHook(reinterpret_cast<void*>(addr), detour, original);
        if (status != MH_OK)
        {
            Logger::Error(std::string(name) + " MH_CreateHook failed " + std::to_string(status));
            return false;
        }

        status = MH_EnableHook(reinterpret_cast<void*>(addr));
        if (status != MH_OK)
        {
            Logger::Error(std::string(name) + " MH_EnableHook failed " + std::to_string(status));
            return false;
        }

        Logger::Info(std::string(name) + " installed");
        return true;
    }

    void LogAddress(const char* name, uintptr_t addr, uintptr_t rva)
    {
        std::ostringstream ss;
        ss << std::hex << name << " addr=0x" << addr << " rva=0x" << rva;
        Logger::Info(ss.str());
    }
}

namespace HookText
{
    bool Install()
    {
        HMODULE exe = GetModuleHandleA(nullptr);
        if (!exe)
        {
            Logger::Error("HookText failed to locate exe");
            return false;
        }

        g_Base = reinterpret_cast<uintptr_t>(exe);

        g_ScaleformCallAddr = g_Base + kScaleformCallRVA;
        g_StringAssignAddr = g_Base + kStringAssignRVA;
        g_StringAppendAddr = g_Base + kStringAppendRVA;
        g_DialogSetMessageAddr = g_Base + kDialogSetMessageRVA;

        LogAddress("HookText ScaleformCall", g_ScaleformCallAddr, kScaleformCallRVA);
        LogAddress("HookText StringAssign", g_StringAssignAddr, kStringAssignRVA);
        LogAddress("HookText StringAppend", g_StringAppendAddr, kStringAppendRVA);
        LogAddress("HookText DialogSetMessage", g_DialogSetMessageAddr, kDialogSetMessageRVA);

        if (!InstallHook(g_ScaleformCallAddr, &hkScaleformCall, reinterpret_cast<void**>(&oScaleformCall), "HookText ScaleformCall"))
            return false;

        if (!InstallHook(g_StringAssignAddr, &hkStringAssign, reinterpret_cast<void**>(&oStringAssign), "HookText StringAssign"))
            return false;

        if (!InstallHook(g_StringAppendAddr, &hkStringAppend, reinterpret_cast<void**>(&oStringAppend), "HookText StringAppend"))
            return false;

        if (!InstallHook(g_DialogSetMessageAddr, &hkDialogSetMessage, reinterpret_cast<void**>(&oDialogSetMessage), "HookText DialogSetMessage"))
            return false;

        PopupManager::Init(g_Base);

        Logger::Info("HookText installed successfully");
        return true;
    }

    void Shutdown()
    {
        PopupManager::Shutdown();

        if (g_DialogSetMessageAddr)
            MH_DisableHook(reinterpret_cast<void*>(g_DialogSetMessageAddr));

        if (g_StringAppendAddr)
            MH_DisableHook(reinterpret_cast<void*>(g_StringAppendAddr));

        if (g_StringAssignAddr)
            MH_DisableHook(reinterpret_cast<void*>(g_StringAssignAddr));

        if (g_ScaleformCallAddr)
            MH_DisableHook(reinterpret_cast<void*>(g_ScaleformCallAddr));

        oDialogSetMessage = nullptr;
        oStringAppend = nullptr;
        oStringAssign = nullptr;
        oScaleformCall = nullptr;

        g_DialogSetMessageAddr = 0;
        g_StringAppendAddr = 0;
        g_StringAssignAddr = 0;
        g_ScaleformCallAddr = 0;
        g_Base = 0;

        Logger::Info("HookText shutdown");
    }
}