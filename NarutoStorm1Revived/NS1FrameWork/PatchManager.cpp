#include "StdInc.h"
#include "PatchManager.h"
#include "Logger.h"

namespace
{
    PatchManager::PatchState g_State;
    std::atomic<bool> g_TextPatchWorkerRunning = false;
    HANDLE g_TextPatchWorker = nullptr;

    bool IsReadableProtect(DWORD protect)
    {
        if (protect & (PAGE_GUARD | PAGE_NOACCESS))
            return false;

        protect &= 0xff;
        return protect == PAGE_READONLY ||
            protect == PAGE_READWRITE ||
            protect == PAGE_WRITECOPY ||
            protect == PAGE_EXECUTE_READ ||
            protect == PAGE_EXECUTE_READWRITE ||
            protect == PAGE_EXECUTE_WRITECOPY;
    }

    std::vector<unsigned char> AsciiBytes(const std::string& text)
    {
        return std::vector<unsigned char>(text.begin(), text.end());
    }

    std::vector<unsigned char> Utf16Bytes(const std::string& text)
    {
        std::vector<unsigned char> bytes;
        bytes.reserve(text.size() * sizeof(wchar_t));

        for (char c : text)
        {
            bytes.push_back(static_cast<unsigned char>(c));
            bytes.push_back(0);
        }

        return bytes;
    }

    std::vector<unsigned char> BlankBytes(size_t count, bool utf16)
    {
        std::vector<unsigned char> blank(count, 0);

        if (utf16)
        {
            for (size_t i = 0; i + 1 < count; i += 2)
            {
                blank[i] = static_cast<unsigned char>(' ');
                blank[i + 1] = 0;
            }
        }
        else
        {
            std::fill(blank.begin(), blank.end(), static_cast<unsigned char>(' '));
        }

        return blank;
    }

    bool AddressInRange(const void* address, const void* begin, size_t size)
    {
        const uintptr_t target = reinterpret_cast<uintptr_t>(address);
        const uintptr_t start = reinterpret_cast<uintptr_t>(begin);
        const uintptr_t end = start + size;
        return target >= start && target < end;
    }

    bool PatchBytes(void* address, const std::vector<unsigned char>& replacement)
    {
        if (!address || replacement.empty())
            return false;

        DWORD oldProtect = 0;
        if (!VirtualProtect(address, replacement.size(), PAGE_EXECUTE_READWRITE, &oldProtect))
            return false;

        std::memcpy(address, replacement.data(), replacement.size());
        FlushInstructionCache(GetCurrentProcess(), address, replacement.size());

        DWORD ignored = 0;
        VirtualProtect(address, replacement.size(), oldProtect, &ignored);
        return true;
    }

    size_t PatchPatternInRegion(
        const MEMORY_BASIC_INFORMATION& mbi,
        const std::vector<unsigned char>& needle,
        const std::vector<unsigned char>& replacement,
        const std::vector<std::pair<const void*, size_t>>& skipRanges)
    {
        if (needle.empty() || replacement.size() != needle.size())
            return 0;

        for (const auto& skip : skipRanges)
        {
            if (skip.first && skip.second != 0 && AddressInRange(skip.first, mbi.BaseAddress, mbi.RegionSize))
                return 0;
        }

        constexpr size_t kChunkSize = 1024 * 1024;
        const size_t overlap = needle.size() > 1 ? needle.size() - 1 : 0;
        const auto* regionBase = static_cast<const unsigned char*>(mbi.BaseAddress);
        size_t patched = 0;
        size_t offset = 0;

        while (offset < mbi.RegionSize)
        {
            const size_t remaining = mbi.RegionSize - offset;
            const size_t readSize = std::min(kChunkSize + overlap, remaining);
            std::vector<unsigned char> buffer(readSize);
            SIZE_T bytesRead = 0;

            if (!ReadProcessMemory(GetCurrentProcess(), regionBase + offset, buffer.data(), readSize, &bytesRead) || bytesRead < needle.size())
            {
                offset += std::min(kChunkSize, remaining);
                continue;
            }

            auto searchBegin = buffer.begin();
            const auto searchEnd = buffer.begin() + static_cast<ptrdiff_t>(bytesRead);

            while (searchBegin != searchEnd)
            {
                auto match = std::search(searchBegin, searchEnd, needle.begin(), needle.end());
                if (match == searchEnd)
                    break;

                const size_t matchOffset = static_cast<size_t>(std::distance(buffer.begin(), match));
                void* liveAddress = const_cast<unsigned char*>(regionBase + offset + matchOffset);

                if (PatchBytes(liveAddress, replacement))
                    ++patched;

                searchBegin = match + static_cast<ptrdiff_t>(needle.size());
            }

            offset += std::min(kChunkSize, remaining);
        }

        return patched;
    }

