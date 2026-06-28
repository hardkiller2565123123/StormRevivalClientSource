#include "FlashBridgeHooks.h"
#include "UniversalHookRegistry.h"
#include "UniversalHookAddresses.h"
#include "UniversalHookPatterns.h"
#include "../Core/SRLogger.h"
#include "../CustomUI/CustomOptionSystem.h"
#include <cstdint>
#include <string>

namespace StormRevival::OnlineMenu::Hooking::FlashBridgeHooks
{
    namespace
    {
        using FnInvokeWithArgs = void(__fastcall*)(std::uintptr_t, const char*, const char*, const char*, std::uintptr_t, std::uintptr_t, int);
        using FnInvokeNoArgs = void(__fastcall*)(std::uintptr_t, const char*, const char*, const char*);
        using FnInvokeReturn = void(__fastcall*)(std::uintptr_t, const char*, const char*, const char*, std::uintptr_t);
        using FnRegisterMovie = std::int64_t(__fastcall*)(std::uintptr_t*, const char*, int, int, int, int);
        using FnUnregisterMovie = void(__fastcall*)(std::uintptr_t*, const char*);

        FnInvokeWithArgs g_InvokeWithArgs = nullptr;
        FnInvokeNoArgs g_InvokeNoArgs = nullptr;
        FnInvokeReturn g_InvokeReturn = nullptr;
        FnRegisterMovie g_RegisterMovie = nullptr;
        FnUnregisterMovie g_UnregisterMovie = nullptr;

        void __fastcall DetourInvokeWithArgs(std::uintptr_t ui, const char* movie, const char* root, const char* functionName, std::uintptr_t a5, std::uintptr_t a6, int argc)
        {
            CustomUI::OnFlashInvoke(movie, root, functionName, argc);
            if (g_InvokeWithArgs)
                g_InvokeWithArgs(ui, movie, root, functionName, a5, a6, argc);
        }

        void __fastcall DetourInvokeNoArgs(std::uintptr_t ui, const char* movie, const char* root, const char* functionName)
        {
            CustomUI::OnFlashInvoke(movie, root, functionName, 0);
            if (g_InvokeNoArgs)
                g_InvokeNoArgs(ui, movie, root, functionName);
        }

        void __fastcall DetourInvokeReturn(std::uintptr_t ui, const char* movie, const char* root, const char* functionName, std::uintptr_t outValue)
        {
            CustomUI::OnFlashInvoke(movie, root, functionName, 0);
            if (g_InvokeReturn)
                g_InvokeReturn(ui, movie, root, functionName, outValue);
        }

        std::int64_t __fastcall DetourRegisterMovie(std::uintptr_t* self, const char* movieName, int a3, int a4, int a5, int a6)
        {
            CustomUI::OnFlashMovieRegistered(movieName);
            if (g_RegisterMovie)
                return g_RegisterMovie(self, movieName, a3, a4, a5, a6);
            return 0;
        }

        void __fastcall DetourUnregisterMovie(std::uintptr_t* self, const char* movieName)
        {
            Log::Info(std::string("[CustomUI] Movie unregistered: ") + (movieName ? movieName : "<null>"));
            if (g_UnregisterMovie)
                g_UnregisterMovie(self, movieName);
        }

        HookSpec g_specs[] =
        {
            { "Flash.InvokeWithArgs.sub_140607BA0", HookGroup::UI, Addresses::UI::InvokeWithArgs, reinterpret_cast<void*>(&DetourInvokeWithArgs), reinterpret_cast<void**>(&g_InvokeWithArgs), "ActionScript Invoke with arguments", Patterns::UI::InvokeWithArgs, 0 },
            { "Flash.InvokeNoArgs.sub_140607B5C", HookGroup::UI, Addresses::UI::InvokeNoArgs, reinterpret_cast<void*>(&DetourInvokeNoArgs), reinterpret_cast<void**>(&g_InvokeNoArgs), "ActionScript Invoke with no args", Patterns::UI::InvokeNoArgs, 0 },
            { "Flash.InvokeReturn.sub_140607B7C", HookGroup::UI, Addresses::UI::InvokeReturn, reinterpret_cast<void*>(&DetourInvokeReturn), reinterpret_cast<void**>(&g_InvokeReturn), "ActionScript Invoke returning value", Patterns::UI::InvokeReturn, 0 },
            { "Flash.RegisterMovie.sub_14060759C", HookGroup::UI, Addresses::UI::RegisterMovie, reinterpret_cast<void*>(&DetourRegisterMovie), reinterpret_cast<void**>(&g_RegisterMovie), "Flash movie registration", Patterns::UI::RegisterMovie, 0 },
            { "Flash.UnregisterMovie.sub_1406078CC", HookGroup::UI, Addresses::UI::UnregisterMovie, reinterpret_cast<void*>(&DetourUnregisterMovie), reinterpret_cast<void**>(&g_UnregisterMovie), "Flash movie unload", Patterns::UI::UnregisterMovie, 0 },
        };
    }

    void Install()
    {
        Log::Info("[FlashBridgeHooks] Installing Scaleform bridge instrumentation hooks.");
        InstallHooks(g_specs, static_cast<int>(sizeof(g_specs) / sizeof(g_specs[0])));
    }

    void Shutdown()
    {
        Log::Info("[FlashBridgeHooks] Shutdown requested.");
    }
}
