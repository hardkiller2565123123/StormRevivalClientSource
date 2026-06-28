#include "PatternScanner.h"
#include <Windows.h>
#include <vector>
#include <string>

namespace StormRevival::OnlineMenu::Hooking
{
    namespace
    {
        struct BytePattern
        {
            std::vector<unsigned char> Bytes;
            std::vector<unsigned char> Mask;
        };

        bool IsHex(char c)
        {
            return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
        }

        unsigned char HexValue(char c)
        {
            if (c >= '0' && c <= '9') return static_cast<unsigned char>(c - '0');
            if (c >= 'a' && c <= 'f') return static_cast<unsigned char>(10 + c - 'a');
            return static_cast<unsigned char>(10 + c - 'A');
        }

        bool ParsePattern(const char* text, BytePattern& out)
        {
            out.Bytes.clear();
            out.Mask.clear();

            if (!text || !*text)
                return false;

            const char* p = text;
            while (*p)
            {
                while (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n')
                    ++p;
                if (!*p)
                    break;

                if (*p == '?')
                {
                    out.Bytes.push_back(0);
                    out.Mask.push_back(0);
                    ++p;
                    if (*p == '?')
                        ++p;
                    continue;
                }

                if (!IsHex(p[0]) || !IsHex(p[1]))
                    return false;

                out.Bytes.push_back(static_cast<unsigned char>((HexValue(p[0]) << 4) | HexValue(p[1])));
                out.Mask.push_back(0xFF);
                p += 2;
            }

            return !out.Bytes.empty() && out.Bytes.size() == out.Mask.size();
        }

        bool SectionExecutable(const IMAGE_SECTION_HEADER& section)
        {
            return (section.Characteristics & IMAGE_SCN_MEM_EXECUTE) != 0;
        }

        PatternResult Result(bool found, std::uintptr_t address, const char* error)
        {
            PatternResult r;
            r.Found = found;
            r.Address = address;
            r.Error = error;
            return r;
        }
    }

    PatternResult FindPatternInMainModule(const char* idaPattern, int relativeOffset, bool executableOnly)
    {
        BytePattern pattern;
        if (!ParsePattern(idaPattern, pattern))
            return Result(false, 0, "invalid or empty pattern");

        HMODULE module = GetModuleHandleW(nullptr);
        if (!module)
            return Result(false, 0, "GetModuleHandleW(nullptr) failed");

        const std::uintptr_t base = reinterpret_cast<std::uintptr_t>(module);
        const auto dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(base);
        if (!dos || dos->e_magic != IMAGE_DOS_SIGNATURE)
            return Result(false, 0, "invalid DOS header");

        const auto nt = reinterpret_cast<const IMAGE_NT_HEADERS*>(base + dos->e_lfanew);
        if (!nt || nt->Signature != IMAGE_NT_SIGNATURE)
            return Result(false, 0, "invalid NT header");

        const IMAGE_SECTION_HEADER* sections = IMAGE_FIRST_SECTION(nt);
        const std::size_t size = pattern.Bytes.size();

        for (WORD i = 0; i < nt->FileHeader.NumberOfSections; ++i)
        {
            const IMAGE_SECTION_HEADER& s = sections[i];
            if (executableOnly && !SectionExecutable(s))
                continue;

            const std::uintptr_t start = base + s.VirtualAddress;
            const std::uintptr_t end = start + s.Misc.VirtualSize;
            if (end <= start || end - start < size)
                continue;

            for (std::uintptr_t cur = start; cur <= end - size; ++cur)
            {
                bool match = true;
                for (std::size_t j = 0; j < size; ++j)
                {
                    if (pattern.Mask[j] && *reinterpret_cast<const unsigned char*>(cur + j) != pattern.Bytes[j])
                    {
                        match = false;
                        break;
                    }
                }

                if (match)
                    return Result(true, cur + relativeOffset, nullptr);
            }
        }

        return Result(false, 0, "pattern not found");
    }
}
