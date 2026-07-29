#include "StdInc.h"
#include "CustomAudioPlayer.h"
#include "Logger.h"

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

namespace
{
    std::mutex g_audioMutex;
    std::wstring g_titlePath;
    bool g_initialized = false;
    bool g_playing = false;
    bool g_stopRequested = false;
    bool g_fading = false;
    float g_volume = 0.30f;
    std::thread g_audioThread;

    struct WavData
    {
        WAVEFORMATEX format{};
        std::vector<BYTE> pcmOriginal;
        std::vector<BYTE> pcmScaled;
    };

    std::string Narrow(const std::wstring& ws)
    {
        if (ws.empty())
            return {};

        int size = WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), -1, nullptr, 0, nullptr, nullptr);
        if (size <= 0)
            return {};

        std::string out(size - 1, '\0');
        WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), -1, out.data(), size, nullptr, nullptr);
        return out;
    }

    std::filesystem::path GameDir()
    {
        wchar_t path[MAX_PATH]{};
        GetModuleFileNameW(nullptr, path, MAX_PATH);
        return std::filesystem::path(path).parent_path();
    }

    std::wstring FindTitleTrack()
    {
        const auto base = GameDir();

        const std::filesystem::path candidates[] =
        {
            base / L"NarutoStormConnectionsRevived" / L"Audio" / L"title.wav",
            base / L"NarutoStormConnectionsRevived" / L"title.wav",
            base / L"Audio" / L"title.wav",
            base / L"title.wav",
        };

        for (const auto& p : candidates)
        {
            std::error_code ec;
            if (std::filesystem::exists(p, ec) && !ec)
                return p.wstring();
        }

        return {};
    }

    DWORD ReadU32(const BYTE* p)
    {
        return (DWORD)p[0] | ((DWORD)p[1] << 8) | ((DWORD)p[2] << 16) | ((DWORD)p[3] << 24);
    }

    WORD ReadU16(const BYTE* p)
    {
        return (WORD)p[0] | ((WORD)p[1] << 8);
    }

    void ApplyVolume(WavData& wav)
    {
        wav.pcmScaled = wav.pcmOriginal;

        int16_t* samples = reinterpret_cast<int16_t*>(wav.pcmScaled.data());
        const size_t count = wav.pcmScaled.size() / sizeof(int16_t);

        float vol;
        {
            std::lock_guard<std::mutex> lock(g_audioMutex);
            vol = std::clamp(g_volume, 0.0f, 1.0f);
        }

        for (size_t i = 0; i < count; ++i)
        {
            int sample = static_cast<int>(samples[i] * vol);
            sample = std::clamp(sample, -32768, 32767);
            samples[i] = static_cast<int16_t>(sample);
        }
    }

    bool LoadWavFile(const std::wstring& path, WavData& out)
    {
        std::ifstream file(path, std::ios::binary);
        if (!file)
        {
            Logger::Error("CustomAudioPlayer: failed to open wav file: " + Narrow(path));
            return false;
        }

        std::vector<BYTE> bytes((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        if (bytes.size() < 44)
        {
            Logger::Error("CustomAudioPlayer: wav too small");
            return false;
        }

        if (memcmp(bytes.data(), "RIFF", 4) != 0 || memcmp(bytes.data() + 8, "WAVE", 4) != 0)
        {
            Logger::Error("CustomAudioPlayer: not a RIFF/WAVE file: " + Narrow(path));
            return false;
        }

        bool foundFmt = false;
        bool foundData = false;
        WAVEFORMATEX fmt{};
        std::vector<BYTE> pcm;

        size_t pos = 12;
        while (pos + 8 <= bytes.size())
        {
            const BYTE* chunk = bytes.data() + pos;
            DWORD chunkSize = ReadU32(chunk + 4);
            size_t dataPos = pos + 8;

            if (dataPos + chunkSize > bytes.size())
                break;

            if (memcmp(chunk, "fmt ", 4) == 0)
            {
                if (chunkSize < 16)
                    return false;

                fmt.wFormatTag = ReadU16(bytes.data() + dataPos + 0);
                fmt.nChannels = ReadU16(bytes.data() + dataPos + 2);
                fmt.nSamplesPerSec = ReadU32(bytes.data() + dataPos + 4);
                fmt.nAvgBytesPerSec = ReadU32(bytes.data() + dataPos + 8);
                fmt.nBlockAlign = ReadU16(bytes.data() + dataPos + 12);
                fmt.wBitsPerSample = ReadU16(bytes.data() + dataPos + 14);
                fmt.cbSize = 0;
                foundFmt = true;
            }
            else if (memcmp(chunk, "data", 4) == 0)
            {
                pcm.assign(bytes.begin() + dataPos, bytes.begin() + dataPos + chunkSize);
                foundData = true;
            }

            pos = dataPos + chunkSize;
            if (chunkSize & 1)
                ++pos;
        }

        if (!foundFmt || !foundData)
        {
            Logger::Error("CustomAudioPlayer: missing fmt/data chunk");
            return false;
        }

        if (fmt.wFormatTag != WAVE_FORMAT_PCM || fmt.wBitsPerSample != 16)
        {
            Logger::Error("CustomAudioPlayer: only 16-bit PCM WAV supported");
            return false;
        }

        out.format = fmt;
        out.pcmOriginal = std::move(pcm);
        ApplyVolume(out);

        Logger::Info("CustomAudioPlayer: loaded wav " +
            std::to_string(fmt.nChannels) + "ch " +
            std::to_string(fmt.nSamplesPerSec) + "Hz 16bit bytes=" +
            std::to_string(out.pcmOriginal.size()));

        return true;
    }

    void AudioThreadMain(std::wstring path)
    {
        WavData wav;
        if (!LoadWavFile(path, wav))
        {
            std::lock_guard<std::mutex> lock(g_audioMutex);
            g_playing = false;
            return;
        }

        HWAVEOUT hWave = nullptr;
        MMRESULT openResult = waveOutOpen(&hWave, WAVE_MAPPER, &wav.format, 0, 0, CALLBACK_NULL);
        if (openResult != MMSYSERR_NOERROR || !hWave)
        {
            Logger::Error("CustomAudioPlayer: waveOutOpen failed result=" + std::to_string(openResult));
            std::lock_guard<std::mutex> lock(g_audioMutex);
            g_playing = false;
            return;
        }

        Logger::Info("CustomAudioPlayer: waveOut started title.wav loop");

        while (true)
        {
            {
                std::lock_guard<std::mutex> lock(g_audioMutex);
                if (g_stopRequested)
                    break;
            }

            ApplyVolume(wav);

            WAVEHDR hdr{};
            hdr.lpData = reinterpret_cast<LPSTR>(wav.pcmScaled.data());
            hdr.dwBufferLength = static_cast<DWORD>(wav.pcmScaled.size());

            if (waveOutPrepareHeader(hWave, &hdr, sizeof(hdr)) != MMSYSERR_NOERROR)
                break;

            if (waveOutWrite(hWave, &hdr, sizeof(hdr)) != MMSYSERR_NOERROR)
            {
                waveOutUnprepareHeader(hWave, &hdr, sizeof(hdr));
                break;
            }

            while (!(hdr.dwFlags & WHDR_DONE))
            {
                {
                    std::lock_guard<std::mutex> lock(g_audioMutex);
                    if (g_stopRequested)
                    {
                        waveOutReset(hWave);
                        break;
                    }
                }
                Sleep(25);
            }

            waveOutUnprepareHeader(hWave, &hdr, sizeof(hdr));
        }

        waveOutReset(hWave);
        waveOutClose(hWave);

        {
            std::lock_guard<std::mutex> lock(g_audioMutex);
            g_playing = false;
            g_stopRequested = false;
            g_fading = false;
            g_volume = 0.30f;
        }

        Logger::Info("CustomAudioPlayer: waveOut stopped");
    }

    void StopNoLock()
    {
        if (!g_playing)
            return;

        g_stopRequested = true;
    }
}

namespace CustomAudioPlayer
{
    bool Init()
    {
        std::lock_guard<std::mutex> lock(g_audioMutex);

        g_titlePath = FindTitleTrack();
        g_initialized = true;

        if (!g_titlePath.empty())
            Logger::Info("CustomAudioPlayer: title wav found: " + Narrow(g_titlePath));
        else
            Logger::Warn("CustomAudioPlayer: no title.wav found");

        return true;
    }

    void Shutdown()
    {
        {
            std::lock_guard<std::mutex> lock(g_audioMutex);
            StopNoLock();
            g_initialized = false;
            g_titlePath.clear();
        }

        if (g_audioThread.joinable())
            g_audioThread.join();
    }

    bool HasTitleTrack()
    {
        std::lock_guard<std::mutex> lock(g_audioMutex);

        if (g_titlePath.empty())
            g_titlePath = FindTitleTrack();

        return !g_titlePath.empty();
    }

    std::wstring TitlePath()
    {
        std::lock_guard<std::mutex> lock(g_audioMutex);

        if (g_titlePath.empty())
            g_titlePath = FindTitleTrack();

        return g_titlePath;
    }

    bool PlayTitleLoop()
    {
        std::wstring path;

        {
            std::lock_guard<std::mutex> lock(g_audioMutex);

            if (g_titlePath.empty())
                g_titlePath = FindTitleTrack();

            if (g_titlePath.empty())
                return false;

            if (g_playing)
                return true;

            g_stopRequested = false;
            g_fading = false;
            g_volume = 0.30f;
            g_playing = true;
            path = g_titlePath;
        }

        if (g_audioThread.joinable())
            g_audioThread.join();

        g_audioThread = std::thread(AudioThreadMain, path);
        Logger::Info("CustomAudioPlayer: started title.wav thread: " + Narrow(path));
        return true;
    }

    void StopTitle()
    {
        {
            std::lock_guard<std::mutex> lock(g_audioMutex);
            StopNoLock();
        }

        if (g_audioThread.joinable())
            g_audioThread.join();
    }

    void FadeOutTitle(int durationMs)
    {
        {
            std::lock_guard<std::mutex> lock(g_audioMutex);
            if (!g_playing || g_fading)
                return;
            g_fading = true;
        }

        std::thread([durationMs]()
        {
            constexpr int steps = 20;
            const int sleepMs = std::max(1, durationMs / steps);

            for (int i = steps; i >= 0; --i)
            {
                {
                    std::lock_guard<std::mutex> lock(g_audioMutex);
                    g_volume = 0.30f * (static_cast<float>(i) / static_cast<float>(steps));
                }
                Sleep(sleepMs);
            }

            StopTitle();
        }).detach();
    }

    bool IsTitlePlaying()
    {
        std::lock_guard<std::mutex> lock(g_audioMutex);
        return g_playing;
    }
}
