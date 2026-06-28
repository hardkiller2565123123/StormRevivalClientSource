#pragma once
#include "NS4GFX/GfxBridge.h"
#include "NS4GFX/ASSymbolRegistry.h"
#include <string>
#include <vector>

namespace NS4GFX { namespace Categories {
namespace AdventureWorld {
std::vector<const ASSymbol*> Symbols();
bool Invoke(const std::string& movie, const std::string& path, const std::string& method, const std::vector<std::string>& args = {});
bool SetText(const std::string& movie, const std::string& path, const std::string& text);
}
namespace BattleHUD {
std::vector<const ASSymbol*> Symbols();
bool Invoke(const std::string& movie, const std::string& path, const std::string& method, const std::vector<std::string>& args = {});
bool SetText(const std::string& movie, const std::string& path, const std::string& text);
}
namespace CharacterSelect {
std::vector<const ASSymbol*> Symbols();
bool Invoke(const std::string& movie, const std::string& path, const std::string& method, const std::vector<std::string>& args = {});
bool SetText(const std::string& movie, const std::string& path, const std::string& text);
}
namespace CommonWidgets {
std::vector<const ASSymbol*> Symbols();
bool Invoke(const std::string& movie, const std::string& path, const std::string& method, const std::vector<std::string>& args = {});
bool SetText(const std::string& movie, const std::string& path, const std::string& text);
}
namespace Misc {
std::vector<const ASSymbol*> Symbols();
bool Invoke(const std::string& movie, const std::string& path, const std::string& method, const std::vector<std::string>& args = {});
bool SetText(const std::string& movie, const std::string& path, const std::string& text);
}
namespace Online {
std::vector<const ASSymbol*> Symbols();
bool Invoke(const std::string& movie, const std::string& path, const std::string& method, const std::vector<std::string>& args = {});
bool SetText(const std::string& movie, const std::string& path, const std::string& text);
}
namespace Settings {
std::vector<const ASSymbol*> Symbols();
bool Invoke(const std::string& movie, const std::string& path, const std::string& method, const std::vector<std::string>& args = {});
bool SetText(const std::string& movie, const std::string& path, const std::string& text);
}
namespace StageSelect {
std::vector<const ASSymbol*> Symbols();
bool Invoke(const std::string& movie, const std::string& path, const std::string& method, const std::vector<std::string>& args = {});
bool SetText(const std::string& movie, const std::string& path, const std::string& text);
}
namespace System {
std::vector<const ASSymbol*> Symbols();
bool Invoke(const std::string& movie, const std::string& path, const std::string& method, const std::vector<std::string>& args = {});
bool SetText(const std::string& movie, const std::string& path, const std::string& text);
}
} }