    size_t SuppressOnlineConnectionWarningText()
    {
        const std::string warningBase =
            std::string("You need an active ") +
            "internet connection to play in this mode";
        const std::array<std::string, 2> warnings = {
            warningBase + ".",
            warningBase
        };

        SYSTEM_INFO info{};
        GetSystemInfo(&info);

        size_t patched = 0;

        for (const std::string& warning : warnings)
        {
            const std::vector<unsigned char> ascii = AsciiBytes(warning);
            const std::vector<unsigned char> asciiBlank = BlankBytes(ascii.size(), false);
            const std::vector<unsigned char> utf16 = Utf16Bytes(warning);
            const std::vector<unsigned char> utf16Blank = BlankBytes(utf16.size(), true);
            const std::vector<std::pair<const void*, size_t>> skipRanges = {
                { warning.data(), warning.size() },
                { warningBase.data(), warningBase.size() },
                { ascii.data(), ascii.size() },
                { asciiBlank.data(), asciiBlank.size() },
                { utf16.data(), utf16.size() },
                { utf16Blank.data(), utf16Blank.size() }
            };

            uintptr_t address = reinterpret_cast<uintptr_t>(info.lpMinimumApplicationAddress);
            const uintptr_t maxAddress = reinterpret_cast<uintptr_t>(info.lpMaximumApplicationAddress);

            while (address < maxAddress)
            {
                MEMORY_BASIC_INFORMATION mbi{};
                if (VirtualQuery(reinterpret_cast<const void*>(address), &mbi, sizeof(mbi)) == 0)
                    break;

                const uintptr_t next = reinterpret_cast<uintptr_t>(mbi.BaseAddress) + mbi.RegionSize;

                if (mbi.State == MEM_COMMIT &&
                    (mbi.Type == MEM_IMAGE || mbi.Type == MEM_MAPPED) &&
                    IsReadableProtect(mbi.Protect))
                {
                    patched += PatchPatternInRegion(mbi, ascii, asciiBlank, skipRanges);
                    patched += PatchPatternInRegion(mbi, utf16, utf16Blank, skipRanges);
                }

                if (next <= address)
                    break;

                address = next;
            }
        }

        return patched;
    }

    DWORD WINAPI TextPatchWorkerMain(LPVOID)
    {
        size_t totalPatched = 0;

        for (int attempt = 0; g_TextPatchWorkerRunning && attempt < 90; ++attempt)
        {
            const size_t patched = SuppressOnlineConnectionWarningText();
            totalPatched += patched;

            if (patched > 0)
            {
                Logger::Info(
                    "PatchManager suppressed online connection warning text count=" +
                    std::to_string(static_cast<unsigned long long>(patched)));
                break;
            }

            Sleep(attempt < 10 ? 500 : 1500);
        }

        if (totalPatched == 0)
            Logger::Info("PatchManager online warning text suppressor found no loaded text to patch");

        return 0;
    }

    void StartTextPatchWorker()
    {
        if (g_TextPatchWorker)
            return;

        g_TextPatchWorkerRunning = true;
        g_TextPatchWorker = CreateThread(nullptr, 0, TextPatchWorkerMain, nullptr, 0, nullptr);

        if (!g_TextPatchWorker)
        {
            g_TextPatchWorkerRunning = false;
            Logger::Error("PatchManager failed to start online warning text suppressor");
        }
    }
}

namespace PatchManager
{
    bool Init()
    {
        Logger::Info("PatchManager initialized");
        StartTextPatchWorker();
        return true;
    }

    void Shutdown()
    {
        g_TextPatchWorkerRunning = false;

        if (g_TextPatchWorker)
        {
            WaitForSingleObject(g_TextPatchWorker, 1000);
            CloseHandle(g_TextPatchWorker);
            g_TextPatchWorker = nullptr;
        }

        Logger::Info("PatchManager shutdown");
    }

    PatchState& State()
    {
        return g_State;
    }

    const PatchState& GetState()
    {
        return g_State;
    }

    void ApplySafePatches()
    {
        Logger::Info("PatchManager: ApplySafePatches");
        SuppressOnlineConnectionWarningText();
    }

    void ApplyDisplayPatches()
    {
        Logger::Info("PatchManager: ApplyDisplayPatches");
    }

    void ApplyGameplayPatches()
    {
        Logger::Info("PatchManager: ApplyGameplayPatches");
        SuppressOnlineConnectionWarningText();
    }
}
