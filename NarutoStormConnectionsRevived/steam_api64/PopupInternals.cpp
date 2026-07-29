#include "StdInc.h"
#include "PopupInternals.h"
#include "PopupReverseMap.h"
#include "Logger.h"

#include <Windows.h>
#include <cstdint>
#include <sstream>

namespace
{
    uintptr_t g_Base = 0;

    template <typename T>
    T Rva(uintptr_t rva)
    {
        return reinterpret_cast<T>(g_Base + rva);
    }

    using DialogCtor_t = int64_t(__fastcall*)(int64_t mem);
    using DialogCreate_t = int64_t(__fastcall*)(int64_t dialog, const char* name, int type, unsigned int flags);
    using DialogSetMessage_t = int64_t(__fastcall*)(int64_t dialog, const char* text, int localized);
    using DialogOpen_t = int64_t(__fastcall*)(int64_t dialog);
    using DialogVisible_t = int64_t(__fastcall*)(int64_t dialog, int visible);

    using CallNoArgs_t = void(__fastcall*)(int64_t flash, int64_t swf, int64_t target, int64_t method);

    using FadeBusy_t = bool(__fastcall*)(int64_t flash);
    using FadeSetColor_t = void(__fastcall*)(int64_t flash, const float* rgb);
    using FadeStart_t = int64_t(__fastcall*)(int64_t flash, int durationMs);

    using SelectGetResult_t = int64_t(__fastcall*)(int64_t dialog);

    DialogCtor_t pDialogCtor = nullptr;
    DialogCreate_t pDialogCreate = nullptr;
    DialogSetMessage_t pDialogSetMessage = nullptr;
    DialogOpen_t pDialogOpen = nullptr;
    DialogVisible_t pDialogVisible = nullptr;
    CallNoArgs_t pCallNoArgs = nullptr;
    FadeBusy_t pFadeBusy = nullptr;
    FadeSetColor_t pFadeSetColor = nullptr;
    FadeStart_t pFadeStart = nullptr;
    SelectGetResult_t pSelectGetResult = nullptr;

    void LogResolved(const char* name, uintptr_t rva)
    {
        std::ostringstream ss;
        ss << "PopupInternals: " << name << " rva=0x" << std::hex << rva
           << " addr=0x" << (g_Base + rva);
        Logger::Info(ss.str());
    }
}

namespace PopupInternals
{
    bool Init(uintptr_t gameBase)
    {
        if (!gameBase)
        {
            Logger::Error("PopupInternals: invalid game base");
            return false;
        }

        g_Base = gameBase;

        pDialogCtor = Rva<DialogCtor_t>(PopupReverseMap::Dialog::Ctor);
        pDialogCreate = Rva<DialogCreate_t>(PopupReverseMap::Dialog::Create);
        pDialogSetMessage = Rva<DialogSetMessage_t>(PopupReverseMap::Dialog::SetMessageText);
        pDialogOpen = Rva<DialogOpen_t>(PopupReverseMap::Dialog::Open);
        pDialogVisible = Rva<DialogVisible_t>(PopupReverseMap::Dialog::SetVisible);
        pCallNoArgs = Rva<CallNoArgs_t>(PopupReverseMap::Flash::CallNoArgs);
        pFadeBusy = Rva<FadeBusy_t>(PopupReverseMap::Fade::Busy);
        pFadeSetColor = Rva<FadeSetColor_t>(PopupReverseMap::Fade::SetColor);
        pFadeStart = Rva<FadeStart_t>(PopupReverseMap::Fade::Start);
        pSelectGetResult = Rva<SelectGetResult_t>(PopupReverseMap::SelectWindow::GetResult);

        LogResolved("DialogCtor", PopupReverseMap::Dialog::Ctor);
        LogResolved("DialogCreate", PopupReverseMap::Dialog::Create);
        LogResolved("DialogSetMessageText", PopupReverseMap::Dialog::SetMessageText);
        LogResolved("DialogOpen", PopupReverseMap::Dialog::Open);
        LogResolved("DialogSetVisible", PopupReverseMap::Dialog::SetVisible);
        LogResolved("CallNoArgs", PopupReverseMap::Flash::CallNoArgs);
        LogResolved("FadeBusy", PopupReverseMap::Fade::Busy);
        LogResolved("FadeSetColor", PopupReverseMap::Fade::SetColor);
        LogResolved("FadeStart", PopupReverseMap::Fade::Start);
        LogResolved("SelectGetResult", PopupReverseMap::SelectWindow::GetResult);

        Logger::Info("PopupInternals initialized with mapped NSC popup, fade, and select-window functions");
        return true;
    }

