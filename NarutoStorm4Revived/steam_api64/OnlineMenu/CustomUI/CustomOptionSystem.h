#pragma once
#include <string>
#include <vector>

namespace StormRevival::OnlineMenu::CustomUI
{
    enum class OptionKind
    {
        Page,
        Toggle,
        Action,
        Debug
    };

    struct CustomOption
    {
        std::string Id;
        std::string Label;
        std::string Description;
        OptionKind Kind;
        bool Enabled;
    };

    void Install();
    void Shutdown();
    void RegisterDefaults();
    void RegisterOption(const CustomOption& option);
    const std::vector<CustomOption>& GetOptions();

    // Called by UI bridge hooks when a menu invokes known ActionScript functions.
    void OnFlashMovieRegistered(const char* movieName);
    void OnFlashInvoke(const char* movie, const char* root, const char* functionName, int argc);
    bool TryHandleMenuSelect(int selectedMode);
}
