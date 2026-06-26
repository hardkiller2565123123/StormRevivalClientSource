#include "OnlineMenuConfig.h"
namespace StormRevival::OnlineMenu::Config { Settings& Get(){ static Settings s; return s; } }
