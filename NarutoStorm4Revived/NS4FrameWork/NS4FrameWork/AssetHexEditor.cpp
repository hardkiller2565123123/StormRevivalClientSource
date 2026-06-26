#include "StdInc.h"
#include "AssetHexEditor.h"
#include "AssetPreviewResolver.h"
#include "AssetOverrideManager.h"
#include "AssetNotification.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <cstdlib>

namespace
{
    AssetHexEditor::Session g_Session;

    bool ReadFile(const std::string& path, std::vector<unsigned char>& out)
    {
        out.clear();

        std::ifstream file(path, std::ios::binary);

        if (!file.is_open())
            return false;

        file.seekg(0, std::ios::end);
        size_t size = static_cast<size_t>(std::max<std::streamoff>(0, file.tellg()));
        file.seekg(0, std::ios::beg);

        if (size > 64 * 1024 * 1024)
            size = 64 * 1024 * 1024;

        out.resize(size);

        if (size)
            file.read(reinterpret_cast<char*>(out.data()), static_cast<std::streamsize>(size));

        return true;
    }

    bool WriteFile(const std::string& path, const std::vector<unsigned char>& bytes)
    {
        std::filesystem::create_directories(std::filesystem::path(path).parent_path());

        std::ofstream file(path, std::ios::binary | std::ios::trunc);

        if (!file.is_open())
            return false;

        file.write(reinterpret_cast<const char*>(bytes.data()), static_cast<std::streamsize>(bytes.size()));
        return true;
    }
}

namespace AssetHexEditor
{
    bool Init() { return true; }
    void Shutdown() { Clear(); }

    bool LoadAsset(const AssetBrowser::AssetEntry& asset, bool makeOverrideCopy)
    {
        Clear();

        std::string path;

        if (!AssetPreviewResolver::ResolveReadablePath(asset, path, true))
        {
            g_Session.Status = "Could not resolve readable asset.";
            return false;
        }

        if (makeOverrideCopy)
        {
            AssetOverrideManager::CreateOverrideFromFile(asset, path);
            path = AssetOverrideManager::GetOverridePath(asset);
        }

        if (!ReadFile(path, g_Session.Bytes))
        {
            g_Session.Status = "Failed to read file.";
            return false;
        }

        g_Session.Loaded = true;
        g_Session.Dirty = false;
        g_Session.SourcePath = path;
        g_Session.WorkingPath = path;
        g_Session.Status = "Loaded " + path;
        return true;
    }

    bool Save()
    {
        if (!g_Session.Loaded || g_Session.WorkingPath.empty())
            return false;

        if (!WriteFile(g_Session.WorkingPath, g_Session.Bytes))
        {
            g_Session.Status = "Save failed.";
            return false;
        }

        g_Session.Dirty = false;
        g_Session.Status = "Saved " + g_Session.WorkingPath;
        AssetNotification::PushSuccess("Hex Saved", g_Session.WorkingPath);
        return true;
    }

    bool SaveAs(const std::string& path)
    {
        if (!g_Session.Loaded)
            return false;

        if (!WriteFile(path, g_Session.Bytes))
            return false;

        g_Session.WorkingPath = path;
        g_Session.Dirty = false;
        g_Session.Status = "Saved as " + path;
        return true;
    }

    void Revert()
    {
        if (g_Session.WorkingPath.empty())
            return;

        std::vector<unsigned char> bytes;

        if (ReadFile(g_Session.WorkingPath, bytes))
        {
            g_Session.Bytes = bytes;
            g_Session.Dirty = false;
            g_Session.Status = "Reverted.";
        }
    }

    void Clear()
    {
        g_Session = Session{};
    }

    Session& GetSession()
    {
        return g_Session;
    }

    int FindString(const std::string& text, size_t startOffset)
    {
        if (!g_Session.Loaded || text.empty())
            return -1;

        for (size_t i = startOffset; i + text.size() <= g_Session.Bytes.size(); ++i)
        {
            if (std::memcmp(g_Session.Bytes.data() + i, text.data(), text.size()) == 0)
                return static_cast<int>(i);
        }

        return -1;
    }

    int FindBytes(const std::vector<unsigned char>& bytes, size_t startOffset)
    {
        if (!g_Session.Loaded || bytes.empty() || bytes.size() > g_Session.Bytes.size())
            return -1;

        for (size_t i = startOffset; i + bytes.size() <= g_Session.Bytes.size(); ++i)
        {
            if (std::memcmp(g_Session.Bytes.data() + i, bytes.data(), bytes.size()) == 0)
                return static_cast<int>(i);
        }

        return -1;
    }

    bool WriteByte(size_t offset, unsigned char value)
    {
        if (!g_Session.Loaded || offset >= g_Session.Bytes.size())
        {
            g_Session.Status = "Write byte offset is out of range.";
            return false;
        }

        g_Session.Bytes[offset] = value;
        g_Session.Cursor = offset;
        g_Session.Dirty = true;
        g_Session.Status = "Byte edited. Save required.";
        return true;
    }