    void Shutdown()
    {
        g_Base = 0;
        pDialogCtor = nullptr;
        pDialogCreate = nullptr;
        pDialogSetMessage = nullptr;
        pDialogOpen = nullptr;
        pDialogVisible = nullptr;
        pCallNoArgs = nullptr;
        pFadeBusy = nullptr;
        pFadeSetColor = nullptr;
        pFadeStart = nullptr;
        pSelectGetResult = nullptr;
    }

    uintptr_t Base()
    {
        return g_Base;
    }

    int64_t CreateBasicDialog(const char* name, PopupTypes::PopupKind kind, unsigned int flags)
    {
        if (!pDialogCtor || !pDialogCreate)
            return 0;

        void* mem = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, 224);
        if (!mem)
        {
            Logger::Error("PopupInternals: HeapAlloc failed for ccUiFlashDialog");
            return 0;
        }

        int64_t dialog = pDialogCtor(reinterpret_cast<int64_t>(mem));
        if (!dialog)
        {
            Logger::Error("PopupInternals: dialog ctor returned null");
            return 0;
        }

        pDialogCreate(dialog, name ? name : "StormRevivalDialog", static_cast<int>(kind), flags);
        return dialog;
    }

    bool SetDialogText(int64_t dialog, const char* text, bool localized)
    {
        if (!dialog || !pDialogSetMessage || !text)
            return false;

        pDialogSetMessage(dialog, text, localized ? 1 : 0);
        return true;
    }

    bool OpenDialog(int64_t dialog)
    {
        if (!dialog || !pDialogOpen)
            return false;

        pDialogOpen(dialog);
        return true;
    }

    bool SetDialogVisible(int64_t dialog, bool visible)
    {
        if (!dialog || !pDialogVisible)
            return false;

        pDialogVisible(dialog, visible ? 1 : 0);
        return true;
    }

    const char* GetDialogSwf(int64_t dialog)
    {
        if (!dialog)
            return nullptr;

        const char* swf = reinterpret_cast<const char*>(dialog + 112);
        if (*reinterpret_cast<uint64_t*>(dialog + 136) >= 0x10)
            swf = *reinterpret_cast<const char**>(dialog + 112);

        return swf;
    }

    const char* GetDialogTarget(int64_t dialog)
    {
        if (!dialog)
            return nullptr;

        const char* target = reinterpret_cast<const char*>(dialog + 168);
        if (*reinterpret_cast<uint64_t*>(dialog + 192) >= 0x10)
            target = *reinterpret_cast<const char**>(dialog + 168);

        return target;
    }

    bool CallNoArgs(int64_t flashObject, const char* swfName, const char* target, const char* method)
    {
        if (!flashObject || !swfName || !target || !method || !pCallNoArgs)
            return false;

        pCallNoArgs(
            flashObject,
            reinterpret_cast<int64_t>(swfName),
            reinterpret_cast<int64_t>(target),
            reinterpret_cast<int64_t>(method));
        return true;
    }

    bool CloseDialog(int64_t dialog)
    {
        const char* swf = GetDialogSwf(dialog);
        const char* target = GetDialogTarget(dialog);
        return CallNoArgs(dialog, swf, target, PopupReverseMap::ScaleformMethods::CloseWindow);
    }

    bool StartFade(int64_t flashObject, const PopupTypes::FadeRgb& color, int durationMs)
    {
        if (!flashObject || !pFadeSetColor || !pFadeStart)
            return false;

        float rgb[3] = { color.r, color.g, color.b };
        pFadeSetColor(flashObject, rgb);
        pFadeStart(flashObject, durationMs);
        return true;
    }

    bool IsFadeBusy(int64_t flashObject)
    {
        if (!flashObject || !pFadeBusy)
            return false;

        return pFadeBusy(flashObject);
    }

    PopupTypes::DialogResult GetDialogResult(int64_t selectDialog)
    {
        if (!selectDialog || !pSelectGetResult)
            return PopupTypes::DialogResult::Waiting;

        return static_cast<PopupTypes::DialogResult>(pSelectGetResult(selectDialog));
    }

    const char* DialogResultName(PopupTypes::DialogResult result)
    {
        switch (result)
        {
        case PopupTypes::DialogResult::Waiting: return "Waiting";
        case PopupTypes::DialogResult::Accept: return "Accept";
        case PopupTypes::DialogResult::Cancel: return "Cancel";
        default: return "Unknown";
        }
    }
}
