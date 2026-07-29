#pragma once

#include <cstdint>

namespace PopupReverseMap
{
    // All RVAs are for the currently reversed Naruto Storm Connections executable build.
    // Keep this file boring on purpose: it is documentation plus a single source of truth for wrappers.
    namespace Flash
    {
        constexpr uintptr_t CreateInstance = 0x71E2D0;       // ccUiFlash::CreateInstance / load SWF
        constexpr uintptr_t CallNoArgs = 0x71F110;           // Scaleform invoke, no args
        constexpr uintptr_t CallReturn = 0x71F250;           // Scaleform invoke, return value
        constexpr uintptr_t CallArgs = 0x71F390;             // Scaleform invoke, args
        constexpr uintptr_t BaseCtor = 0x71DE20;             // ccUiFlash ctor
        constexpr uintptr_t BaseDtor = 0x71E140;             // ccUiFlash dtor
        constexpr uintptr_t UnloadAll = 0x71E7B0;            // unload/reset flash tree
        constexpr uintptr_t CreateUpdateTask = 0x71EA90;     // ccUiFlash::Update task
    }

    namespace Dialog
    {
        constexpr uintptr_t Ctor = 0x763340;                 // ccUiFlashDialog ctor
        constexpr uintptr_t Create = 0x763B50;               // create msg window
        constexpr uintptr_t Open = 0x764040;                 // OpenWindow
        constexpr uintptr_t SetMessageText = 0x764220;       // SetMessageText
        constexpr uintptr_t SetVisible = 0x764370;           // SetVisible
        constexpr uintptr_t PumpVisibility = 0x7636A0;       // dialog task visibility pump
        constexpr uintptr_t CloseTask = 0x7638F0;            // click/confirm close task
    }

    namespace SelectWindow
    {
        constexpr uintptr_t Ctor = 0x800C50;                 // ccUiFlashSelectWindow ctor
        constexpr uintptr_t RegisterCallbacks = 0x800A70;    // ChangeAnimLoop, OnMouseClicked, etc.
        constexpr uintptr_t Open = 0x801FD0;                 // OpenWindow + EntryOnFrameUpdate
        constexpr uintptr_t GetResult = 0x801E80;            // returns result at +464
        constexpr uintptr_t SetButtons = 0x802210;           // SetSelectParam helper
        constexpr uintptr_t SetLine = 0x8034F0;              // SetLine
        constexpr uintptr_t SetTitle = 0x803640;             // SetWindowTitle
        constexpr uintptr_t VisibilityTask = 0x801980;       // SetVisibleWindow pump
    }

    namespace Fade
    {
        constexpr uintptr_t Busy = 0x7741F0;                 // GetFadeAlpha / busy check
        constexpr uintptr_t Finished = 0x7741D0;             // fade finished check
        constexpr uintptr_t SetColor = 0x7742C0;             // set white/black/custom fade mode
        constexpr uintptr_t Start = 0x7744D0;                // start fadeInOut duration
    }

    namespace SelectionController
    {
        constexpr uintptr_t Ctor = 0x108A110;
        constexpr uintptr_t Bind = 0x108A8C0;
        constexpr uintptr_t SetDisplayCount = 0x108A8A0;
        constexpr uintptr_t SetOptionCount = 0x108AC10;
        constexpr uintptr_t SetDefaultSelection = 0x108AC30;
    }

    namespace CharacterSelect
    {
        constexpr uintptr_t SetCharacter = 0x17CC00;         // SetCharacter on free battle/select UI
        constexpr uintptr_t SetItemText = 0x1789E0;          // list text setter style helper
        constexpr uintptr_t LoadAccessoryOrSubstitution = 0x1755F0;
        constexpr uintptr_t CopyUiStringA = 0x181FC0;
        constexpr uintptr_t CopyUiStringB = 0x182080;
    }

    namespace ScaleformCallbacks
    {
        // Registered in ccUiFlashSelectWindow via RegisterCallbacks.
        constexpr const char* ChangeAnimLoop = "ChangeAnimLoop";
        constexpr const char* ChangeAnimClosed = "ChangeAnimClosed";
        constexpr const char* GetSelValue = "GetSelValue";
        constexpr const char* GetDispNo = "GetDispNo";
        constexpr const char* GetDispSelValue = "GetDispSelValue";
        constexpr const char* OnMouseClicked = "OnMouseClicked";
        constexpr const char* OnMouseMoved = "OnMouseMoved";
    }

    namespace ScaleformMethods
    {
        constexpr const char* CreateSelectWindow = "CreateSelectWindow";
        constexpr const char* CreateMsgWindow = "CreateMsgWindow";
        constexpr const char* OpenWindow = "OpenWindow";
        constexpr const char* CloseWindow = "CloseWindow";
        constexpr const char* SetMessageText = "SetMessageText";
        constexpr const char* SetWindowTitle = "SetWindowTitle";
        constexpr const char* SetVisible = "SetVisible";
        constexpr const char* SetVisibleWindow = "SetVisibleWindow";
        constexpr const char* SetEnableWordWrap = "SetEnableWordWrap";
        constexpr const char* SetLine = "SetLine";
        constexpr const char* SetCharacter = "SetCharacter";
    }
}
