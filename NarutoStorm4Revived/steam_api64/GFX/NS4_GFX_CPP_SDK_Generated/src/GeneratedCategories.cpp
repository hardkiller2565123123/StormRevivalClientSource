#include "NS4GFX/GeneratedCategories.h"

namespace NS4GFX { namespace Categories {
namespace AdventureWorld {
std::vector<const ASSymbol*> Symbols() { size_t n=0; const ASSymbol* all=GetAllSymbols(&n); std::vector<const ASSymbol*> out; for(size_t i=0;i<n;++i) if(std::string(all[i].category)=="AdventureWorld") out.push_back(&all[i]); return out; }
bool Invoke(const std::string& movie, const std::string& path, const std::string& method, const std::vector<std::string>& args) { return Bridge().Invoke(movie,path,method,args); }
bool SetText(const std::string& movie, const std::string& path, const std::string& text) { return Bridge().SetText(movie,path,text); }
}
namespace BattleHUD {
std::vector<const ASSymbol*> Symbols() { size_t n=0; const ASSymbol* all=GetAllSymbols(&n); std::vector<const ASSymbol*> out; for(size_t i=0;i<n;++i) if(std::string(all[i].category)=="BattleHUD") out.push_back(&all[i]); return out; }
bool Invoke(const std::string& movie, const std::string& path, const std::string& method, const std::vector<std::string>& args) { return Bridge().Invoke(movie,path,method,args); }
bool SetText(const std::string& movie, const std::string& path, const std::string& text) { return Bridge().SetText(movie,path,text); }
}
namespace CharacterSelect {
std::vector<const ASSymbol*> Symbols() { size_t n=0; const ASSymbol* all=GetAllSymbols(&n); std::vector<const ASSymbol*> out; for(size_t i=0;i<n;++i) if(std::string(all[i].category)=="CharacterSelect") out.push_back(&all[i]); return out; }
bool Invoke(const std::string& movie, const std::string& path, const std::string& method, const std::vector<std::string>& args) { return Bridge().Invoke(movie,path,method,args); }
bool SetText(const std::string& movie, const std::string& path, const std::string& text) { return Bridge().SetText(movie,path,text); }
}
namespace CommonWidgets {
std::vector<const ASSymbol*> Symbols() { size_t n=0; const ASSymbol* all=GetAllSymbols(&n); std::vector<const ASSymbol*> out; for(size_t i=0;i<n;++i) if(std::string(all[i].category)=="CommonWidgets") out.push_back(&all[i]); return out; }
bool Invoke(const std::string& movie, const std::string& path, const std::string& method, const std::vector<std::string>& args) { return Bridge().Invoke(movie,path,method,args); }
bool SetText(const std::string& movie, const std::string& path, const std::string& text) { return Bridge().SetText(movie,path,text); }
}
namespace Misc {
std::vector<const ASSymbol*> Symbols() { size_t n=0; const ASSymbol* all=GetAllSymbols(&n); std::vector<const ASSymbol*> out; for(size_t i=0;i<n;++i) if(std::string(all[i].category)=="Misc") out.push_back(&all[i]); return out; }
bool Invoke(const std::string& movie, const std::string& path, const std::string& method, const std::vector<std::string>& args) { return Bridge().Invoke(movie,path,method,args); }
bool SetText(const std::string& movie, const std::string& path, const std::string& text) { return Bridge().SetText(movie,path,text); }
}
namespace Online {
std::vector<const ASSymbol*> Symbols() { size_t n=0; const ASSymbol* all=GetAllSymbols(&n); std::vector<const ASSymbol*> out; for(size_t i=0;i<n;++i) if(std::string(all[i].category)=="Online") out.push_back(&all[i]); return out; }
bool Invoke(const std::string& movie, const std::string& path, const std::string& method, const std::vector<std::string>& args) { return Bridge().Invoke(movie,path,method,args); }
bool SetText(const std::string& movie, const std::string& path, const std::string& text) { return Bridge().SetText(movie,path,text); }
}
namespace Settings {
std::vector<const ASSymbol*> Symbols() { size_t n=0; const ASSymbol* all=GetAllSymbols(&n); std::vector<const ASSymbol*> out; for(size_t i=0;i<n;++i) if(std::string(all[i].category)=="Settings") out.push_back(&all[i]); return out; }
bool Invoke(const std::string& movie, const std::string& path, const std::string& method, const std::vector<std::string>& args) { return Bridge().Invoke(movie,path,method,args); }
bool SetText(const std::string& movie, const std::string& path, const std::string& text) { return Bridge().SetText(movie,path,text); }
}
namespace StageSelect {
std::vector<const ASSymbol*> Symbols() { size_t n=0; const ASSymbol* all=GetAllSymbols(&n); std::vector<const ASSymbol*> out; for(size_t i=0;i<n;++i) if(std::string(all[i].category)=="StageSelect") out.push_back(&all[i]); return out; }
bool Invoke(const std::string& movie, const std::string& path, const std::string& method, const std::vector<std::string>& args) { return Bridge().Invoke(movie,path,method,args); }
bool SetText(const std::string& movie, const std::string& path, const std::string& text) { return Bridge().SetText(movie,path,text); }
}
namespace System {
std::vector<const ASSymbol*> Symbols() { size_t n=0; const ASSymbol* all=GetAllSymbols(&n); std::vector<const ASSymbol*> out; for(size_t i=0;i<n;++i) if(std::string(all[i].category)=="System") out.push_back(&all[i]); return out; }
bool Invoke(const std::string& movie, const std::string& path, const std::string& method, const std::vector<std::string>& args) { return Bridge().Invoke(movie,path,method,args); }
bool SetText(const std::string& movie, const std::string& path, const std::string& text) { return Bridge().SetText(movie,path,text); }
}
} }
