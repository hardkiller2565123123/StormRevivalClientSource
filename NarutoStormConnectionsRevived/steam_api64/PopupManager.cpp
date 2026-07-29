#include "StdInc.h"
#include "PopupManager.h"
#include "PopupInternals.h"
#include "Logger.h"

#include <Windows.h>
#include <atomic>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

namespace
{
    std::atomic<bool> g_Running{ false };
    std::atomic<unsigned int> g_RequestCounter{ 0 };

    CRITICAL_SECTION g_DialogLock{};
    bool g_LockReady = false;

    struct PopupEntry
    {
        unsigned int id = 0;
        int64_t dialog = 0;
        bool closing = false;
        std::string windowName;
    };

    std::vector<PopupEntry> g_ActivePopups;

    struct ScopedLock
    {
        ScopedLock() { if (g_LockReady) EnterCriticalSection(&g_DialogLock); }
        ~ScopedLock() { if (g_LockReady) LeaveCriticalSection(&g_DialogLock); }
    };

    bool CloseInputPressed()
    {
        return
            (GetAsyncKeyState(VK_LBUTTON) & 1) ||
            (GetAsyncKeyState(VK_RBUTTON) & 1) ||
            (GetAsyncKeyState(VK_RETURN) & 1) ||
            (GetAsyncKeyState(VK_ESCAPE) & 1) ||
            (GetAsyncKeyState(VK_BACK) & 1) ||
            (GetAsyncKeyState(VK_SPACE) & 1) ||
            (GetAsyncKeyState('E') & 1);
    }

    void FlushCloseInput()
    {
        GetAsyncKeyState(VK_LBUTTON);
        GetAsyncKeyState(VK_RBUTTON);
        GetAsyncKeyState(VK_RETURN);
        GetAsyncKeyState(VK_ESCAPE);
        GetAsyncKeyState(VK_BACK);
        GetAsyncKeyState(VK_SPACE);
        GetAsyncKeyState('E');
    }

    std::string UniqueWindowName(const char* baseName, unsigned int id)
    {
        std::ostringstream ss;
        if (baseName && baseName[0])
            ss << baseName;
        else
            ss << "StormRevivalPopup";
        ss << "_" << id;
        return ss.str();
    }

    std::string BuildWelcomeText(int secondsLeft)
    {
        std::ostringstream ss;
        ss << "Welcome to Naruto Storm Revival API\n\n"
           << "GitHub:\n"
           << "https://github.com/hardkiller2565123123\n\n"
           << "Closing in " << secondsLeft << " seconds.";
        return ss.str();
    }

    std::string BuildCustomText(const PopupTypes::CustomPopupConfig& cfg, int secondsLeft)
    {
        std::ostringstream ss;
        if (cfg.titleText && cfg.titleText[0])
            ss << cfg.titleText << "\n\n";
        if (cfg.bodyText && cfg.bodyText[0])
            ss << cfg.bodyText << "\n\n";
        ss << "Popup id: " << g_RequestCounter.load() << "\n";
        ss << "Closing in " << secondsLeft << " seconds.";
        return ss.str();
    }

    PopupEntry* FindPopupLocked(unsigned int id)
    {
        for (auto& popup : g_ActivePopups)
        {
            if (popup.id == id)
                return &popup;
        }
        return nullptr;
    }

    bool PopupExists(unsigned int id)
    {
        ScopedLock lock;
        PopupEntry* popup = FindPopupLocked(id);
        return popup && popup->dialog && !popup->closing;
    }

    bool CreatePopup(unsigned int id, const std::string& windowName, PopupTypes::PopupKind kind)
    {
        ScopedLock lock;

        int64_t dialog = PopupInternals::CreateBasicDialog(windowName.c_str(), kind);
        if (!dialog)
            return false;

        PopupEntry entry{};
        entry.id = id;
        entry.dialog = dialog;
        entry.closing = false;
        entry.windowName = windowName;
        g_ActivePopups.push_back(entry);
        return true;
    }

    void SetTextOnPopup(unsigned int id, const std::string& text, bool localized)
    {
        ScopedLock lock;
        PopupEntry* popup = FindPopupLocked(id);
        if (popup && popup->dialog && !popup->closing)
            PopupInternals::SetDialogText(popup->dialog, text.c_str(), localized);
    }

    void OpenPopup(unsigned int id, bool useFade, const PopupTypes::FadeRgb& color, int fadeMs)
    {
        ScopedLock lock;
        PopupEntry* popup = FindPopupLocked(id);
        if (!popup || !popup->dialog || popup->closing)
            return;
        if (useFade)
            PopupInternals::StartFade(popup->dialog, color, fadeMs);
        PopupInternals::OpenDialog(popup->dialog);
        PopupInternals::SetDialogVisible(popup->dialog, true);
    }

    void ClosePopup(unsigned int id, const char* reason)
    {
        int64_t dialogToClose = 0;
        std::string windowName;
        {
            ScopedLock lock;
            PopupEntry* popup = FindPopupLocked(id);
            if (!popup || !popup->dialog || popup->closing)
                return;
            popup->closing = true;
            dialogToClose = popup->dialog;
            windowName = popup->windowName;
            popup->dialog = 0;
        }

        Logger::Info(std::string("PopupManager: closing reason=") + reason +
                     " id=" + std::to_string(id) +
                     " window=" + windowName);
        PopupInternals::CloseDialog(dialogToClose);

        {
            ScopedLock lock;
            g_ActivePopups.erase(
                std::remove_if(g_ActivePopups.begin(), g_ActivePopups.end(),
                    [id](const PopupEntry& popup) { return popup.id == id; }),
                g_ActivePopups.end());
        }
    }

