#include "StdInc.h"
#include "RuntimeAssetTelemetry.h"
#include "Logger.h"
#include "imgui.h"

#include <mutex>
#include <chrono>
#include <cctype>

namespace
{
    std::mutex g_Mutex;
    std::vector<RuntimeAssetTelemetry::Event> g_Events;
    std::atomic<uint64_t> g_FileReadCount{ 0 };
    std::atomic<uint64_t> g_FileReadBytes{ 0 };
    std::atomic<uint64_t> g_FileWriteCount{ 0 };
    std::atomic<uint64_t> g_FileWriteBytes{ 0 };
    std::array<std::atomic<uint64_t>, 11> g_EventTypeCounts{};
    std::unordered_map<std::string, uint64_t> g_EventHitCounts;

    double Now()
    {
        using namespace std::chrono;
        static auto start = steady_clock::now();
        return duration<double>(steady_clock::now() - start).count();
    }

    bool Interesting(const std::string& s)
    {
        std::string v = s;
        std::transform(v.begin(), v.end(), v.begin(), [](unsigned char c){ return static_cast<char>(std::tolower(c)); });

        return v.find(".xfbin") != std::string::npos ||
               v.find(".cpk") != std::string::npos ||
               v.find(".nud") != std::string::npos ||
               v.find(".nut") != std::string::npos ||
               v.find(".dds") != std::string::npos ||
               v.find(".adx") != std::string::npos ||
               v.find(".awb") != std::string::npos ||
               v.find(".acb") != std::string::npos ||
               v.find(".lua") != std::string::npos ||
               v.find("\\data\\") != std::string::npos ||
               v.find("/data/") != std::string::npos;
    }

    size_t EventIndex(RuntimeAssetTelemetry::EventType type)
    {
        const size_t index = static_cast<size_t>(type);
        return index < g_EventTypeCounts.size() ? index : static_cast<size_t>(RuntimeAssetTelemetry::EventType::Unknown);
    }

    bool HighVolume(RuntimeAssetTelemetry::EventType type)
    {
        return type == RuntimeAssetTelemetry::EventType::FileOpen ||
            type == RuntimeAssetTelemetry::EventType::FindFile ||
            type == RuntimeAssetTelemetry::EventType::Xfbin ||
            type == RuntimeAssetTelemetry::EventType::Cpk;
    }

    bool ShouldRecord(RuntimeAssetTelemetry::EventType type, uint64_t hitCount, uint64_t typeCount)
    {
        if (!HighVolume(type))
            return true;

        NSR_UNUSED(hitCount);
        return typeCount <= 200 || (typeCount % 250) == 0;
    }

    bool ShouldLog(RuntimeAssetTelemetry::EventType type, uint64_t hitCount, uint64_t typeCount)
    {
        if (!HighVolume(type))
            return hitCount == 1;

        return typeCount <= 5 || (typeCount % 1000) == 0;
    }

    std::string EventKey(RuntimeAssetTelemetry::EventType type, const std::string& name, const std::string& detail)
    {
        return std::to_string(static_cast<int>(type)) + "|" + name + "|" + detail;
    }
}

namespace RuntimeAssetTelemetry
{
    bool Init()
    {
        Clear();
        Logger::Info("RuntimeAssetTelemetry initialized");
        return true;
    }

    void Shutdown()
    {
        Clear();
    }

    std::string EventTypeName(EventType type)
    {
        switch (type)
        {
        case EventType::FileOpen: return "FileOpen";
        case EventType::FileRead: return "FileRead";
        case EventType::FileWrite: return "FileWrite";
        case EventType::FindFile: return "FindFile";
        case EventType::Xfbin: return "XFBIN";
        case EventType::Cpk: return "CPK";
        case EventType::Model: return "Model";
        case EventType::Texture: return "Texture";
        case EventType::Sound: return "Sound";
        case EventType::Lua: return "Lua";
        default: return "Unknown";
        }
    }

