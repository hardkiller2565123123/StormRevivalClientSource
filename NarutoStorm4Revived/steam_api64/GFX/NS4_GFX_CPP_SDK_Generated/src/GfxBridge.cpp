#include "NS4GFX/GfxBridge.h"

namespace NS4GFX {
static NullGfxBridge g_nullBridge;
static IGfxBridge* g_bridge = &g_nullBridge;
void SetBridge(IGfxBridge* bridge) { g_bridge = bridge ? bridge : &g_nullBridge; }
IGfxBridge& Bridge() { return *g_bridge; }
}
