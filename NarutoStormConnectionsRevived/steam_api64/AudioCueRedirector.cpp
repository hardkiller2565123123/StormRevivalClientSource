#include "StdInc.h"
#include "AudioCueRedirector.h"
#include "CustomAudioPlayer.h"
#include "HookManager.h"
#include "Logger.h"

namespace
{
    using PlayCue_t = void(__fastcall*)(__int64, unsigned int, signed int, int, int);

    constexpr uintptr_t kPlayCueRva = 0x12CB040;
    constexpr unsigned int kTitleCueId = 203;

    PlayCue_t g_originalPlayCue = nullptr;
    std::atomic<bool> g_initialized{ false };

    bool IsMusicCue(int slot, int mode)
    {
        return mode == 0 && slot >= 0 && slot <= 2;
    }

    void __fastcall Hook_PlayCue(__int64 atomManager, unsigned int cueId, signed int slot, int mode, int bank)
    {
        Logger::Info("[AUDIO-CUE] cueId=" + std::to_string(cueId) +
            " slot=" + std::to_string(slot) +
            " mode=" + std::to_string(mode) +
            " bank=" + std::to_string(bank));

        if (IsMusicCue(slot, mode))
        {
            if (cueId == kTitleCueId && CustomAudioPlayer::HasTitleTrack())
            {
                if (CustomAudioPlayer::PlayTitleLoop())
                {
                    Logger::Info("AudioCueRedirector: replaced title cue 203 with title.wav");
                    return;
                }

                Logger::Warn("AudioCueRedirector: title.wav failed, falling back to game cue");
            }
            else if (CustomAudioPlayer::IsTitlePlaying())
            {
                Logger::Info("AudioCueRedirector: fading out title.wav for cueId=" + std::to_string(cueId));
                CustomAudioPlayer::FadeOutTitle(750);
            }
        }

        if (g_originalPlayCue)
            g_originalPlayCue(atomManager, cueId, slot, mode, bank);
    }
}

namespace AudioCueRedirector
{
    bool Init()
    {
        if (g_initialized.exchange(true))
            return true;

        CustomAudioPlayer::Init();

        HMODULE exe = GetModuleHandleW(nullptr);
        if (!exe)
        {
            Logger::Error("AudioCueRedirector: GetModuleHandleW failed");
            return false;
        }

        void* target = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(exe) + kPlayCueRva);

        if (!HookManager::Create(target, reinterpret_cast<void*>(&Hook_PlayCue), reinterpret_cast<void**>(&g_originalPlayCue)))
        {
            Logger::Error("AudioCueRedirector: failed to create PlayCue hook");
            return false;
        }

        if (!HookManager::Enable(target))
        {
            Logger::Error("AudioCueRedirector: failed to enable PlayCue hook");
            return false;
        }

        Logger::Info("AudioCueRedirector initialized: cue 203 -> Audio\\title.wav with fade-out");
        return true;
    }

    void Shutdown()
    {
        if (!g_initialized.exchange(false))
            return;

        CustomAudioPlayer::Shutdown();
        Logger::Info("AudioCueRedirector shutdown");
    }
}
