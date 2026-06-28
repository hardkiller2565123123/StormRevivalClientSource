#include "ScenarioHooks.h"
#include "UniversalHookRegistry.h"
#include "UniversalHookAddresses.h"
#include "UniversalHookPatterns.h"
#include "../Core/SRLogger.h"
#include <cstdint>
#include <string>

namespace StormRevival::OnlineMenu::Hooking::ScenarioHooks
{
    namespace
    {
        using FnGpSettingLoad = std::int64_t(__fastcall*)(std::uintptr_t);
        using FnScenarioParse = std::int64_t(__fastcall*)(std::uintptr_t, const char*);
        using FnXmlParse = std::int64_t(__fastcall*)(std::uintptr_t*, const char*);
        using FnXmlLookup = unsigned char*(__fastcall*)(std::uintptr_t, const char*);

        FnGpSettingLoad g_GpSettingLoad = nullptr;
        FnScenarioParse g_ScenarioParse = nullptr;
        FnXmlParse g_XmlParse = nullptr;
        FnXmlLookup g_XmlAttr = nullptr;
        FnXmlLookup g_XmlChild = nullptr;
        FnXmlLookup g_XmlSibling = nullptr;

        std::int64_t __fastcall DetourGpSettingLoad(std::uintptr_t self)
        {
            Log::Info("[ScenarioHook] gpSetting loader sub_14043FB28");
            return g_GpSettingLoad ? g_GpSettingLoad(self) : 0;
        }

        std::int64_t __fastcall DetourScenarioParse(std::uintptr_t self, const char* xml)
        {
            Log::Info(std::string("[ScenarioHook] scenario parse xml=") + (xml ? "<data>" : "<null>"));
            return g_ScenarioParse ? g_ScenarioParse(self, xml) : 0;
        }

        std::int64_t __fastcall DetourXmlParse(std::uintptr_t* outRoot, const char* xml)
        {
            Log::Info("[ScenarioHook] XML tree parse sub_1404B6284");
            return g_XmlParse ? g_XmlParse(outRoot, xml) : 0;
        }

        unsigned char* __fastcall DetourXmlAttr(std::uintptr_t node, const char* name)
        {
            return g_XmlAttr ? g_XmlAttr(node, name) : nullptr;
        }

        unsigned char* __fastcall DetourXmlChild(std::uintptr_t node, const char* name)
        {
            return g_XmlChild ? g_XmlChild(node, name) : nullptr;
        }

        unsigned char* __fastcall DetourXmlSibling(std::uintptr_t node, const char* name)
        {
            return g_XmlSibling ? g_XmlSibling(node, name) : nullptr;
        }

        HookSpec g_specs[] =
        {
            { "Scenario.GpSettingLoad.sub_14043FB28", HookGroup::Scenario, Addresses::Scenario::GpSettingLoad, reinterpret_cast<void*>(&DetourGpSettingLoad), reinterpret_cast<void**>(&g_GpSettingLoad), "Loads data/gp/setting/gpSetting.xfbin", Patterns::Scenario::GpSettingLoad, 0 },
            { "Scenario.ParseEntry.sub_14043F208", HookGroup::Scenario, Addresses::Scenario::ParseEntry, reinterpret_cast<void*>(&DetourScenarioParse), reinterpret_cast<void**>(&g_ScenarioParse), "Parses scenario XML entry", Patterns::Scenario::ParseEntry, 0 },
            { "Scenario.XmlParse.sub_1404B6284", HookGroup::Scenario, Addresses::Scenario::XmlParse, reinterpret_cast<void*>(&DetourXmlParse), reinterpret_cast<void**>(&g_XmlParse), "Build XML tree", Patterns::Scenario::XmlParse, 0 },
            { "Scenario.XmlAttribute.sub_1404B6B58", HookGroup::Scenario, Addresses::Scenario::XmlAttribute, reinterpret_cast<void*>(&DetourXmlAttr), reinterpret_cast<void**>(&g_XmlAttr), "XML attribute lookup", Patterns::Scenario::XmlAttribute, 0 },
            { "Scenario.XmlChild.sub_1404B6BC8", HookGroup::Scenario, Addresses::Scenario::XmlChild, reinterpret_cast<void*>(&DetourXmlChild), reinterpret_cast<void**>(&g_XmlChild), "XML first child lookup", Patterns::Scenario::XmlChild, 0 },
            { "Scenario.XmlSibling.sub_1404B6B90", HookGroup::Scenario, Addresses::Scenario::XmlSibling, reinterpret_cast<void*>(&DetourXmlSibling), reinterpret_cast<void**>(&g_XmlSibling), "XML sibling lookup", Patterns::Scenario::XmlSibling, 0 },
        };
    }

    void Install()
    {
        Log::Info("[ScenarioHooks] Installing scenario/XML hooks.");
        InstallHooks(g_specs, static_cast<int>(sizeof(g_specs) / sizeof(g_specs[0])));
    }

    void Shutdown()
    {
        Log::Info("[ScenarioHooks] Shutdown requested.");
    }
}