    void Push(EventType type, const std::string& name, const std::string& detail, uint64_t size)
    {
        if (type == EventType::FileRead || type == EventType::FileWrite)
        {
            if (type == EventType::FileRead)
            {
                g_FileReadCount.fetch_add(1, std::memory_order_relaxed);
                g_FileReadBytes.fetch_add(size, std::memory_order_relaxed);
            }
            else
            {
                g_FileWriteCount.fetch_add(1, std::memory_order_relaxed);
                g_FileWriteBytes.fetch_add(size, std::memory_order_relaxed);
            }

            return;
        }

        if ((type == EventType::FileOpen || type == EventType::FindFile) && !Interesting(name))
            return;

        const uint64_t typeCount = g_EventTypeCounts[EventIndex(type)].fetch_add(1, std::memory_order_relaxed) + 1;

        Event e{};
        e.Type = type;
        e.Name = name;
        e.Detail = detail;
        e.Size = size;
        e.ThreadId = GetCurrentThreadId();
        e.TimeSeconds = Now();

        uint64_t hitCount = 1;
        bool recordEvent = true;

        if (HighVolume(type))
        {
            hitCount = typeCount;
            recordEvent = ShouldRecord(type, hitCount, typeCount);

            if (recordEvent)
            {
                std::lock_guard<std::mutex> lock(g_Mutex);

                if (hitCount > 1)
                    e.Detail += " x" + std::to_string(static_cast<unsigned long long>(hitCount));

                g_Events.push_back(e);
                if (g_Events.size() > 1000)
                    g_Events.erase(g_Events.begin(), g_Events.begin() + 200);
            }
        }
        else
        {
            std::lock_guard<std::mutex> lock(g_Mutex);

            hitCount = ++g_EventHitCounts[EventKey(type, name, detail)];
            recordEvent = ShouldRecord(type, hitCount, typeCount);

            if (recordEvent)
            {
                if (hitCount > 1)
                    e.Detail += " x" + std::to_string(static_cast<unsigned long long>(hitCount));

                g_Events.push_back(e);
                if (g_Events.size() > 1000)
                    g_Events.erase(g_Events.begin(), g_Events.begin() + 200);
            }
        }

        if (ShouldLog(type, hitCount, typeCount))
        {
            std::string message = "[RUNTIME] " + EventTypeName(type) + " | " + name + " | " + detail;
            if (hitCount > 1)
                message += " x" + std::to_string(static_cast<unsigned long long>(hitCount));

            Logger::Info(message);
        }
    }

    std::vector<Event> Snapshot()
    {
        std::lock_guard<std::mutex> lock(g_Mutex);
        return g_Events;
    }

    void Clear()
    {
        std::lock_guard<std::mutex> lock(g_Mutex);
        g_Events.clear();
        g_FileReadCount.store(0, std::memory_order_relaxed);
        g_FileReadBytes.store(0, std::memory_order_relaxed);
        g_FileWriteCount.store(0, std::memory_order_relaxed);
        g_FileWriteBytes.store(0, std::memory_order_relaxed);
        g_EventHitCounts.clear();

        for (auto& count : g_EventTypeCounts)
            count.store(0, std::memory_order_relaxed);
    }

    int Count(EventType type)
    {
        if (type == EventType::FileRead)
            return static_cast<int>(std::min<uint64_t>(g_FileReadCount.load(std::memory_order_relaxed), 2147483647ull));

        if (type == EventType::FileWrite)
            return static_cast<int>(std::min<uint64_t>(g_FileWriteCount.load(std::memory_order_relaxed), 2147483647ull));

        return static_cast<int>(std::min<uint64_t>(
            g_EventTypeCounts[EventIndex(type)].load(std::memory_order_relaxed),
            2147483647ull));
    }

    void DrawDebugPanel()
    {
        ImGui::Text("Runtime Asset Telemetry");
        ImGui::Separator();

        if (ImGui::Button("Clear Runtime Events", ImVec2(180, 24)))
            Clear();

        ImGui::SameLine();
        uint64_t readCount = 0;
        uint64_t readBytes = 0;
        uint64_t writeCount = 0;
        uint64_t writeBytes = 0;

        readCount = g_FileReadCount.load(std::memory_order_relaxed);
        readBytes = g_FileReadBytes.load(std::memory_order_relaxed);
        writeCount = g_FileWriteCount.load(std::memory_order_relaxed);
        writeBytes = g_FileWriteBytes.load(std::memory_order_relaxed);

        ImGui::TextDisabled("Open %d | XFBIN %d | CPK %d | Texture %d | Model %d | Sound %d | Lua %d",
            Count(EventType::FileOpen), Count(EventType::Xfbin), Count(EventType::Cpk),
            Count(EventType::Texture), Count(EventType::Model), Count(EventType::Sound), Count(EventType::Lua));

        ImGui::TextDisabled("Read %llu calls / %.2f MB | Write %llu calls / %.2f MB",
            static_cast<unsigned long long>(readCount),
            static_cast<double>(readBytes) / 1024.0 / 1024.0,
            static_cast<unsigned long long>(writeCount),
            static_cast<double>(writeBytes) / 1024.0 / 1024.0);

        auto events = Snapshot();
        ImGui::BeginChild("##RuntimeEvents", ImVec2(0, 260), true);
        int start = static_cast<int>(events.size()) - 300;
        if (start < 0) start = 0;

        for (int i = start; i < static_cast<int>(events.size()); ++i)
        {
            const auto& e = events[i];
            ImGui::TextWrapped("[%.2f] [%s] T%u %s %s",
                e.TimeSeconds, EventTypeName(e.Type).c_str(), e.ThreadId, e.Name.c_str(), e.Detail.c_str());
        }
        ImGui::EndChild();
    }
}
