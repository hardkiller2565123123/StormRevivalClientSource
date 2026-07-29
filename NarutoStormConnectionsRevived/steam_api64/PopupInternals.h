#pragma once

#include "PopupTypes.h"
#include <Windows.h>
#include <cstdint>
#include <string>

namespace PopupInternals
{
    bool Init(uintptr_t gameBase);
    void Shutdown();
    uintptr_t Base();

    int64_t CreateBasicDialog(const char* name, PopupTypes::PopupKind kind, unsigned int flags = 0x42);
    bool SetDialogText(int64_t dialog, const char* text, bool localized);
    bool OpenDialog(int64_t dialog);
    bool SetDialogVisible(int64_t dialog, bool visible);
    bool CloseDialog(int64_t dialog);

    const char* GetDialogSwf(int64_t dialog);
    const char* GetDialogTarget(int64_t dialog);

    bool CallNoArgs(int64_t flashObject, const char* swfName, const char* target, const char* method);

    bool StartFade(int64_t flashObject, const PopupTypes::FadeRgb& color, int durationMs);
    bool IsFadeBusy(int64_t flashObject);

    PopupTypes::DialogResult GetDialogResult(int64_t selectDialog);

    const char* DialogResultName(PopupTypes::DialogResult result);
}
