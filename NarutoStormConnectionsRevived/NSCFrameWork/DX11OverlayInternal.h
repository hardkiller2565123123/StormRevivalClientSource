#pragma once

#include "StdInc.h"

#include "DX11OverlayState.h"

#include "Logger.h"
#include "NS2Config.h"
#include "AssetBrowser.h"
#include "AssetPreview.h"
#include "AssetModelViewer.h"
#include "CpkArchive.h"
#include "ModRedirector.h"
#include "AssetPreloadManager.h"
#include "LuaManager.h"
#include "AssetRelations.h"
#include "XfbinInspector.h"
#include "AssetHash.h"
#include "AssetNotification.h"
#include "AssetOverrideManager.h"
#include "AssetHexEditor.h"
#include "AssetReport.h"
#include "AssetPackageCreator.h"
#include "AssetFavorites.h"
#include "AssetDuplicateFinder.h"
#include "AssetConflictScanner.h"
#include "AssetBackupManager.h"
#include "AssetTextureInfo.h"
#include "AssetTexturePreview.h"
#include "AssetBulkExtractor.h"
#include "AssetToolkitUI.h"
#include "AssetSearchFilter.h"
#include "AssetPreviewResolver.h"
#include "OverlayConsole.h"
#include "LuaHooks.h"
#include "PatchManager.h"
#include "AssetTaskQueue.h"
#include "NS2Offsets.h"
#include "RuntimeHookBootstrap.h"

#include "imgui.h"

#include <d3d11.h>
#include <dxgi.h>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

bool ActiveCheckbox(const char* label, bool* value, const char* help);
bool PlannedCheckbox(const char* label, bool* value, const char* reason);
void DrawLeftButton(const char* label, int page);
bool IniCheckbox(const char* label, int& value);
bool IniCheckbox(const char* label, int& value, const char* help);
void HelpMarker(const char* text);
void ResolutionPreset(const char* label, int width, int height);

void DrawLuaScriptList(LuaManager::ScriptSource sourceFilter);
void DrawLuaPage();
void DrawGraphicsPage();
void DrawControlsPage();
void DrawModsPage();
void DrawCameraPage();
void DrawPatchesPage();
void DrawAssetsPage();

void DrawModelPreviewShell(const ImVec2& size);