    bool WriteBytes(size_t offset, const std::vector<unsigned char>& bytes)
    {
        if (!g_Session.Loaded || bytes.empty())
        {
            g_Session.Status = "No bytes to write.";
            return false;
        }

        if (offset > g_Session.Bytes.size() || offset + bytes.size() > g_Session.Bytes.size())
        {
            g_Session.Status = "Write range is out of bounds.";
            return false;
        }

        std::copy(bytes.begin(), bytes.end(), g_Session.Bytes.begin() + static_cast<ptrdiff_t>(offset));
        g_Session.Cursor = offset;
        g_Session.Dirty = true;
        g_Session.Status = "Hex bytes written. Save required.";
        return true;
    }

    bool InsertBytes(size_t offset, const std::vector<unsigned char>& bytes)
    {
        if (!g_Session.Loaded || bytes.empty())
        {
            g_Session.Status = "No bytes to insert.";
            return false;
        }

        if (offset > g_Session.Bytes.size())
        {
            g_Session.Status = "Insert offset is out of range.";
            return false;
        }

        g_Session.Bytes.insert(g_Session.Bytes.begin() + static_cast<ptrdiff_t>(offset), bytes.begin(), bytes.end());
        g_Session.Cursor = offset;
        g_Session.Dirty = true;
        g_Session.Status = "Hex bytes inserted. Save required.";
        return true;
    }

    bool DeleteBytes(size_t offset, size_t count)
    {
        if (!g_Session.Loaded || count == 0)
        {
            g_Session.Status = "No bytes to delete.";
            return false;
        }

        if (offset >= g_Session.Bytes.size())
        {
            g_Session.Status = "Delete offset is out of range.";
            return false;
        }

        const size_t end = std::min(g_Session.Bytes.size(), offset + count);
        g_Session.Bytes.erase(
            g_Session.Bytes.begin() + static_cast<ptrdiff_t>(offset),
            g_Session.Bytes.begin() + static_cast<ptrdiff_t>(end));
        g_Session.Cursor = std::min(offset, g_Session.Bytes.empty() ? size_t(0) : g_Session.Bytes.size() - 1);
        g_Session.Dirty = true;
        g_Session.Status = "Bytes deleted. Save required.";
        return true;
    }

    bool ParseHexString(const std::string& text, std::vector<unsigned char>& outBytes, std::string* error)
    {
        outBytes.clear();
        if (error)
            error->clear();

        std::string token;
        auto fail = [&](const std::string& message)
        {
            if (error)
                *error = message;
            return false;
        };

        auto flushToken = [&]() -> bool
        {
            if (token.empty())
                return true;

            if (token.size() > 2 && token[0] == '0' && (token[1] == 'x' || token[1] == 'X'))
                token.erase(0, 2);

            if (token.empty() || token.size() > 2)
                return fail("Use one-byte hex tokens like 00, 7F, or 0x90.");

            char* end = nullptr;
            unsigned long value = std::strtoul(token.c_str(), &end, 16);

            if (!end || *end != '\0' || value > 0xFF)
                return fail("Invalid hex byte: " + token);

            outBytes.push_back(static_cast<unsigned char>(value));
            token.clear();
            return true;
        };

        for (char c : text)
        {
            if (std::isspace(static_cast<unsigned char>(c)) || c == ',' || c == ';')
            {
                if (!flushToken())
                    return false;
                continue;
            }

            if (!std::isxdigit(static_cast<unsigned char>(c)) && c != 'x' && c != 'X')
                return fail("Only hex bytes, spaces, commas, and 0x prefixes are supported.");

            token.push_back(c);
        }

        if (!flushToken())
            return false;

        if (outBytes.empty())
            return fail("No hex bytes entered.");

        return true;
    }

    std::string BuildHexView(size_t startOffset, size_t maxBytes)
    {
        std::ostringstream ss;

        if (!g_Session.Loaded)
            return "";

        size_t end = std::min(g_Session.Bytes.size(), startOffset + maxBytes);

        for (size_t i = startOffset; i < end; i += 16)
        {
            ss << std::hex << std::setw(8) << std::setfill('0') << i << "  ";

            for (size_t j = 0; j < 16; ++j)
            {
                if (i + j < end)
                    ss << std::setw(2) << static_cast<int>(g_Session.Bytes[i + j]) << " ";
                else
                    ss << "   ";
            }

            ss << " ";

            for (size_t j = 0; j < 16 && i + j < end; ++j)
            {
                unsigned char c = g_Session.Bytes[i + j];
                ss << ((c >= 32 && c < 127) ? static_cast<char>(c) : '.');
            }

            ss << "\n";
        }

        return ss.str();
    }
}
