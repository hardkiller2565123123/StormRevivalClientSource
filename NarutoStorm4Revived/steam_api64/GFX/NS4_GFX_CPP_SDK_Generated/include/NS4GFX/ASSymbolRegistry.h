#pragma once
#include <cstddef>

namespace NS4GFX {

struct ASStringList { const char* const* items; size_t count; };
struct ASSymbol {
    const char* file;
    const char* category;
    const char* packageName;
    const char* className;
    const char* baseClass;
    const char* const* methods;
    size_t methodCount;
    const char* const* variables;
    size_t variableCount;
    const char* const* callbacks;
    size_t callbackCount;
};

const ASSymbol* GetAllSymbols(size_t* count);
const ASSymbol* FindSymbolByFile(const char* file);
const ASSymbol* FindSymbolByClass(const char* className);
void ForEachSymbol(void (*fn)(const ASSymbol& symbol, void* user), void* user);

} // namespace NS4GFX