    void CloseAll(const char* reason)
    {
        std::vector<unsigned int> ids;
        {
            ScopedLock lock;
            for (const auto& popup : g_ActivePopups)
            {
                if (popup.dialog && !popup.closing)
                    ids.push_back(popup.id);
            }
        }

        for (unsigned int id : ids)
            ClosePopup(id, reason);
    }

    template <typename ConfigT, typename TextBuilderT>
    DWORD RunTimedPopup(ConfigT cfg, const char* baseWindowName, const char* kindName, TextBuilderT buildText)
    {
        Sleep(cfg.delayMs);
        if (!g_Running)
            return 0;

        const unsigned int requestId = ++g_RequestCounter;
        const std::string windowName = UniqueWindowName(baseWindowName, requestId);

        if (!CreatePopup(requestId, windowName, PopupTypes::PopupKind::Normal))
        {
            Logger::Error(std::string("PopupManager: failed to create ") + kindName +
                          " id=" + std::to_string(requestId) +
                          " window=" + windowName);
            return 0;
        }

        int initialSeconds = cfg.durationMs / 1000;
        if (initialSeconds <= 0)
            initialSeconds = 1;

        SetTextOnPopup(requestId, buildText(initialSeconds), cfg.localizeText);
        OpenPopup(requestId, cfg.useFade, cfg.fadeColor, cfg.fadeDurationMs);
        FlushCloseInput();

        Logger::Info(std::string("PopupManager: opened ") + kindName +
                     " id=" + std::to_string(requestId) +
                     " window=" + windowName);

        DWORD start = GetTickCount();
        int lastSecond = initialSeconds;

        while (g_Running && PopupExists(requestId))
        {
            DWORD elapsed = GetTickCount() - start;
            int secondsLeft = (cfg.durationMs - static_cast<int>(elapsed) + 999) / 1000;
            if (secondsLeft < 0)
                secondsLeft = 0;

            if (secondsLeft != lastSecond)
            {
                lastSecond = secondsLeft;
                SetTextOnPopup(requestId, buildText(secondsLeft), cfg.localizeText);
            }

            if (cfg.allowInputClose && elapsed > 750 && CloseInputPressed())
            {
                ClosePopup(requestId, "input");
                break;
            }

            if (elapsed >= static_cast<DWORD>(cfg.durationMs))
            {
                ClosePopup(requestId, "timer");
                break;
            }

            Sleep(16);
        }

        if (PopupExists(requestId))
            ClosePopup(requestId, "finished");
        return 0;
    }

    DWORD WINAPI TimedWelcomeThread(LPVOID param)
    {
        PopupTypes::TimedPopupConfig cfg = *reinterpret_cast<PopupTypes::TimedPopupConfig*>(param);
        delete reinterpret_cast<PopupTypes::TimedPopupConfig*>(param);
        return RunTimedPopup(cfg, "StormRevivalApiWelcome", "timed welcome", [](int sec) { return BuildWelcomeText(sec); });
    }

    DWORD WINAPI CustomPopupThread(LPVOID param)
    {
        PopupTypes::CustomPopupConfig cfg = *reinterpret_cast<PopupTypes::CustomPopupConfig*>(param);
        delete reinterpret_cast<PopupTypes::CustomPopupConfig*>(param);
        const char* baseName = (cfg.windowName && cfg.windowName[0]) ? cfg.windowName : "StormRevivalCustomPopup";
        return RunTimedPopup(cfg, baseName, "custom popup", [&cfg](int sec) { return BuildCustomText(cfg, sec); });
    }
}

namespace PopupManager
{
    bool Init(uintptr_t gameBase)
    {
        if (!g_LockReady)
        {
            InitializeCriticalSection(&g_DialogLock);
            g_LockReady = true;
        }

        if (!PopupInternals::Init(gameBase))
        {
            Logger::Error("PopupManager: failed to initialize internals");
            return false;
        }

        g_Running = true;
        CloseAll("init-reset");
        Logger::Info("PopupManager initialized with independent multi-popup runtime");
        return true;
    }

    bool ShowTimedWelcome(const PopupTypes::TimedPopupConfig& config)
    {
        if (!g_Running)
            return false;

        auto* heapConfig = new PopupTypes::TimedPopupConfig(config);
        HANDLE thread = CreateThread(nullptr, 0, TimedWelcomeThread, heapConfig, 0, nullptr);
        if (!thread)
        {
            delete heapConfig;
            Logger::Error("PopupManager: failed to create timed welcome thread");
            return false;
        }
        CloseHandle(thread);
        return true;
    }

    bool ShowCustomPopup(const PopupTypes::CustomPopupConfig& config)
    {
        if (!g_Running)
            return false;

        auto* heapConfig = new PopupTypes::CustomPopupConfig(config);
        HANDLE thread = CreateThread(nullptr, 0, CustomPopupThread, heapConfig, 0, nullptr);
        if (!thread)
        {
            delete heapConfig;
            Logger::Error("PopupManager: failed to create custom popup thread");
            return false;
        }
        CloseHandle(thread);
        return true;
    }

    bool IsShowing()
    {
        ScopedLock lock;
        return !g_ActivePopups.empty();
    }

    bool IsBusy()
    {
        return IsShowing();
    }

    unsigned int ActivePopupId()
    {
        return g_RequestCounter.load();
    }

    void CloseNow()
    {
        CloseAll("manual");
    }

    void Shutdown()
    {
        g_Running = false;
        CloseAll("shutdown");
        PopupInternals::Shutdown();
        Logger::Info("PopupManager shutdown");
    }
}
