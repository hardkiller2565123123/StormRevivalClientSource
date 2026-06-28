#include "EditorGUI.h"
#include <sstream>
#include "DirectX.h"
#include "UltimateStormAPI.h"
#include "Common.h"
#include <windows.h>
#include <cstdio>
using namespace std;
#include <iostream>
#include "ccCmnCamera.h"
#include "Utilities.h"
#include "ccPlayerMain.h"
#include <Xinput.h>
#include "MouseLook.h"
#include "Console.h"
#include "Offsets.h"
#include "MovesetPlus.h"
#include "CommonRender.h"
#include "imgui_internal.h"
#pragma comment(lib,"XInput.lib")
#pragma comment(lib,"Xinput9_1_0.lib")
XINPUT_STATE controller;

bool EditorGUI::Show = false;
bool EditorGUI::HideHudDuringUJ = false;
bool EditorGUI::showHelpWindow = false;
bool EditorGUI::WindowList[100];

#define editor_cameraWindow 2
#define editor_charselWindow 3
#define editor_colorRadial 4
#define editor_colorDirc 5
#define editor_colorConvert 6
#define editor_brigthContrast 7
#define editor_blurWindow 8
#define editor_glareWindow 9
#define editor_helpWindow 10
#define editor_playerOutput 11
#define editor_dynamicsDebug 12
#define editor_lightSettings 13
float EditorGUI::editor_cameraWindowPos[3];
float EditorGUI::editor_cameraWindowLook[3];
bool EditorGUI::editor_cameraWindowEnableCam = true;
int EditorGUI::editor_cameraWindowMode = 0;
ColorFilterDirectionalSettings EditorGUI::editor_colorFilterDirectional;
ColorFilterRadialSettings EditorGUI::editor_colorFilterRadial;
ColorConvertSettings EditorGUI::editor_colorConverter;
BrightnessContrastSettings EditorGUI::editor_brightnessContrast;
BlurSettings EditorGUI::editor_blur;
GlareSettings EditorGUI::editor_glareConfig;
LightShadowSettings EditorGUI::editor_lightShadow;
float editor_cameraWindowPlAngle = 0;
float editor_cameraWindowPlHeight = 400;
float editor_cameraWindowPlDistance = 600;
float editor_cameraWindowFov = 90;
void DrawRadialColorWindow(bool* p_open, int pl1_frame, int pl2_frame);
void DrawDirectionalColorWindow(bool* p_open, int pl1_frame, int pl2_frame);
void DrawColorConvertWindow(bool* p_open, int pl1_frame, int pl2_frame);
void DrawBrightnessContrastWindow(bool* p_open, int pl1_frame, int pl2_frame);
void DrawBlurWindow(bool* p_open, int pl1_frame, int pl2_frame);
void DrawGlareConfigWindow(bool* p_open, int pl1_frame, int pl2_frame);
void DrawDynamicsWindow(bool* p_open);
void DrawLightSettingsWindow(bool* p_open);
Vector3 editor_cameraWindowPlLookOffset = Vector3(0, 0, 100);
// Разрешить цепочку указателей: baseModule + baseOffset, затем последовательность offsets.
// Возвращает адрес конца цепочки или 0 при ошибке.
// Безопасное разрешение цепочки и чтение/запись — защищено от AV и проверяет оба порядка offsets.
// Требует <windows.h>, <vector>, <cstdint>

void ApplyPartnerHitRegister(uintptr_t partner, uintptr_t player, const char* gameVersion) {
    if (!gameVersion) return;

    if (std::strcmp(gameVersion, "1.60") == 0) {
        int partnerHitReg = *(int*)(partner + 0x10BA8);
        if (partnerHitReg != 0) {
            *(int*)(player + 0x10BAC) = partnerHitReg;
        }
    }
    else if (std::strcmp(gameVersion, "1.09") == 0) {
        int partnerHitReg = *(int*)(partner + 0x14054);
        if (partnerHitReg != 0) {
            *(int*)(player + 0x14058) = partnerHitReg;
        }
    }
}


// Утилиты чтения/записи 11 float подряд (без крашей)
static bool Read11Floats(uintptr_t baseAddr, float outVals[11])
{
    if (baseAddr == 0) return false;
    for (size_t i = 0; i < 11; ++i)
    {
        if (!Offset::SafeReadFloat(baseAddr + i * sizeof(float), outVals[i])) return false;
    }
    return true;
}
void EditorGUI::InitGUI()
{
	for (int x = 0; x < sizeof(WindowList); x++)
	{
		WindowList[x] = false;
	}
}
typedef char* (__fastcall* GetPlAnmNameFromId_t)(int a1);

struct PlayerAnmInfo {
    int frame = -1;
    int frameMax = -1;
    int planmId = -1;
    const char* animationName = "????";
    const char* plAnmName = "Unknown";
    const char* plActName = "Unknown";
    int plActId = -1;

    // Обновляет данные из ccPlayerMain* (использует moduleBase и GameVersion).
    // Опционально можно передать функцию GetPlAnmNameFromId; если nullptr — попробует таблицу по смещению 0x1543CC0.
    void Update(ccPlayerMain* pl, GetPlAnmNameFromId_t getNameFunc = nullptr) {
        if (!pl) {
            frame = frameMax = planmId = -1;
            plAnmName = "Unknown";
            return;
        }

        typedef __int64(__fastcall* ccPlayer_GetAnmFrame_t)(ccPlayerMain* a1);
        ccPlayer_GetAnmFrame_t fnGetFrame = nullptr;
        ccPlayer_GetAnmFrame_t fnGetFrameMax = nullptr;
        ccPlayer_GetAnmFrame_t fnGetPlAnmId = nullptr;
        ccPlayer_GetAnmFrame_t fnGetAnimationName = nullptr;

        if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
            fnGetFrame = reinterpret_cast<ccPlayer_GetAnmFrame_t>(moduleBase + 0x98ECA0);
            fnGetFrameMax = reinterpret_cast<ccPlayer_GetAnmFrame_t>(moduleBase + 0x98ECC0);
            fnGetPlAnmId = reinterpret_cast<ccPlayer_GetAnmFrame_t>(moduleBase + 0x98ECE0);
        }
        else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
            fnGetFrame = reinterpret_cast<ccPlayer_GetAnmFrame_t>(moduleBase + 0x77CEF8);
            fnGetFrameMax = reinterpret_cast<ccPlayer_GetAnmFrame_t>(moduleBase + 0x77CF18);
            fnGetPlAnmId = reinterpret_cast<ccPlayer_GetAnmFrame_t>(moduleBase + 0x77CF38);
        }

        if (fnGetFrame) frame = static_cast<int>(fnGetFrame(pl)); else frame = -1;
        if (fnGetFrameMax) frameMax = static_cast<int>(fnGetFrameMax(pl)); else frameMax = -1;
        if (fnGetPlAnmId) planmId = static_cast<int>(fnGetPlAnmId(pl)); else planmId = -1;
        animationName = ccPlayer::GetAnmName(pl);
        plActName = ccPlayer::GetActFuncName(pl);
        plActId = ccPlayer::GetActionID(pl);
        // resolve name
        if (getNameFunc) {
            char* tmp = getNameFunc(planmId);
            plAnmName = (tmp && *tmp) ? tmp : "Unknown";
        }

    }

    // возврат нормализованного кадра (нужно подать measuredFps и baseline)
    int GetNormalizedFrame(float measuredFps, float baselineFps) const {
        if (frame < 0) return -1;
        float mf = (measuredFps <= 0.0001f) ? 60.0f : measuredFps;
        float seconds = static_cast<float>(frame) / mf;
        return static_cast<int>(seconds * baselineFps + 0.5f);
    }
    int GetNormalizedFrameMax(float measuredFps, float baselineFps) const {
        if (frameMax < 0) return -1;
        float mf = (measuredFps <= 0.0001f) ? 60.0f : measuredFps;
        float seconds = static_cast<float>(frameMax) / mf;
        return static_cast<int>(seconds * baselineFps + 0.5f);
    }
};

void EditorGUI::LoopGUI()
{

    ccCmnCamera* camPtr = FrameworkHelpers::GetActiveCamera(); 
    // Poll controller state
    XINPUT_STATE controller = {};
    if (XInputGetState(0, &controller) != ERROR_SUCCESS)
    {
        ZeroMemory(&controller, sizeof(XINPUT_STATE)); // no controller connected
    }
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    ccPlayerMain* pl1 = BattleUtils::ccGame_GetPlayerLeader(0);
    ccPlayerMain* pl2 = BattleUtils::ccGame_GetPlayerLeader(1);


    int dispFrame1 = 0;
    int dispFrame2 = 0;
    int dispFrame1max = 0;
    int dispFrame2max = 0;

    


    if (pl1 && pl2) {

        // создаём и обновляем
        PlayerAnmInfo p1;
        PlayerAnmInfo p2;



        // Если у вас есть специфичная функция получения имени для версии 1.60/1.09, можно создать и передать её:
        GetPlAnmNameFromId_t getNameFunc = nullptr;
        if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
            getNameFunc = reinterpret_cast<GetPlAnmNameFromId_t>(moduleBase + 0x5915A0);
        }
        else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
            getNameFunc = reinterpret_cast<GetPlAnmNameFromId_t>(moduleBase + 0x529884);
        }

        p1.Update(pl1, getNameFunc);
        p2.Update(pl2, getNameFunc);

        //function for hiding HUD during ultimates
        if (pl1 && pl2 && HideHudDuringUJ) {
            int pl1_action_id = p1.plActId;
            int pl2_action_id = p2.plActId;
            if (pl1_action_id == 137 || pl2_action_id == 137) {
                MovesetPlus::me_hud_control(1);
            }
            if (pl1_action_id == 138 || pl2_action_id == 138) {
                MovesetPlus::me_hud_control(2);
            }
            if (p1.planmId == 128 || p2.planmId == 128) {

                MovesetPlus::me_hud_control(2);
            }
        }


        //Function for applying hit status from partner to leader
        ccPlayerMain* pl1_partner = ccPlayer::GetPartnerPointer(pl1);
        ccPlayerMain* pl2_partner = ccPlayer::GetPartnerPointer(pl2);
        if (pl1_partner) {

            ApplyPartnerHitRegister((uintptr_t)pl1_partner, (uintptr_t)pl1, GameVersion);
        }


        if (pl2_partner) {

            ApplyPartnerHitRegister((uintptr_t)pl2_partner, (uintptr_t)pl2, GameVersion);
        }

        int pl1_charID = ccPlayer::GetCharCodeID(pl1);
        int pl2_charID = ccPlayer::GetCharCodeID(pl2);
        int pl1_charCostumeID = ccPlayer::GetCharCodeCostumeID(pl1);
        int pl2_charCostumeID = ccPlayer::GetCharCodeCostumeID(pl2);
        const char* pl1_charCode = ccPlayer::GetCharCode(pl1_charID);
        const char* pl2_charCode = ccPlayer::GetCharCode(pl2_charID);
        const char* pl1_charCodeCostume = ccPlayer::GetCharCostumeCode(pl1_charID, pl1_charCostumeID);
        const char* pl2_charCodeCostume = ccPlayer::GetCharCostumeCode(pl2_charID, pl2_charCostumeID);

        int pl1_charState = ccPlayer::GetCharacterState(pl1);
        int pl2_charState = ccPlayer::GetCharacterState(pl2);
        MovesetPlus::CHARACODE[0] = pl1_charCode ? pl1_charCode : "DUMMY";
        MovesetPlus::CHARACODE[1] = pl2_charCode ? pl2_charCode : "DUMMY";




        // рисовать только если окно открыт и оба игрока существуют
        if (pl1 && pl2 && WindowList[editor_playerOutput]) {

            // создаём и обновляем
            PlayerAnmInfo p1;
            PlayerAnmInfo p2;

            // Если у вас есть специфичная функция получения имени для версии 1.60/1.09, можно создать и передать её:
            GetPlAnmNameFromId_t getNameFunc = nullptr;
            if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
                getNameFunc = reinterpret_cast<GetPlAnmNameFromId_t>(moduleBase + 0x5915A0);
            }
            else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
                getNameFunc = reinterpret_cast<GetPlAnmNameFromId_t>(moduleBase + 0x529884);
            }

            p1.Update(pl1, getNameFunc);
            p2.Update(pl2, getNameFunc);

            // рисовать только если окно открыт и оба игрока существуют
            if (pl1 && pl2 && WindowList[editor_playerOutput]) {

                // --- нарисовать белые метки в верхних углах ---
                ImGuiIO& io = ImGui::GetIO();
                ImDrawList* drawList = ImGui::GetForegroundDrawList();
                ImVec2 screenSize = io.DisplaySize;

                // нормализация
                const float BASELINE_FPS = 30.0f;
                float measuredFps = io.Framerate;
                if (measuredFps <= 0.0001f) measuredFps = 60.0f;

                dispFrame1 = p1.GetNormalizedFrame(measuredFps, BASELINE_FPS);
                dispFrame2 = p2.GetNormalizedFrame(measuredFps, BASELINE_FPS);
                dispFrame1max = p1.GetNormalizedFrameMax(measuredFps, BASELINE_FPS);
                dispFrame2max = p2.GetNormalizedFrameMax(measuredFps, BASELINE_FPS);
                const float topPadding = 20.0f; // отступ сверху
                const float innerLineSpacing = 4.0f;
                const float padding = 8.0f;
                const float pointerGapMultiplier = 5.5f; // <-- множитель для высоты отступа после pointer
                static bool showLabelsBackground = true; // переключатель (сохраняется между кадрами)
                // таблица имён состояний
                static const char* stateNames[] = {
                    "prm_mot",        // 0
                    "prm_awa",        // 1
                    "prm_upgrade01",  // 2
                    "prm_upgrade02",  // 3
                    "prm_upgrade03",  // 4
                    "prm_boss01",     // 5
                    "prm_boss02",     // 6
                    "prm_boss03",     // 7
                    "prm_boss04"      // 8
                };
                const int stateCount = static_cast<int>(sizeof(stateNames) / sizeof(stateNames[0]));

                // --- формируем строку State: name (id)
                char* pl1_state_name = (pl1_charState >= 0 && pl1_charState < stateCount) ? stateNames[pl1_charState] : "unknown";
                char* pl2_state_name = (pl2_charState >= 0 && pl2_charState < stateCount) ? stateNames[pl2_charState] : "unknown";


                // строки
                char bufPtrL[64]; std::snprintf(bufPtrL, sizeof(bufPtrL), "%p", static_cast<void*>(pl1));
                char bufPtrR[64]; std::snprintf(bufPtrR, sizeof(bufPtrR), "%p", static_cast<void*>(pl2));

                // --- добавляем строки с кодом персонажа и ID ---
                char bufCharInfoL[128]; std::snprintf(bufCharInfoL, sizeof(bufCharInfoL), "<%s(ID=%d)>", pl1_charCode ? pl1_charCode : "Unknown", pl1_charID);
                char bufCharInfoR[128]; std::snprintf(bufCharInfoR, sizeof(bufCharInfoR), "<%s(ID=%d)>", pl2_charCode ? pl2_charCode : "Unknown", pl2_charID);

                char bufCostumeL[128]; std::snprintf(bufCostumeL, sizeof(bufCostumeL), "Costume: %s (%d)", pl1_charCodeCostume ? pl1_charCodeCostume : "Unknown", pl1_charCostumeID);
                char bufCostumeR[128]; std::snprintf(bufCostumeR, sizeof(bufCostumeR), "Costume: %s (%d)", pl2_charCodeCostume ? pl2_charCodeCostume : "Unknown", pl2_charCostumeID);

                char bufCharStateInfoL[128];
                std::snprintf(bufCharStateInfoL, sizeof(bufCharStateInfoL), "State: %s (%d)", pl1_state_name, pl1_charState);

                char bufCharStateInfoR[128];
                std::snprintf(bufCharStateInfoR, sizeof(bufCharStateInfoR), "State: %s (%d)", pl2_state_name, pl2_charState);

                // существующие строки Frame / Act / Animation / PLAct
                char bufFrameL[128]; std::snprintf(bufFrameL, sizeof(bufFrameL), "Frame: %d / %d", dispFrame1, dispFrame1max);
                char bufFrameR[128]; std::snprintf(bufFrameR, sizeof(bufFrameR), "Frame: %d / %d", dispFrame2, dispFrame2max);

                char bufActL[256]; std::snprintf(bufActL, sizeof(bufActL), "%s (%d) ", p1.plAnmName ? p1.plAnmName : "Unknown", p1.planmId);
                char bufActR[256]; std::snprintf(bufActR, sizeof(bufActR), "%s (%d)", p2.plAnmName ? p2.plAnmName : "Unknown", p2.planmId);

                char bufAnmL[256]; std::snprintf(bufAnmL, sizeof(bufAnmL), "Animation: %s", p1.animationName);
                char bufAnmR[256]; std::snprintf(bufAnmR, sizeof(bufAnmR), "Animation: %s", p2.animationName);
                char bufPLActL[256]; std::snprintf(bufPLActL, sizeof(bufPLActL), "Action: %s (%d)", p1.plActName ? p1.plActName : "Unknown", p1.plActId);
                char bufPLActR[256]; std::snprintf(bufPLActR, sizeof(bufPLActR), "Action: %s (%d)", p2.plActName ? p2.plActName : "Unknown", p2.plActId);

                // --- вычисление размеров строк ---
                ImVec2 sizePtrL = ImGui::CalcTextSize(bufPtrL);
                ImVec2 sizePtrR = ImGui::CalcTextSize(bufPtrR);

                ImVec2 sizeCharInfoL = ImGui::CalcTextSize(bufCharInfoL);
                ImVec2 sizeCharInfoR = ImGui::CalcTextSize(bufCharInfoR);

                ImVec2 sizeCostumeL = ImGui::CalcTextSize(bufCostumeL);
                ImVec2 sizeCostumeR = ImGui::CalcTextSize(bufCostumeR);

                ImVec2 sizeCharStateInfoL = ImGui::CalcTextSize(bufCharStateInfoL);
                ImVec2 sizeCharStateInfoR = ImGui::CalcTextSize(bufCharStateInfoR);

                ImVec2 sizeFrameL = ImGui::CalcTextSize(bufFrameL);
                ImVec2 sizeFrameR = ImGui::CalcTextSize(bufFrameR);

                ImVec2 sizeActL = ImGui::CalcTextSize(bufActL);
                ImVec2 sizeActR = ImGui::CalcTextSize(bufActR);

                ImVec2 sizeAnmL = ImGui::CalcTextSize(bufAnmL);
                ImVec2 sizeAnmR = ImGui::CalcTextSize(bufAnmR);

                ImVec2 sizePLActL = ImGui::CalcTextSize(bufPLActL);
                ImVec2 sizePLActR = ImGui::CalcTextSize(bufPLActR);

                // ширина колонок учитывает и charInfo + state
                float rightMaxW = max(sizePtrR.x, max(sizeCharInfoR.x, max(sizeCostumeR.x, max(sizeCharStateInfoR.x, max(sizeFrameR.x, max(sizeActR.x, max(sizeAnmR.x, sizePLActR.x)))))));
                float leftMaxW = max(sizePtrL.x, max(sizeCharInfoL.x, max(sizeCostumeL.x, max(sizeCharStateInfoL.x, max(sizeFrameL.x, max(sizeActL.x, max(sizeAnmL.x, sizePLActL.x)))))));

                // параметры для отступов
                const float inputTextHeight = ImGui::GetFrameHeight();
                const float pointerGap = innerLineSpacing * pointerGapMultiplier;

                // позиции колонок: Pointer -> CharInfo -> State -> Frame -> Act -> PLAct -> Animation
                ImVec2 posLeftPtr = ImVec2(padding, topPadding);
                ImVec2 posLeftChar = ImVec2(padding, posLeftPtr.y + inputTextHeight + pointerGap);
                // Add costume position
                ImVec2 posLeftCostume = ImVec2(padding, posLeftChar.y + sizeCharInfoL.y + innerLineSpacing);
                // Update all positions below to use costume instead of char
                ImVec2 posLeftState = ImVec2(padding, posLeftCostume.y + sizeCostumeL.y + innerLineSpacing);
                ImVec2 posLeftFrame = ImVec2(padding, posLeftState.y + sizeCharStateInfoL.y + innerLineSpacing);
                ImVec2 posLeftAct = ImVec2(padding, posLeftFrame.y + sizeFrameL.y + innerLineSpacing);
                ImVec2 posLeftPLAct = ImVec2(padding, posLeftAct.y + sizeActL.y + innerLineSpacing);
                ImVec2 posLeftAnmBelow = ImVec2(padding, posLeftPLAct.y + sizePLActL.y + innerLineSpacing);

                ImVec2 posRightPtr = ImVec2(io.DisplaySize.x - rightMaxW - padding, topPadding);
                ImVec2 posRightChar = ImVec2(posRightPtr.x, posRightPtr.y + inputTextHeight + pointerGap);
                // Add costume position
                ImVec2 posRightCostume = ImVec2(posRightPtr.x, posRightChar.y + sizeCharInfoR.y + innerLineSpacing);
                // Update all positions below
                ImVec2 posRightState = ImVec2(posRightPtr.x, posRightCostume.y + sizeCostumeR.y + innerLineSpacing);
                ImVec2 posRightFrame = ImVec2(posRightPtr.x, posRightState.y + sizeCharStateInfoR.y + innerLineSpacing);
                ImVec2 posRightAct = ImVec2(posRightPtr.x, posRightFrame.y + sizeFrameR.y + innerLineSpacing);
                ImVec2 posRightPLAct = ImVec2(posRightPtr.x, posRightAct.y + sizeActR.y + innerLineSpacing);
                ImVec2 posRightAnmBelow = ImVec2(posRightPtr.x, posRightPLAct.y + sizePLActR.y + innerLineSpacing);

                // фоновые прямоугольники (учтём нижнюю строку animation)
                if (showLabelsBackground) {
                    ImU32 bgCol = IM_COL32(0, 0, 0, 160);
                    ImU32 borderCol = IM_COL32(255, 255, 255, 60);
                    float padInside = 6.0f;
                    float rounding = 6.0f;

                    ImVec2 leftRectMin = ImVec2(posLeftPtr.x - padInside, posLeftPtr.y - padInside);
                    ImVec2 leftRectMax = ImVec2(posLeftPtr.x + leftMaxW + padInside, posLeftAnmBelow.y + sizeAnmL.y + padInside);

                    ImDrawList* bgDraw = ImGui::GetBackgroundDrawList();
                    bgDraw->AddRectFilled(leftRectMin, leftRectMax, bgCol, rounding);
                    bgDraw->AddRect(leftRectMin, leftRectMax, borderCol, rounding, 0, 1.0f);

                    ImVec2 rightRectMin = ImVec2(posRightPtr.x - padInside, posRightPtr.y - padInside);
                    ImVec2 rightRectMax = ImVec2(posRightPtr.x + rightMaxW + padInside, posRightAnmBelow.y + sizeAnmR.y + padInside);

                    bgDraw->AddRectFilled(rightRectMin, rightRectMax, bgCol, rounding);
                    bgDraw->AddRect(rightRectMin, rightRectMax, borderCol, rounding, 0, 1.0f);
                }

                // рисуем: CharInfo -> State -> Frame -> Act -> PLAct -> Animation
                drawList->AddText(posLeftChar, IM_COL32(255, 255, 255, 255), bufCharInfoL);
                drawList->AddText(posLeftCostume, IM_COL32(255, 255, 255, 255), bufCostumeL);
                drawList->AddText(posLeftState, IM_COL32(255, 255, 255, 255), bufCharStateInfoL);
                drawList->AddText(posLeftFrame, IM_COL32(255, 255, 255, 255), bufFrameL);
                drawList->AddText(posLeftAct, IM_COL32(255, 255, 255, 255), bufActL);
                drawList->AddText(posLeftPLAct, IM_COL32(255, 255, 255, 255), bufPLActL);
                drawList->AddText(posLeftAnmBelow, IM_COL32(255, 255, 255, 255), bufAnmL);

                drawList->AddText(posRightChar, IM_COL32(255, 255, 255, 255), bufCharInfoR);
                drawList->AddText(posRightCostume, IM_COL32(255, 255, 255, 255), bufCostumeR);
                drawList->AddText(posRightState, IM_COL32(255, 255, 255, 255), bufCharStateInfoR);
                drawList->AddText(posRightFrame, IM_COL32(255, 255, 255, 255), bufFrameR);
                drawList->AddText(posRightAct, IM_COL32(255, 255, 255, 255), bufActR);
                drawList->AddText(posRightPLAct, IM_COL32(255, 255, 255, 255), bufPLActR);
                drawList->AddText(posRightAnmBelow, IM_COL32(255, 255, 255, 255), bufAnmR);


                // --- Pointer windows (top) — InputText ReadOnly для копирования ---
                ImGuiWindowFlags flags =
                    ImGuiWindowFlags_NoTitleBar |
                    ImGuiWindowFlags_NoResize |
                    ImGuiWindowFlags_AlwaysAutoResize |
                    ImGuiWindowFlags_NoSavedSettings |
                    ImGuiWindowFlags_NoFocusOnAppearing |
                    ImGuiWindowFlags_NoMove;

                // Левый pointer
                {
                    ImGui::SetNextWindowPos(posLeftPtr, ImGuiCond_Always);
                    ImGui::SetNextWindowBgAlpha(0.0f);
                    ImGui::Begin("##ptr_win_L", nullptr, flags);
                    ImGui::PushItemWidth(leftMaxW - 12.0f);
                    char leftBuf[64]; std::memset(leftBuf, 0, sizeof(leftBuf)); std::strncpy(leftBuf, bufPtrL, sizeof(leftBuf) - 1);
                    ImGui::InputText("##ptr_left", leftBuf, sizeof(leftBuf), ImGuiInputTextFlags_ReadOnly | ImGuiInputTextFlags_AutoSelectAll);
                    ImGui::PopItemWidth();
                    ImGui::End();
                }

                // Правый pointer
                {
                    ImGui::SetNextWindowPos(posRightPtr, ImGuiCond_Always);
                    ImGui::SetNextWindowBgAlpha(0.0f);
                    ImGui::Begin("##ptr_win_R", nullptr, flags);
                    ImGui::PushItemWidth(rightMaxW - 12.0f);
                    char rightBuf[64]; std::memset(rightBuf, 0, sizeof(rightBuf)); std::strncpy(rightBuf, bufPtrR, sizeof(rightBuf) - 1);
                    ImGui::InputText("##ptr_right", rightBuf, sizeof(rightBuf), ImGuiInputTextFlags_ReadOnly | ImGuiInputTextFlags_AutoSelectAll);
                    ImGui::PopItemWidth();
                    ImGui::End();
                }

                // --- PARTNER DISPLAY SECTION ---
                if (pl1_partner || pl2_partner) {
                    // Gap between player and partner displays
                    const float partnerGap = 30.0f;

                    // Calculate starting Y position for partners (below player displays)
                    float partnerStartY = posLeftAnmBelow.y + sizeAnmL.y + partnerGap;

                    // Partner info structures
                    PlayerAnmInfo p1_partner_info;
                    PlayerAnmInfo p2_partner_info;

                    if (pl1_partner) {
                        p1_partner_info.Update(pl1_partner, getNameFunc);
                    }

                    if (pl2_partner) {
                        p2_partner_info.Update(pl2_partner, getNameFunc);
                    }

                    // Get partner character info
                    int pl1_partner_charID = pl1_partner ? ccPlayer::GetCharCodeID(pl1_partner) : -1;
                    int pl2_partner_charID = pl2_partner ? ccPlayer::GetCharCodeID(pl2_partner) : -1;
                    int pl1_partner_charCostumeID = pl1_partner ? ccPlayer::GetCharCodeCostumeID(pl1_partner) : -1;
                    int pl2_partner_charCostumeID = pl2_partner ? ccPlayer::GetCharCodeCostumeID(pl2_partner) : -1;
                    const char* pl1_partner_charCode = pl1_partner ? ccPlayer::GetCharCode(pl1_partner_charID) : nullptr;
                    const char* pl2_partner_charCode = pl2_partner ? ccPlayer::GetCharCode(pl2_partner_charID) : nullptr;
                    const char* pl1_partner_charCodeCostume = pl1_partner ? ccPlayer::GetCharCostumeCode(pl1_partner_charID, pl1_partner_charCostumeID) : nullptr;
                    const char* pl2_partner_charCodeCostume = pl2_partner ? ccPlayer::GetCharCostumeCode(pl2_partner_charID, pl2_partner_charCostumeID) : nullptr;

                    int pl1_partner_charState = pl1_partner ? ccPlayer::GetCharacterState(pl1_partner) : -1;
                    int pl2_partner_charState = pl2_partner ? ccPlayer::GetCharacterState(pl2_partner) : -1;

                    // Partner frames
                    int dispFrame1_partner = 0, dispFrame1max_partner = 0;
                    int dispFrame2_partner = 0, dispFrame2max_partner = 0;

                    if (pl1_partner) {
                        dispFrame1_partner = p1_partner_info.GetNormalizedFrame(measuredFps, BASELINE_FPS);
                        dispFrame1max_partner = p1_partner_info.GetNormalizedFrameMax(measuredFps, BASELINE_FPS);
                    }
                    if (pl2_partner) {
                        dispFrame2_partner = p2_partner_info.GetNormalizedFrame(measuredFps, BASELINE_FPS);
                        dispFrame2max_partner = p2_partner_info.GetNormalizedFrameMax(measuredFps, BASELINE_FPS);
                    }

                    // State names
                    char* pl1_partner_state_name = (pl1_partner_charState >= 0 && pl1_partner_charState < stateCount) ? stateNames[pl1_partner_charState] : "unknown";
                    char* pl2_partner_state_name = (pl2_partner_charState >= 0 && pl2_partner_charState < stateCount) ? stateNames[pl2_partner_charState] : "unknown";

                    // Build strings for left partner
                    char bufPtrL_partner[64]; std::snprintf(bufPtrL_partner, sizeof(bufPtrL_partner), "%p", static_cast<void*>(pl1_partner));
                    char bufCharInfoL_partner[128]; std::snprintf(bufCharInfoL_partner, sizeof(bufCharInfoL_partner), "<%s(ID=%d)>", pl1_partner_charCode ? pl1_partner_charCode : "Unknown", pl1_partner_charID);
                    char bufCostumeL_partner[128]; std::snprintf(bufCostumeL_partner, sizeof(bufCostumeL_partner), "Costume: %s (%d)", pl1_partner_charCodeCostume ? pl1_partner_charCodeCostume : "Unknown", pl1_partner_charCostumeID);
                    char bufCharStateInfoL_partner[128]; std::snprintf(bufCharStateInfoL_partner, sizeof(bufCharStateInfoL_partner), "State: %s (%d)", pl1_partner_state_name, pl1_partner_charState);
                    char bufFrameL_partner[128]; std::snprintf(bufFrameL_partner, sizeof(bufFrameL_partner), "Frame: %d / %d", dispFrame1_partner, dispFrame1max_partner);
                    char bufActL_partner[256]; std::snprintf(bufActL_partner, sizeof(bufActL_partner), "%s (%d) ", pl1_partner ? (p1_partner_info.plAnmName ? p1_partner_info.plAnmName : "Unknown") : "N/A", pl1_partner ? p1_partner_info.planmId : -1);
                    char bufAnmL_partner[256]; std::snprintf(bufAnmL_partner, sizeof(bufAnmL_partner), "Animation: %s", pl1_partner ? p1_partner_info.animationName : "N/A");
                    char bufPLActL_partner[256]; std::snprintf(bufPLActL_partner, sizeof(bufPLActL_partner), "Action: %s (%d)", pl1_partner ? (p1_partner_info.plActName ? p1_partner_info.plActName : "Unknown") : "N/A", pl1_partner ? p1_partner_info.plActId : -1);

                    // Build strings for right partner
                    char bufPtrR_partner[64]; std::snprintf(bufPtrR_partner, sizeof(bufPtrR_partner), "%p", static_cast<void*>(pl2_partner));
                    char bufCharInfoR_partner[128]; std::snprintf(bufCharInfoR_partner, sizeof(bufCharInfoR_partner), "<%s(ID=%d)>", pl2_partner_charCode ? pl2_partner_charCode : "Unknown", pl2_partner_charID);
                    char bufCostumeR_partner[128]; std::snprintf(bufCostumeR_partner, sizeof(bufCostumeR_partner), "Costume: %s (%d)", pl2_partner_charCodeCostume ? pl2_partner_charCodeCostume : "Unknown", pl2_partner_charCostumeID);
                    char bufCharStateInfoR_partner[128]; std::snprintf(bufCharStateInfoR_partner, sizeof(bufCharStateInfoR_partner), "State: %s (%d)", pl2_partner_state_name, pl2_partner_charState);
                    char bufFrameR_partner[128]; std::snprintf(bufFrameR_partner, sizeof(bufFrameR_partner), "Frame: %d / %d", dispFrame2_partner, dispFrame2max_partner);
                    char bufActR_partner[256]; std::snprintf(bufActR_partner, sizeof(bufActR_partner), "%s (%d)", pl2_partner ? (p2_partner_info.plAnmName ? p2_partner_info.plAnmName : "Unknown") : "N/A", pl2_partner ? p2_partner_info.planmId : -1);
                    char bufAnmR_partner[256]; std::snprintf(bufAnmR_partner, sizeof(bufAnmR_partner), "Animation: %s", pl2_partner ? p2_partner_info.animationName : "N/A");
                    char bufPLActR_partner[256]; std::snprintf(bufPLActR_partner, sizeof(bufPLActR_partner), "Action: %s (%d)", pl2_partner ? (p2_partner_info.plActName ? p2_partner_info.plActName : "Unknown") : "N/A", pl2_partner ? p2_partner_info.plActId : -1);

                    // Calculate text sizes for partners
                    ImVec2 sizePtrL_partner = ImGui::CalcTextSize(bufPtrL_partner);
                    ImVec2 sizePtrR_partner = ImGui::CalcTextSize(bufPtrR_partner);
                    ImVec2 sizeCharInfoL_partner = ImGui::CalcTextSize(bufCharInfoL_partner);
                    ImVec2 sizeCharInfoR_partner = ImGui::CalcTextSize(bufCharInfoR_partner);
                    ImVec2 sizeCostumeL_partner = ImGui::CalcTextSize(bufCostumeL_partner);
                    ImVec2 sizeCostumeR_partner = ImGui::CalcTextSize(bufCostumeR_partner);
                    ImVec2 sizeCharStateInfoL_partner = ImGui::CalcTextSize(bufCharStateInfoL_partner);
                    ImVec2 sizeCharStateInfoR_partner = ImGui::CalcTextSize(bufCharStateInfoR_partner);
                    ImVec2 sizeFrameL_partner = ImGui::CalcTextSize(bufFrameL_partner);
                    ImVec2 sizeFrameR_partner = ImGui::CalcTextSize(bufFrameR_partner);
                    ImVec2 sizeActL_partner = ImGui::CalcTextSize(bufActL_partner);
                    ImVec2 sizeActR_partner = ImGui::CalcTextSize(bufActR_partner);
                    ImVec2 sizeAnmL_partner = ImGui::CalcTextSize(bufAnmL_partner);
                    ImVec2 sizeAnmR_partner = ImGui::CalcTextSize(bufAnmR_partner);
                    ImVec2 sizePLActL_partner = ImGui::CalcTextSize(bufPLActL_partner);
                    ImVec2 sizePLActR_partner = ImGui::CalcTextSize(bufPLActR_partner);

                    // Calculate max widths for partners
                    float rightMaxW_partner = max(sizePtrR_partner.x, max(sizeCharInfoR_partner.x, max(sizeCostumeR_partner.x, max(sizeCharStateInfoR_partner.x, max(sizeFrameR_partner.x, max(sizeActR_partner.x, max(sizeAnmR_partner.x, sizePLActR_partner.x)))))));
                    float leftMaxW_partner = max(sizePtrL_partner.x, max(sizeCharInfoL_partner.x, max(sizeCostumeL_partner.x, max(sizeCharStateInfoL_partner.x, max(sizeFrameL_partner.x, max(sizeActL_partner.x, max(sizeAnmL_partner.x, sizePLActL_partner.x)))))));

                    // Calculate positions for partner displays
                    ImVec2 posLeftPtr_partner = ImVec2(padding, partnerStartY);
                    ImVec2 posLeftChar_partner = ImVec2(padding, posLeftPtr_partner.y + inputTextHeight + pointerGap);
                    ImVec2 posLeftCostume_partner = ImVec2(padding, posLeftChar_partner.y + sizeCharInfoL_partner.y + innerLineSpacing);
                    ImVec2 posLeftState_partner = ImVec2(padding, posLeftCostume_partner.y + sizeCostumeL_partner.y + innerLineSpacing);
                    ImVec2 posLeftFrame_partner = ImVec2(padding, posLeftState_partner.y + sizeCharStateInfoL_partner.y + innerLineSpacing);
                    ImVec2 posLeftAct_partner = ImVec2(padding, posLeftFrame_partner.y + sizeFrameL_partner.y + innerLineSpacing);
                    ImVec2 posLeftPLAct_partner = ImVec2(padding, posLeftAct_partner.y + sizeActL_partner.y + innerLineSpacing);
                    ImVec2 posLeftAnmBelow_partner = ImVec2(padding, posLeftPLAct_partner.y + sizePLActL_partner.y + innerLineSpacing);

                    ImVec2 posRightPtr_partner = ImVec2(io.DisplaySize.x - rightMaxW_partner - padding, partnerStartY);
                    ImVec2 posRightChar_partner = ImVec2(posRightPtr_partner.x, posRightPtr_partner.y + inputTextHeight + pointerGap);
                    ImVec2 posRightCostume_partner = ImVec2(posRightPtr_partner.x, posRightChar_partner.y + sizeCharInfoR_partner.y + innerLineSpacing);
                    ImVec2 posRightState_partner = ImVec2(posRightPtr_partner.x, posRightCostume_partner.y + sizeCostumeR_partner.y + innerLineSpacing);
                    ImVec2 posRightFrame_partner = ImVec2(posRightPtr_partner.x, posRightState_partner.y + sizeCharStateInfoR_partner.y + innerLineSpacing);
                    ImVec2 posRightAct_partner = ImVec2(posRightPtr_partner.x, posRightFrame_partner.y + sizeFrameR_partner.y + innerLineSpacing);
                    ImVec2 posRightPLAct_partner = ImVec2(posRightPtr_partner.x, posRightAct_partner.y + sizeActR_partner.y + innerLineSpacing);
                    ImVec2 posRightAnmBelow_partner = ImVec2(posRightPtr_partner.x, posRightPLAct_partner.y + sizePLActR_partner.y + innerLineSpacing);

                    // Draw background rectangles for partners
                    if (showLabelsBackground) {
                        ImU32 bgCol = IM_COL32(0, 0, 0, 160);
                        ImU32 borderCol = IM_COL32(255, 255, 255, 60);
                        float padInside = 6.0f;
                        float rounding = 6.0f;

                        if (pl1_partner) {
                            ImVec2 leftRectMin_partner = ImVec2(posLeftPtr_partner.x - padInside, posLeftPtr_partner.y - padInside);
                            ImVec2 leftRectMax_partner = ImVec2(posLeftPtr_partner.x + leftMaxW_partner + padInside, posLeftAnmBelow_partner.y + sizeAnmL_partner.y + padInside);

                            ImDrawList* bgDraw = ImGui::GetBackgroundDrawList();
                            bgDraw->AddRectFilled(leftRectMin_partner, leftRectMax_partner, bgCol, rounding);
                            bgDraw->AddRect(leftRectMin_partner, leftRectMax_partner, borderCol, rounding, 0, 1.0f);
                        }

                        if (pl2_partner) {
                            ImVec2 rightRectMin_partner = ImVec2(posRightPtr_partner.x - padInside, posRightPtr_partner.y - padInside);
                            ImVec2 rightRectMax_partner = ImVec2(posRightPtr_partner.x + rightMaxW_partner + padInside, posRightAnmBelow_partner.y + sizeAnmR_partner.y + padInside);

                            ImDrawList* bgDraw = ImGui::GetBackgroundDrawList();
                            bgDraw->AddRectFilled(rightRectMin_partner, rightRectMax_partner, bgCol, rounding);
                            bgDraw->AddRect(rightRectMin_partner, rightRectMax_partner, borderCol, rounding, 0, 1.0f);
                        }
                    }

                    // Draw partner text labels
                    if (pl1_partner) {
                        drawList->AddText(posLeftChar_partner, IM_COL32(255, 255, 255, 255), bufCharInfoL_partner);
                        drawList->AddText(posLeftCostume_partner, IM_COL32(255, 255, 255, 255), bufCostumeL_partner);
                        drawList->AddText(posLeftState_partner, IM_COL32(255, 255, 255, 255), bufCharStateInfoL_partner);
                        drawList->AddText(posLeftFrame_partner, IM_COL32(255, 255, 255, 255), bufFrameL_partner);
                        drawList->AddText(posLeftAct_partner, IM_COL32(255, 255, 255, 255), bufActL_partner);
                        drawList->AddText(posLeftPLAct_partner, IM_COL32(255, 255, 255, 255), bufPLActL_partner);
                        drawList->AddText(posLeftAnmBelow_partner, IM_COL32(255, 255, 255, 255), bufAnmL_partner);
                    }

                    if (pl2_partner) {
                        drawList->AddText(posRightChar_partner, IM_COL32(255, 255, 255, 255), bufCharInfoR_partner);
                        drawList->AddText(posRightCostume_partner, IM_COL32(255, 255, 255, 255), bufCostumeR_partner);
                        drawList->AddText(posRightState_partner, IM_COL32(255, 255, 255, 255), bufCharStateInfoR_partner);
                        drawList->AddText(posRightFrame_partner, IM_COL32(255, 255, 255, 255), bufFrameR_partner);
                        drawList->AddText(posRightAct_partner, IM_COL32(255, 255, 255, 255), bufActR_partner);
                        drawList->AddText(posRightPLAct_partner, IM_COL32(255, 255, 255, 255), bufPLActR_partner);
                        drawList->AddText(posRightAnmBelow_partner, IM_COL32(255, 255, 255, 255), bufAnmR_partner);
                    }

                    // Partner pointer windows (InputText for copying)
                    ImGuiWindowFlags flags_partner =
                        ImGuiWindowFlags_NoTitleBar |
                        ImGuiWindowFlags_NoResize |
                        ImGuiWindowFlags_AlwaysAutoResize |
                        ImGuiWindowFlags_NoSavedSettings |
                        ImGuiWindowFlags_NoFocusOnAppearing |
                        ImGuiWindowFlags_NoMove;

                    // Left partner pointer
                    if (pl1_partner) {
                        ImGui::SetNextWindowPos(posLeftPtr_partner, ImGuiCond_Always);
                        ImGui::SetNextWindowBgAlpha(0.0f);
                        ImGui::Begin("##ptr_win_L_partner", nullptr, flags_partner);
                        ImGui::PushItemWidth(leftMaxW_partner - 12.0f);
                        char leftBuf_partner[64]; std::memset(leftBuf_partner, 0, sizeof(leftBuf_partner)); std::strncpy(leftBuf_partner, bufPtrL_partner, sizeof(leftBuf_partner) - 1);
                        ImGui::InputText("##ptr_left_partner", leftBuf_partner, sizeof(leftBuf_partner), ImGuiInputTextFlags_ReadOnly | ImGuiInputTextFlags_AutoSelectAll);
                        ImGui::PopItemWidth();
                        ImGui::End();
                    }

                    // Right partner pointer
                    if (pl2_partner) {
                        ImGui::SetNextWindowPos(posRightPtr_partner, ImGuiCond_Always);
                        ImGui::SetNextWindowBgAlpha(0.0f);
                        ImGui::Begin("##ptr_win_R_partner", nullptr, flags_partner);
                        ImGui::PushItemWidth(rightMaxW_partner - 12.0f);
                        char rightBuf_partner[64]; std::memset(rightBuf_partner, 0, sizeof(rightBuf_partner)); std::strncpy(rightBuf_partner, bufPtrR_partner, sizeof(rightBuf_partner) - 1);
                        ImGui::InputText("##ptr_right_partner", rightBuf_partner, sizeof(rightBuf_partner), ImGuiInputTextFlags_ReadOnly | ImGuiInputTextFlags_AutoSelectAll);
                        ImGui::PopItemWidth();
                        ImGui::End();
                    }
                }
                // --- END PARTNER DISPLAY SECTION ---

                // --- переключатель в правом-нижнем углу для скрытия/показа фона ---
                {
                    ImGuiIO& ioLocal = ImGui::GetIO();
                    const float pad = 10.0f;
                    ImGui::SetNextWindowBgAlpha(0.35f);
                    ImGui::SetNextWindowPos(ImVec2(ioLocal.DisplaySize.x - pad, ioLocal.DisplaySize.y - pad), ImGuiCond_Always, ImVec2(1.0f, 1.0f));
                    ImGui::Begin("##labels_bg_toggle", nullptr,
                        ImGuiWindowFlags_NoTitleBar |
                        ImGuiWindowFlags_NoResize |
                        ImGuiWindowFlags_AlwaysAutoResize |
                        ImGuiWindowFlags_NoSavedSettings |
                        ImGuiWindowFlags_NoFocusOnAppearing);
                    ImGui::TextUnformatted("Labels background");
                    ImGui::SameLine();
                    ImGui::Checkbox("##show_labels_bg", &showLabelsBackground);
                    ImGui::End();
                }

                // Использует: render::WorldPosData (заполнено вызовом GetWorldPosNew ранее)

                auto IsReadable = [](const void* addr, size_t size)->bool {
                    MEMORY_BASIC_INFORMATION mbi;
                    uintptr_t start = reinterpret_cast<uintptr_t>(addr);
                    uintptr_t end = start + size;
                    uintptr_t cur = start & ~static_cast<uintptr_t>(0xFFF);
                    while (cur < end) {
                        if (!VirtualQuery(reinterpret_cast<LPCVOID>(cur), &mbi, sizeof(mbi))) return false;
                        if (!(mbi.State & MEM_COMMIT)) return false;
                        if (mbi.Protect & (PAGE_NOACCESS | PAGE_GUARD)) return false;
                        cur = reinterpret_cast<uintptr_t>(mbi.BaseAddress) + mbi.RegionSize;
                    }
                    return true;
                    };


            }
        }
    }


    if (Show)
    {

        // Рисуем GUI
        ImGui::BeginMainMenuBar();
        if (ImGui::BeginMenu("UltimateStormAPI"))
        {
            if (ImGui::MenuItem("Help", "")) { WindowList[editor_helpWindow] = true; }
            if (ImGui::MenuItem("About...", "")) { showHelpWindow = true; }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Debug"))
        {
            if (ImGui::MenuItem("Camera Manager", "")) { WindowList[editor_cameraWindow] = true; }
            if (ImGui::MenuItem("Character Select Manager", "")) { WindowList[editor_charselWindow] = true; }
            //if (ImGui::MenuItem("Dynamics Editor", "")) { WindowList[editor_dynamicsDebug] = true; }
            ImGui::Checkbox("Player Info Output", &WindowList[editor_playerOutput]);
            ImGui::Checkbox("Show Message IDs", &render::skip_crc32_conv);
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Render"))
        {
            if (ImGui::BeginMenu("Post-Processing Settings"))
            {
                if (ImGui::MenuItem("Radial Color Settings", "")) { WindowList[editor_colorRadial] = true; }
                if (ImGui::MenuItem("Directional Color Settings", "")) { WindowList[editor_colorDirc] = true; }
                if (ImGui::MenuItem("Color Convert Settings", "")) { WindowList[editor_colorConvert] = true; }
                if (ImGui::MenuItem("Brightness Contrast Settings", "")) { WindowList[editor_brigthContrast] = true; }
                if (ImGui::MenuItem("Blur Settings", "")) { WindowList[editor_blurWindow] = true; }
                if (ImGui::MenuItem("Glare Settings", "")) { WindowList[editor_glareWindow] = true; }
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Stage"))
        {

            if (ImGui::MenuItem("Light Settings", "")) { WindowList[editor_lightSettings] = true; }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();

        
        if (WindowList[editor_dynamicsDebug]) {

            DrawDynamicsWindow(&WindowList[editor_dynamicsDebug]);
        }

        if (WindowList[editor_colorRadial])
        {
            DrawRadialColorWindow(&WindowList[editor_colorRadial], dispFrame1, dispFrame2);
        }
        if (WindowList[editor_colorDirc])
        {
            DrawDirectionalColorWindow(&WindowList[editor_colorDirc], dispFrame1, dispFrame2);
        }
        if (WindowList[editor_colorConvert])
        {
            DrawColorConvertWindow(&WindowList[editor_colorConvert], dispFrame1, dispFrame2);
        }

        if (WindowList[editor_brigthContrast])
        {
            DrawBrightnessContrastWindow(&WindowList[editor_brigthContrast], dispFrame1, dispFrame2);
        }
        if (WindowList[editor_blurWindow])
        {
            DrawBlurWindow(&WindowList[editor_blurWindow], dispFrame1, dispFrame2);
        }

        if (WindowList[editor_glareWindow])
        {
            DrawGlareConfigWindow(&WindowList[editor_glareWindow], dispFrame1, dispFrame2);
        }
        if (WindowList[editor_lightSettings])
        {
            DrawLightSettingsWindow(&WindowList[editor_lightSettings]);
        }
        if (WindowList[editor_cameraWindow])
        {
            ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);
            ImGui::Begin("Camera Manager", &WindowList[editor_cameraWindow]);

            // camera GUI
            std::string camText = "Camera: ";
            if (camPtr)
            {
                std::stringstream camPtrRead;
                camPtrRead << std::hex << std::uppercase << camPtr;
                camText += camPtrRead.str();

                editor_cameraWindowPos[0] = *((float*)(((__int64)camPtr) + 112));
                editor_cameraWindowPos[1] = *((float*)(((__int64)camPtr) + 116));
                editor_cameraWindowPos[2] = *((float*)(((__int64)camPtr) + 120));
            }
            else camText += "[nullptr]";

            // Внутри LoopGUI
            ImGui::TextWrapped(camText.c_str());

            // Позиция камеры (drag без ограничений)
            ImGui::DragFloat3("Position", &editor_cameraWindowPos[0], 1.0f, -FLT_MAX, FLT_MAX, "%.2f");

            // Вкл/выкл движение камеры
            std::string camMoveBtnText = editor_cameraWindowEnableCam ? "Disable Camera Movement" : "Enable Camera Movement";
            if (ImGui::Button(camMoveBtnText.c_str()))
            {
                editor_cameraWindowEnableCam = !editor_cameraWindowEnableCam;
                if (editor_cameraWindowEnableCam) FrameworkHelpers::EnableCameraMovement();
                else FrameworkHelpers::DisableCameraMovement();
            }

            // Camera Mode (0 или 1)
            ImGui::InputInt("Camera Mode", &editor_cameraWindowMode);
            if (editor_cameraWindowMode < 0) editor_cameraWindowMode = 0;
            if (editor_cameraWindowMode > 2) editor_cameraWindowMode = 2;

            // FOV сразу под Camera Mode
            ImGui::DragFloat("Field of View", &editor_cameraWindowFov, 0.5f, -FLT_MAX, FLT_MAX, "%.2f");

            // Отступ
            ImGui::Dummy(ImVec2(0, 10));

            // Поля для Camera Mode 1
            if (editor_cameraWindowMode == 1 || editor_cameraWindowMode == 2)
            {
                ImGui::DragFloat("Cam Distance", &editor_cameraWindowPlDistance, 1.0f, -FLT_MAX, FLT_MAX, "%.2f");
                ImGui::DragFloat("Cam Height", &editor_cameraWindowPlHeight, 1.0f, -FLT_MAX, FLT_MAX, "%.2f");
                ImGui::DragFloat3("Look Offset", &editor_cameraWindowPlLookOffset.x, 0.1f, -FLT_MAX, FLT_MAX, "%.2f");
            }

            ImGui::End();

        }
        if (WindowList[editor_charselWindow]) {

            ImGui::SetNextWindowSize(ImVec2(300, 700), ImGuiCond_FirstUseEver);
            ImGui::Begin("Character Select Manager", &WindowList[editor_charselWindow]);

            // Подписи полей (ровно 11)
            static const char* labels[11] = {
                "Light X",
                "Light Y",
                "Light Z",
                "Position X (Constant)",
                "Position Y (Constant)",
                "Position Z (Constant)",
                "Position X",
                "Position Y",
                "Position Z",
                "Rotation (Constant)",
                "Rotation"
            };
            float vals1[11] = { 0 }, vals2[11] = { 0 };

            struct VersionOffsets
            {
                const char* version;
                uintptr_t baseP1;
                std::vector<uint32_t> offsetsP1;
                uintptr_t baseP2;
                std::vector<uint32_t> offsetsP2;
            };

            static std::vector<VersionOffsets> CharSelversions =
            {
                {
                    "1.60",
                    0x022FB988, { 0x80,0x130,0x50,0xC0,0x118,0x48,0x1DC },
                    0x022FB998, { 0x18,0x08,0x10,0x28,0x30,0x40,0xCC }
                },
                {
                    "1.09",
                    0x016BDA18, { 0x80, 0x130, 0x50, 0x30, 0x98, 0x18, 0x2B4 },
                    0x016BDA18, { 0x80, 0x138, 0x38, 0x148, 0x70, 0xF4 }
                }
                // сюда легко добавить новые версии
            };
            uintptr_t baseFloatsP1 = 0, baseFloatsP2 = 0;

            if (GameVersion)
            {
                for (auto& v : CharSelversions)
                {
                    if (std::strcmp(GameVersion, v.version) == 0)
                    {
                        baseFloatsP1 = Offset::ResolvePointerChainBase(moduleBase, v.baseP1, v.offsetsP1);
                        baseFloatsP2 = Offset::ResolvePointerChainBase(moduleBase, v.baseP2, v.offsetsP2);
                        break;
                    }
                }
            }

            Read11Floats(baseFloatsP1, vals1);
            Read11Floats(baseFloatsP2, vals2);

            if (ImGui::CollapsingHeader("Player 1"))
            {
                if (!baseFloatsP1)
                    ImGui::TextWrapped("Player 1 pointer not resolved.");

                for (int i = 0; i < 11; ++i)
                {
                    if (i == 3 || i == 4 || i == 5 || i == 9) continue; // скрыть ненужные

                    ImGui::PushID(i);
                    if (ImGui::DragFloat(labels[i], &vals1[i], 1.0f, -FLT_MAX, FLT_MAX, "%.6f"))
                    {
                        if (baseFloatsP1)
                            Offset::WriteFloatAtIndexSafe(baseFloatsP1, i, vals1[i]);
                    }
                    ImGui::PopID();
                }
            }

            if (ImGui::CollapsingHeader("Player 2"))
            {
                if (!baseFloatsP2)
                    ImGui::TextWrapped("Player 2 pointer not resolved.");

                for (int i = 0; i < 11; ++i)
                {
                    if (i == 3 || i == 4 || i == 5 || i == 9) continue; // скрыть ненужные

                    ImGui::PushID(100 + i);
                    if (ImGui::DragFloat(labels[i], &vals2[i], 1.0f, -FLT_MAX, FLT_MAX, "%.6f"))
                    {
                        if (baseFloatsP2)
                            Offset::WriteFloatAtIndexSafe(baseFloatsP2, i, vals2[i]);
                    }
                    ImGui::PopID();
                }
            }

            ImGui::End();
        }
        if (showHelpWindow)
        {
            ImGui::Begin("About", &showHelpWindow); void* inner[4];
            ImGui::TextWrapped("UltimateStormAPI made by TheLeonX.\nSpecial thanks to ZealotTormunds aka Tomato, Xact and exavadeathwitch!");
            ImGui::End();
        }

        if (WindowList[editor_helpWindow]) {

            ImGui::Begin("Help", &WindowList[editor_helpWindow]); void* inner[4];
            ImGui::TextWrapped("Press F1 to hide HUD in battle.\nPress F2 to pause battle.\nPress F3 to show current scene (in console).");
            ImGui::End();
        }
    }


    if (pl1 && pl2 && render::pause) {
        // время и альфа для мерцания
        float t = ImGui::GetTime();
        float alpha = (sinf(t * 8.0f) * 0.5f + 0.5f);
        float minAlpha = 0.15f;
        float a = minAlpha + (1.0f - minAlpha) * alpha;

        // получить размер экрана и отступ
        ImGuiIO& io = ImGui::GetIO();
        ImVec2 screenSize = io.DisplaySize;
        const float padding = 10.0f;

        // взять текущий шрифт и увеличить размер
        ImFont* font = ImGui::GetFont();
        float font_size = font->LegacySize * 2.0f;

        // вычислить размер текста при выбранном шрифте/размере
        ImVec2 textSize = font->CalcTextSizeA(font_size, FLT_MAX, 0.0f, "PAUSE");

        // позиция в левом нижнем углу (с учётом высоты текста и отступа)
        ImVec2 pos = ImVec2(padding, screenSize.y - padding - textSize.y);

        // цвет с альфа
        ImU32 col = ImGui::GetColorU32(ImVec4(1.0f, 1.0f, 1.0f, a));

        // нарисовать текст поверх всего
        ImDrawList* draw_list = ImGui::GetForegroundDrawList();
        draw_list->AddText(font, font_size, pos, col, "PAUSE");

    }

    // === ВЫНЕСЕНО ОТСЮДА ===
    // Камера обновляется ВСЕГДА, даже если Show == false
    if (camPtr)
    {
        Vector3 newPos(editor_cameraWindowPos[0], editor_cameraWindowPos[1], editor_cameraWindowPos[2]);
        switch (editor_cameraWindowMode)
        {
        default:
        {
            if (!editor_cameraWindowEnableCam)
            {
                if (Editor::MouseLook::instance == nullptr)
                    Editor::MouseLook::instance = new Editor::MouseLook();
                Editor::MouseLook::instance->Update((HWND)((__int64)(DirectX::theWindow)));

                Vector3* look = &(camPtr->m_look);
                Vector3 forward = Editor::MouseLook::instance->CalculateLookPoint();

                float camSpeed = 8.0f;
                if (GetAsyncKeyState(VK_SHIFT)) camSpeed = 16.0f;

                // Keyboard movement
                if (GetAsyncKeyState('W')) newPos = newPos + (forward.Normalize() * camSpeed);
                if (GetAsyncKeyState('S')) newPos = newPos - (forward.Normalize() * camSpeed);

                // Controller left stick movement
                float lx = controller.Gamepad.sThumbLX / 32767.0f;
                float ly = controller.Gamepad.sThumbLY / 32767.0f;

                if (fabs(lx) > 0.2f) newPos = newPos + (Vector3(forward.z, 0, -forward.x).Normalize() * (lx * camSpeed));
                if (fabs(ly) > 0.2f) newPos = newPos + (forward.Normalize() * (ly * camSpeed));

                *look = (newPos)+(forward * 5);

                ccCmnCamera::SetCameraPosNew(camPtr, &newPos);
                camPtr->m_internalPosX = newPos.x;
                camPtr->m_internalPosY = newPos.y;
                camPtr->m_internalPosZ = newPos.z;
                camPtr->m_fov = editor_cameraWindowFov;
                camPtr->m_tilt_unk = 0;
                camPtr->m_tilt = Vector3(0, 1, 0.01);

                ccCmnCamera::Update(camPtr);
            }
            break;
        }
        case 1:
        {
            ccPlayerMain* pl = BattleUtils::ccGame_GetPlayerLeader(0);
            if (pl)
            {
                Vector3* plPos = (Vector3*)((__int64)(pl)+112);
                Vector3* look = &(camPtr->m_look);
                *look = *plPos + editor_cameraWindowPlLookOffset;

                // Rotate camera with gamepad right stick or keyboard
                float rx = controller.Gamepad.sThumbRX / 32767.0f;
                if (fabs(rx) > 0.2f) editor_cameraWindowPlAngle += (rx / 50.0f);

                if (GetAsyncKeyState('Z') || (controller.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT))
                    editor_cameraWindowPlAngle -= 0.03f;
                if (GetAsyncKeyState('C') || (controller.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT))
                    editor_cameraWindowPlAngle += 0.03f;

                Vector3 calculatedPos = *plPos +
                    Vector3(editor_cameraWindowPlDistance * sinf(editor_cameraWindowPlAngle),
                        editor_cameraWindowPlDistance * cosf(editor_cameraWindowPlAngle),
                        editor_cameraWindowPlHeight);

                ccCmnCamera::SetCameraPosNew(camPtr, &calculatedPos);
                camPtr->m_fov = editor_cameraWindowFov;
                camPtr->m_tilt_unk = 0;
                camPtr->m_tilt = Vector3(0, 1, 0.01);
            }
            break;
        }
        case 2:
        {
            ccPlayerMain* pl = BattleUtils::ccGame_GetPlayerLeader(1);
            if (pl)
            {
                Vector3* plPos = (Vector3*)((__int64)(pl)+112);
                Vector3* look = &(camPtr->m_look);
                *look = *plPos + editor_cameraWindowPlLookOffset;

                // Rotate camera with gamepad right stick or keyboard
                float rx = controller.Gamepad.sThumbRX / 32767.0f;
                if (fabs(rx) > 0.2f) editor_cameraWindowPlAngle += (rx / 50.0f);

                if (GetAsyncKeyState('Z') || (controller.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT))
                    editor_cameraWindowPlAngle -= 0.03f;
                if (GetAsyncKeyState('C') || (controller.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT))
                    editor_cameraWindowPlAngle += 0.03f;

                Vector3 calculatedPos = *plPos +
                    Vector3(editor_cameraWindowPlDistance * sinf(editor_cameraWindowPlAngle),
                        editor_cameraWindowPlDistance * cosf(editor_cameraWindowPlAngle),
                        editor_cameraWindowPlHeight);

                ccCmnCamera::SetCameraPosNew(camPtr, &calculatedPos);
                camPtr->m_fov = editor_cameraWindowFov;
                camPtr->m_tilt_unk = 0;
                camPtr->m_tilt = Vector3(0, 1, 0.01);
            }
            break;
        }
        }
    }
    // === КОНЕЦ ВЫНЕСЕННОГО ===


    

    UltimateStormAPI::OnGUI(Show, (__int64)(DirectX::theWindow), (__int64)(DirectX::guiContext));

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}



static void DrawBlurWindow(bool* p_open, int pl1_frame, int pl2_frame)
{
    static int playerIndex = 0; // 0 => Player 1, 1 => Player 2

    // ====== Window UI ======
    ImGui::SetNextWindowSize(ImVec2(435, 427), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Blur Editor", p_open, ImGuiWindowFlags_NoCollapse))
    {
        ImGui::End();
        return;
    }

    // Header
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 6.0f);
    ImGui::BeginChild("header_child", ImVec2(0, 40), false, ImGuiWindowFlags_NoScrollbar);
    ImGui::SetCursorPosX(8.0f);
    ImGui::Checkbox("Apply", &EditorGUI::editor_blur.enable);
    ImGui::SameLine();
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 6.0f);
    ImGui::Dummy(ImVec2(0, 6));
    if (ImGui::Button("Output FCURVE", ImVec2(100, 0)))
    {
        int frame = 0;
        if (playerIndex == 0) {

            frame = pl1_frame;
        }
        else {

            frame = pl2_frame;
        }
        auto& s = EditorGUI::editor_blur;
        Console::PrintOut("=========BLUR==========\n");
        if (s.type == 0) {
            Console::PrintOutY("%d, %d.000000, %.6f, %.6f, %.6f, %.6f, %d.000000,\n",
                frame,
                s.type,                     // int -> %d
                s.RadialPosXY.x,            // float -> %.6f
                s.RadialPosXY.y,            // float -> %.6f
                s.width,                    // float -> %.6f
                s.alpha,                    // float -> %.6f
                s.blurAccuracy);            // int -> %d

        }
        else {
            Console::PrintOutY("%d, %d.000000, %.6f, %.6f, %.6f, %.6f, %d.000000,\n",
                frame,
                s.type,                     // int -> %d
                s.DirectionCenterXY.x,      // float -> %.6f
                s.DirectionCenterXY.y,      // float -> %.6f
                s.width,                    // float -> %.6f
                s.alpha,                    // float -> %.6f
                s.blurAccuracy);            // int -> %d
        }

    }

    // combobox right after the button on the same row
    ImGui::SameLine();
    ImGui::PushItemWidth(120.0f);
    const char* players[] = { "Player 1", "Player 2" };
    ImGui::Combo("##player_select", &playerIndex, players, IM_ARRAYSIZE(players));
    ImGui::PopItemWidth();

    ImGui::PopStyleVar();
    ImGui::EndChild();

    // Main child with controls
    ImGui::BeginChild("main_child", ImVec2(0, 0), true);

    // Blur type selection with immediate side-effects
    ImGui::TextUnformatted("Blur type");
    ImGui::Indent(4.0f);
    ImGui::RadioButton("Radial blur", &EditorGUI::editor_blur.type, 0);
    ImGui::RadioButton("Directional blur", &EditorGUI::editor_blur.type, 1);
    ImGui::RadioButton("Motion blur", &EditorGUI::editor_blur.type, 2);
    ImGui::Unindent(4.0f);

    ImGui::Spacing();

    // For radial: position sliders in 0..100 (percent of screen)
    if (EditorGUI::editor_blur.type == 0)
    {
        ImGui::TextUnformatted("Radial position (%)");
        ImGui::DragFloat("X##radialX", &EditorGUI::editor_blur.RadialPosXY.x, 0.2f, 0.0f, 100.0f, "%.3f");
        ImGui::DragFloat("Y##radialY", &EditorGUI::editor_blur.RadialPosXY.y, 0.2f, 0.0f, 100.0f, "%.3f");
    }
    else
    {
        // For directional and motion: show direction controls but do NOT allow editing blur.width here
        ImGui::TextUnformatted("Blur direction");
        ImGui::DragFloat("X##dirX", &EditorGUI::editor_blur.DirectionCenterXY.x, 0.05f, -1000.0f, 1000.0f, "%.3f");
        ImGui::DragFloat("Y##dirY", &EditorGUI::editor_blur.DirectionCenterXY.y, 0.05f, -1000.0f, 1000.0f, "%.3f");
    }

    ImGui::Spacing();

    ImGui::TextUnformatted("Blur width");
    ImGui::SliderFloat("##blurWidth", &EditorGUI::editor_blur.width, 0.0f, 100.0f, "%.2f");

    ImGui::TextUnformatted("Alpha");
    ImGui::SliderFloat("##alpha", &EditorGUI::editor_blur.alpha, 0.0f, 1.0f, "%.2f");

    ImGui::Spacing();

    // Blur accuracy radio buttons
    ImGui::TextUnformatted("Blur accuracy");
    ImGui::Indent(4.0f);
    ImGui::RadioButton("Low precision", &EditorGUI::editor_blur.blurAccuracy, 0);
    ImGui::RadioButton("Medium precision", &EditorGUI::editor_blur.blurAccuracy, 1);
    ImGui::RadioButton("High precision", &EditorGUI::editor_blur.blurAccuracy, 2);
    ImGui::Unindent(4.0f);

    ImGui::EndChild(); // main_child

    // write settings to game
    __int64 cfptr = Game::ObjectList_GetPtrLightsAndFog();
    BlurSettings::SetSettings(cfptr, &EditorGUI::editor_blur);

    ImGui::End();

    // =========================
    // Overlay drawing (visual aids)
    // - Radial blur: draw three concentric ellipses using radialPosX/Y (0..100)
    // - Directional and Motion blur: draw 6x6 small oriented lines showing direction; arrows scaled ×4 and independent of blur.width
    // =========================

    ImGuiIO& io = ImGui::GetIO();
    ImDrawList* drawList = ImGui::GetForegroundDrawList();
    ImVec2 screenSize = io.DisplaySize;
    float minDimension = (screenSize.x < screenSize.y) ? screenSize.x : screenSize.y;

    // Compute overlay center:
    ImVec2 overlayCenter = ImVec2(screenSize.x * 0.5f, screenSize.y * 0.5f);

    if (EditorGUI::editor_blur.type == 0)
    {
        // radial uses radialPosX/Y normalized from 0..100 => 0..1
        float normX = ImClamp(EditorGUI::editor_blur.RadialPosXY.x * 0.01f, 0.0f, 1.0f);
        float normY = ImClamp(EditorGUI::editor_blur.RadialPosXY.y * 0.01f, 0.0f, 1.0f);
        overlayCenter = ImVec2(screenSize.x * normX, screenSize.y * normY);

        const float outerPadding = 1.00f;
        const float base = minDimension * 0.5f;
        float normalizedWidth = 10;

        float innerRadiusX = base * (0.20f + 0.02f * normalizedWidth);
        float innerRadiusY = innerRadiusX;
        float middleRadiusX = base * (0.45f + 0.03f * normalizedWidth);
        float middleRadiusY = middleRadiusX;
        float outerRadiusX = base * (0.80f + 0.05f * normalizedWidth * (1.0f + outerPadding * 0.5f));
        float outerRadiusY = outerRadiusX;

        const int SEGMENTS = 128;

        {
            ImVec2 pts[SEGMENTS];
            for (int i = 0; i < SEGMENTS; ++i)
            {
                float a = (2.0f * 3.14159265358979323846f) * (float)i / (float)SEGMENTS;
                pts[i].x = overlayCenter.x + innerRadiusX * cosf(a);
                pts[i].y = overlayCenter.y + innerRadiusY * sinf(a);
            }
            drawList->AddPolyline(pts, SEGMENTS, IM_COL32(255, 255, 255, 200), true, 2.5f);
        }

        {
            ImVec2 pts[SEGMENTS];
            for (int i = 0; i < SEGMENTS; ++i)
            {
                float a = (2.0f * 3.14159265358979323846f) * (float)i / (float)SEGMENTS;
                pts[i].x = overlayCenter.x + middleRadiusX * cosf(a);
                pts[i].y = overlayCenter.y + middleRadiusY * sinf(a);
            }
            drawList->AddPolyline(pts, SEGMENTS, IM_COL32(255, 255, 255, 160), true, 1.8f);
        }

        {
            ImVec2 pts[SEGMENTS];
            for (int i = 0; i < SEGMENTS; ++i)
            {
                float a = (2.0f * 3.14159265358979323846f) * (float)i / (float)SEGMENTS;
                pts[i].x = overlayCenter.x + outerRadiusX * cosf(a);
                pts[i].y = overlayCenter.y + outerRadiusY * sinf(a);
            }
            drawList->AddPolyline(pts, SEGMENTS, IM_COL32(255, 255, 255, 120), true, 1.2f);
        }
    }
    else
    {
        // Directional and Motion: center forced to normalized (1,0) as requested
        overlayCenter = ImVec2(screenSize.x * 1.0f, screenSize.y * 0.0f);

        // Direction vector uses DirectionCenterXY fields as direction input
        ImVec2 dir = ImVec2(EditorGUI::editor_blur.DirectionCenterXY.x, EditorGUI::editor_blur.DirectionCenterXY.y);

        float dirLength = sqrtf(dir.x * dir.x + dir.y * dir.y);

        // Grid parameters
        const int GRID_N = 6;
        const float CELL_SPACING = 14.0f * 6;
        const float GRID_HALF = (GRID_N - 1) * 0.5f * CELL_SPACING;

        // Arrow base length: fixed scale (independent from blur.width) and multiplied by 4 as requested
        const float BASE_ARROW_LENGTH = 16.0f; // base visual length
        const float ARROW_LENGTH = BASE_ARROW_LENGTH * 3.0f; // scaled 4x, does not use blur.width

        const float markerHalf = 3.0f;

        for (int gy = 0; gy < GRID_N; ++gy)
        {
            for (int gx = 0; gx < GRID_N; ++gx)
            {
                float offsetX = ((float)gx * CELL_SPACING) - GRID_HALF;
                float offsetY = ((float)gy * CELL_SPACING) - GRID_HALF;
                ImVec2 cellCenter = ImVec2((screenSize.x * 0.5f) + offsetX, (screenSize.y * 0.5f) + offsetY);

                if (dirLength < 0.001f)
                {
                    // draw small cross to indicate no direction
                    drawList->AddLine(ImVec2(cellCenter.x - markerHalf, cellCenter.y - markerHalf),
                        ImVec2(cellCenter.x + markerHalf, cellCenter.y + markerHalf),
                        IM_COL32(255, 255, 255, 160), 1.0f);
                    drawList->AddLine(ImVec2(cellCenter.x - markerHalf, cellCenter.y + markerHalf),
                        ImVec2(cellCenter.x + markerHalf, cellCenter.y - markerHalf),
                        IM_COL32(255, 255, 255, 160), 1.0f);
                }
                else
                {
                    ImVec2 dirNorm = ImVec2(-dir.x / dirLength, -dir.y / dirLength); // negative Y so positive input goes up
                    float halfLen = ARROW_LENGTH * 0.5f;
                    ImVec2 p0 = ImVec2(cellCenter.x - dirNorm.x * halfLen, cellCenter.y - dirNorm.y * halfLen);
                    ImVec2 p1 = ImVec2(cellCenter.x + dirNorm.x * halfLen, cellCenter.y + dirNorm.y * halfLen);
                    drawList->AddLine(p0, p1, IM_COL32(255, 255, 255, 200), 1.6f);

                    // arrow head
                    ImVec2 arrowDir = dirNorm;
                    ImVec2 perp = ImVec2(-arrowDir.y, arrowDir.x);
                    float arrowSize = ImMin(8.0f, halfLen * 0.35f);
                    ImVec2 arrowP1 = ImVec2(p1.x - arrowDir.x * arrowSize + perp.x * (arrowSize * 0.5f),
                        p1.y - arrowDir.y * arrowSize + perp.y * (arrowSize * 0.5f));
                    ImVec2 arrowP2 = ImVec2(p1.x - arrowDir.x * arrowSize - perp.x * (arrowSize * 0.5f),
                        p1.y - arrowDir.y * arrowSize - perp.y * (arrowSize * 0.5f));
                    drawList->AddTriangleFilled(p1, arrowP1, arrowP2, IM_COL32(255, 255, 255, 200));
                }
            }
        }
    }
}

static void DrawGlareConfigWindow(bool* p_open, int pl1_frame, int pl2_frame)
{
    static int playerIndex = 0; // 0 => Player 1, 1 => Player 2
    // ====== Window UI ======
    ImGui::SetNextWindowSize(ImVec2(335, 327), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Glare Editor", p_open, ImGuiWindowFlags_NoCollapse))
    {
        ImGui::End();
        return;
    }

    // Header
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 6.0f);
    ImGui::BeginChild("header_child", ImVec2(0, 40), false, ImGuiWindowFlags_NoScrollbar);
    ImGui::SetCursorPosX(8.0f);
    ImGui::Checkbox("Apply", &EditorGUI::editor_glareConfig.enable);
    ImGui::SameLine();
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 6.0f);
    ImGui::Dummy(ImVec2(0, 6));
    if (ImGui::Button("Output FCURVE", ImVec2(100, 0)))
    {
        int frame = 0;
        if (playerIndex == 0) {

            frame = pl1_frame;
        }
        else {

            frame = pl2_frame;
        }
        auto& s = EditorGUI::editor_glareConfig;
        Console::PrintOut("=========GLARE==========\n");
        Console::PrintOutY("%d, %.6f, %.6f, %.6f,\n", frame,
            s.luminanceThreshold,
            s.subtractedValue,
            s.CompositionStrength);
    }
    // combobox right after the button on the same row
    ImGui::SameLine();
    ImGui::PushItemWidth(120.0f);
    const char* players[] = { "Player 1", "Player 2" };
    ImGui::Combo("##player_select", &playerIndex, players, IM_ARRAYSIZE(players));
    ImGui::PopItemWidth();

    ImGui::PopStyleVar();
    ImGui::EndChild();
    // single child (no columns)
    ImGui::BeginChild("main_child", ImVec2(0, 0), true);

    // Brightness and Contrast
    ImGui::TextUnformatted("Luminance Threshold");
    ImGui::PushItemWidth(-1);
    ImGui::DragFloat("##luminancethreshold", &EditorGUI::editor_glareConfig.luminanceThreshold, 0.05f, 0.0f, 1.0f, "%.3f");
    ImGui::PopItemWidth();
    ImGui::Spacing();
    ImGui::TextUnformatted("Subtracted Value");
    ImGui::PushItemWidth(-1);
    ImGui::DragFloat("##subtractedvalue", &EditorGUI::editor_glareConfig.subtractedValue, 0.05f, 0.0f, 1.0f, "%.3f");
    ImGui::PopItemWidth();
    ImGui::Spacing();
    ImGui::TextUnformatted("Composition Strength");
    ImGui::PushItemWidth(-1);
    ImGui::DragFloat("##compositionstrength", &EditorGUI::editor_glareConfig.CompositionStrength, 0.25f, 0.0f, 100.0f, "%.3f");
    ImGui::PopItemWidth();
    ImGui::Spacing();



    ImGui::EndChild(); // main_child



    // write settings
    __int64 cfptr = Game::ObjectList_GetPtrLightsAndFog();
    GlareSettings::SetSettings(cfptr, &EditorGUI::editor_glareConfig);

    ImGui::End();
}

static void DrawBrightnessContrastWindow(bool* p_open, int pl1_frame, int pl2_frame)
{
    static int playerIndex = 0; // 0 => Player 1, 1 => Player 2
    // ====== Window UI ======
    ImGui::SetNextWindowSize(ImVec2(335, 327), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Brightness And Contrast Editor", p_open, ImGuiWindowFlags_NoCollapse))
    {
        ImGui::End();
        return;
    }

    // Header
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 6.0f);
    ImGui::BeginChild("header_child", ImVec2(0, 40), false, ImGuiWindowFlags_NoScrollbar);
    ImGui::SetCursorPosX(8.0f);
    ImGui::Checkbox("Apply", &EditorGUI::editor_brightnessContrast.enable);
    ImGui::SameLine();
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 6.0f);
    ImGui::Dummy(ImVec2(0, 6));
    if (ImGui::Button("Output FCURVE", ImVec2(100, 0)))
    {
        int frame = 0;
        if (playerIndex == 0) {

            frame = pl1_frame;
        }
        else {

            frame = pl2_frame;
        }
        auto& s = EditorGUI::editor_brightnessContrast;
        Console::PrintOut("=========BRIGTHNESS AND CONTRAST==========\n");
        Console::PrintOutY("%d, %.6f, %.6f,\n", frame,
            s.brightness,
            s.contrast);
    }
    // combobox right after the button on the same row
    ImGui::SameLine();
    ImGui::PushItemWidth(120.0f);
    const char* players[] = { "Player 1", "Player 2" };
    ImGui::Combo("##player_select", &playerIndex, players, IM_ARRAYSIZE(players));
    ImGui::PopItemWidth();

    ImGui::PopStyleVar();
    ImGui::EndChild();
    // single child (no columns)
    ImGui::BeginChild("main_child", ImVec2(0, 0), true);

    // Brightness and Contrast
    ImGui::TextUnformatted("Brightness Correction");
    ImGui::PushItemWidth(-1);
    ImGui::DragFloat("##brightness", &EditorGUI::editor_brightnessContrast.brightness, 0.05f, -1.0f, 1.0f, "%.3f");
    ImGui::PopItemWidth();
    ImGui::Spacing();
    ImGui::TextUnformatted("Contrast Correction");
    ImGui::PushItemWidth(-1);
    ImGui::DragFloat("##contrast", &EditorGUI::editor_brightnessContrast.contrast, 0.25f, 0.0f, 100.0f, "%.3f");
    ImGui::PopItemWidth();
    ImGui::Spacing();

    

    ImGui::EndChild(); // main_child

   

    // write settings
    __int64 cfptr = Game::ObjectList_GetPtrLightsAndFog();
    BrightnessContrastSettings::SetSettings(cfptr, &EditorGUI::editor_brightnessContrast);

    ImGui::End();
}

static void DrawDynamicsWindow(bool* p_open) {
    ImGui::Separator();
    ImGui::TextUnformatted("Physics FPS Factors");
    ImGui::Spacing();

    ImGui::TextUnformatted("Stiffness Factor");
    ImGui::PushItemWidth(-1);
    ImGui::DragFloat("##stiffnessFactor", &render::stiffnessFactor, 0.01f, 0.0f, 4.0f, "%.3f");
    ImGui::PopItemWidth();
    ImGui::Spacing();

    ImGui::TextUnformatted("Bounciness Factor");
    ImGui::PushItemWidth(-1);
    ImGui::DragFloat("##bouncinessFactor", &render::bouncinessFactor, 0.01f, 0.0f, 4.0f, "%.3f");
    ImGui::PopItemWidth();
    ImGui::Spacing();

    ImGui::TextUnformatted("Elasticity Factor");
    ImGui::PushItemWidth(-1);
    ImGui::DragFloat("##elasticityFactor", &render::elasticityFactor, 0.01f, 0.0f, 4.0f, "%.3f");
    ImGui::PopItemWidth();
    ImGui::Spacing();

    ImGui::TextUnformatted("Movement Factor");
    ImGui::PushItemWidth(-1);
    ImGui::DragFloat("##movementFactor", &render::movementFactor, 0.01f, 0.0f, 4.0f, "%.3f");
    ImGui::PopItemWidth();
    ImGui::Spacing();

    // Clamp to avoid negative values
    if (render::stiffnessFactor < 0.0f) render::stiffnessFactor = 0.0f;
    if (render::bouncinessFactor < 0.0f) render::bouncinessFactor = 0.0f;
    if (render::elasticityFactor < 0.0f) render::elasticityFactor = 0.0f;
    if (render::movementFactor < 0.0f) render::movementFactor = 0.0f;

    // Reset button
    if (ImGui::Button("Reset Physics Factors"))
    {
        render::stiffnessFactor = 1.0f;
        render::bouncinessFactor = 1.0f;
        render::elasticityFactor = 1.0f;
        render::movementFactor = 1.0f;
    }
}


static void DrawColorConvertWindow(bool* p_open, int pl1_frame, int pl2_frame)
{
    // ====== Fixed calibration defaults (no UI) ======
    static const bool calib_swap_xy = true;
    static const bool calib_invert_x = false;
    static const bool calib_invert_y = true;
    static const float calib_hue_offset_deg = 25.0f;
    static const float calib_sat_scale = 1.0f;
    static const float calib_val_scale = 1.0f; // kept for clarity but NOT used for preview/HSV value
    static int playerIndex = 0; // 0 => Player 1, 1 => Player 2
    // clamp helper
    auto clampf = [](float v, float a, float b) { return (v < a) ? a : ((v > b) ? b : v); };

    // ====== HSV <-> RGB helpers ======
    auto HSVtoRGB = [](float h, float s, float v, float& out_r, float& out_g, float& out_b)
        {
            if (s <= 0.0f) { out_r = out_g = out_b = v; return; }
            float hf = h * 6.0f;
            int i = static_cast<int>(floorf(hf));
            float f = hf - static_cast<float>(i);
            float p = v * (1.0f - s);
            float q = v * (1.0f - s * f);
            float t = v * (1.0f - s * (1.0f - f));
            switch (i % 6)
            {
            case 0: out_r = v; out_g = t; out_b = p; break;
            case 1: out_r = q; out_g = v; out_b = p; break;
            case 2: out_r = p; out_g = v; out_b = t; break;
            case 3: out_r = p; out_g = q; out_b = v; break;
            case 4: out_r = t; out_g = p; out_b = v; break;
            case 5: out_r = v; out_g = p; out_b = q; break;
            default: out_r = out_g = out_b = 0.0f; break;
            }
        };

    auto RGBtoHSV = [](float r, float g, float b, float& out_h, float& out_s, float& out_v)
        {
            float maxc = fmaxf(r, fmaxf(g, b));
            float minc = fminf(r, fminf(g, b));
            out_v = maxc;
            float delta = maxc - minc;
            if (maxc == 0.0f) { out_s = 0.0f; out_h = 0.0f; return; }
            out_s = delta / maxc;
            if (delta == 0.0f) { out_h = 0.0f; return; }
            if (maxc == r) out_h = (g - b) / delta;
            else if (maxc == g) out_h = 2.0f + (b - r) / delta;
            else out_h = 4.0f + (r - g) / delta;
            out_h /= 6.0f;
            if (out_h < 0.0f) out_h += 1.0f;
        };

    // ====== ColorBR <-> HSV (uses fixed calibration values above) ======
    auto ColorBR_FromHSV = [&](float h, float s, float /*v*/, float& out_x, float& out_y)
        {
            const float TWO_PI = 6.28318530717958647692f;
            float h_shifted = h + (calib_hue_offset_deg / 360.0f);
            if (h_shifted >= 1.0f) h_shifted -= floorf(h_shifted);
            if (h_shifted < 0.0f) h_shifted += ceilf(-h_shifted);

            float length = s / (2.0f * calib_sat_scale);
            length = clampf(length, 0.0f, 0.5f);

            float angle = (h_shifted - 0.5f) * TWO_PI;
            float lx = cosf(angle) * length;
            float ly = sinf(angle) * length;

            float rx = lx, ry = ly;
            if (calib_swap_xy) std::swap(rx, ry);
            if (calib_invert_x) rx = -rx;
            if (calib_invert_y) ry = -ry;

            out_x = clampf(rx, -0.5f, 0.5f);
            out_y = clampf(ry, -0.5f, 0.5f);
        };

    auto HSV_FromColorBR = [&](float x, float y, float& out_h, float& out_s, float& out_v)
        {
            float tx = x;
            float ty = y;
            if (calib_invert_x) tx = -tx;
            if (calib_invert_y) ty = -ty;
            if (calib_swap_xy) std::swap(tx, ty);

            const float TWO_PI = 6.28318530717958647692f;
            float angle = atan2f(ty, tx);
            float h = (angle / TWO_PI) + 0.5f;
            h -= (calib_hue_offset_deg / 360.0f);
            if (h < 0.0f) h += 1.0f;
            if (h >= 1.0f) h -= floorf(h);

            float mag = sqrtf(tx * tx + ty * ty);
            float s = mag * 2.0f * calib_sat_scale;
            s = clampf(s, 0.0f, 1.0f);

            // FORCE value = 1.0f to match game
            float v = 1.0f;

            out_h = h; out_s = s; out_v = v;
        };

    // ====== Window UI ======
    ImGui::SetNextWindowSize(ImVec2(435, 427), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Color Convert Editor", p_open, ImGuiWindowFlags_NoCollapse))
    {
        ImGui::End();
        return;
    }

    // Header
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 6.0f);
    ImGui::BeginChild("header_child", ImVec2(0, 40), false, ImGuiWindowFlags_NoScrollbar);
    ImGui::SetCursorPosX(8.0f);
    ImGui::Checkbox("Apply", &EditorGUI::editor_colorConverter.enable);
    ImGui::SameLine();
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 6.0f);
    ImGui::Dummy(ImVec2(0, 6));
    if (ImGui::Button("Output FCURVE", ImVec2(100, 0)))
    {
        int frame = 0;
        if (playerIndex == 0) {

            frame = pl1_frame;
        }
        else {

            frame = pl2_frame;
        }
        auto& s = EditorGUI::editor_colorConverter;
        float cx = clampf(s.ColorBR.x, -0.5f, 0.5f);
        float cy = clampf(s.ColorBR.y, -0.5f, 0.5f);
        Console::PrintOut("=========COLOR CONVERT==========\n");
        Console::PrintOutY("%d, %.6f, %.6f, %.6f, %.6f,\n", frame,
            static_cast<float>(s.mode),
            s.opacity,
            cx, cy);
    }
    // combobox right after the button on the same row
    ImGui::SameLine();
    ImGui::PushItemWidth(120.0f);
    const char* players[] = { "Player 1", "Player 2" };
    ImGui::Combo("##player_select", &playerIndex, players, IM_ARRAYSIZE(players));
    ImGui::PopItemWidth();

    ImGui::PopStyleVar();
    ImGui::EndChild();
    // single child (no columns)
    ImGui::BeginChild("main_child", ImVec2(0, 0), true);

    // Mode and Opacity
    ImGui::TextUnformatted("Mode");
    ImGui::PushItemWidth(-1);
    ImGui::SliderInt("##mode", &EditorGUI::editor_colorConverter.mode, 0, 4);
    ImGui::PopItemWidth();
    ImGui::Spacing();
    ImGui::TextUnformatted("Opacity");
    ImGui::PushItemWidth(-1);
    ImGui::SliderFloat("##opacity", &EditorGUI::editor_colorConverter.opacity, 0.0f, 1.0f, "%.3f");
    ImGui::PopItemWidth();
    ImGui::Spacing();

    // Clamp ColorBR before use
    EditorGUI::editor_colorConverter.ColorBR.x = clampf(EditorGUI::editor_colorConverter.ColorBR.x, -0.5f, 0.5f);
    EditorGUI::editor_colorConverter.ColorBR.y = clampf(EditorGUI::editor_colorConverter.ColorBR.y, -0.5f, 0.5f);

    // Get current RGB from ColorBR (force v=1.0)
    float cur_h, cur_s, cur_v;
    HSV_FromColorBR(EditorGUI::editor_colorConverter.ColorBR.x, EditorGUI::editor_colorConverter.ColorBR.y, cur_h, cur_s, cur_v);
    cur_v = 1.0f; // enforce game value
    float cur_r, cur_g, cur_b;
    HSVtoRGB(cur_h, cur_s, cur_v, cur_r, cur_g, cur_b);

    // ColorEdit3 (keeps sync) — when user picks, convert HSV->ColorBR with v forced to 1
    float picker_col[3] = { cur_r, cur_g, cur_b };
    const ImGuiColorEditFlags pickerFlags = ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoSidePreview;
    ImGui::TextUnformatted("Color (RGB)");
    ImGui::PushItemWidth(-1);
    if (ImGui::ColorEdit3("##colorpicker", picker_col, pickerFlags))
    {
        float hr, hs, hv;
        RGBtoHSV(picker_col[0], picker_col[1], picker_col[2], hr, hs, hv);
        // ignore hv, force v = 1 when converting to ColorBR
        float nx, ny;
        ColorBR_FromHSV(hr, hs, 1.0f, nx, ny);
        EditorGUI::editor_colorConverter.ColorBR.x = clampf(nx, -0.5f, 0.5f);
        EditorGUI::editor_colorConverter.ColorBR.y = clampf(ny, -0.5f, 0.5f);
    }

    ImGui::PopItemWidth();
    ImGui::Spacing();
    ImGui::TextUnformatted("ColorBR (x, y)");
    ImGui::PushItemWidth(-1);
    ImGui::InputFloat("##ColorBRx", &EditorGUI::editor_colorConverter.ColorBR.x, 0.01f, 0.1f, "%.4f");
    EditorGUI::editor_colorConverter.ColorBR.x = clampf(EditorGUI::editor_colorConverter.ColorBR.x, -0.5f, 0.5f);
    ImGui::InputFloat("##ColorBRy", &EditorGUI::editor_colorConverter.ColorBR.y, 0.01f, 0.1f, "%.4f");
    EditorGUI::editor_colorConverter.ColorBR.y = clampf(EditorGUI::editor_colorConverter.ColorBR.y, -0.5f, 0.5f);
    ImGui::PopItemWidth();

    ImGui::Spacing();

    // ====== Large interactive preview stretched to available width (V = 1) ======
    ImGuiIO& io = ImGui::GetIO();
    ImVec2 avail = ImGui::GetContentRegionAvail();
    float previewHeight = ImMax(80.0f, avail.x * 0.30f);
    ImVec2 previewSize = ImVec2(avail.x, previewHeight);
    ImGui::TextUnformatted("Preview");
    ImGui::InvisibleButton("color_preview_area", previewSize, ImGuiButtonFlags_MouseButtonLeft);
    ImVec2 p0 = ImGui::GetItemRectMin();
    ImDrawList* dl = ImGui::GetWindowDrawList();

    int tilesX = (int)fminf(previewSize.x, 360.0f);
    int tilesY = (int)fminf(previewSize.y, 180.0f);
    tilesX = tilesX > 0 ? tilesX : 1;
    tilesY = tilesY > 0 ? tilesY : 1;
    float tileW = previewSize.x / (float)tilesX;
    float tileH = previewSize.y / (float)tilesY;

    for (int iy = 0; iy < tilesY; ++iy)
    {
        float sy = 1.0f - (iy + 0.5f) / (float)tilesY;
        for (int ix = 0; ix < tilesX; ++ix)
        {
            float hx = (ix + 0.5f) / (float)tilesX;
            float rr, gg, bb;
            HSVtoRGB(hx, sy, 1.0f, rr, gg, bb); // VALUE = 1.0f
            ImU32 col = ImGui::ColorConvertFloat4ToU32(ImVec4(rr, gg, bb, 1.0f));
            ImVec2 a = ImVec2(p0.x + ix * tileW, p0.y + iy * tileH);
            ImVec2 b = ImVec2(a.x + tileW, a.y + tileH);
            dl->AddRectFilled(a, b, col, 0.0f);
        }
    }

    // selection marker (uses cur_v forced = 1)
    float sel_h = cur_h;
    float sel_s = cur_s;
    ImVec2 markPos = ImVec2(p0.x + sel_h * previewSize.x, p0.y + (1.0f - sel_s) * previewSize.y);
    dl->AddCircleFilled(markPos, 6.0f, IM_COL32(0, 0, 0, 200), 12);
    dl->AddCircle(markPos, 6.0f, IM_COL32(255, 255, 255, 200), 12);

    // click/drag: pick hue/sat, v forced = 1
    if (ImGui::IsItemActive() && (ImGui::IsMouseDown(ImGuiMouseButton_Left) || ImGui::IsMouseDragging(ImGuiMouseButton_Left)))
    {
        ImVec2 mouse = io.MousePos;
        float lx = (mouse.x - p0.x) / previewSize.x;
        float ly = (mouse.y - p0.y) / previewSize.y;
        lx = clampf(lx, 0.0f, 1.0f);
        ly = clampf(ly, 0.0f, 1.0f);

        float picked_h = lx;
        float picked_s = 1.0f - ly;
        float picked_v = 1.0f;

        float nx, ny;
        ColorBR_FromHSV(picked_h, picked_s, picked_v, nx, ny);
        EditorGUI::editor_colorConverter.ColorBR.x = clampf(nx, -0.5f, 0.5f);
        EditorGUI::editor_colorConverter.ColorBR.y = clampf(ny, -0.5f, 0.5f);
    }

    ImGui::Dummy(previewSize);
    ImGui::Spacing();

    ImGui::EndChild(); // main_child

    // final clamp
    EditorGUI::editor_colorConverter.ColorBR.x = clampf(EditorGUI::editor_colorConverter.ColorBR.x, -0.5f, 0.5f);
    EditorGUI::editor_colorConverter.ColorBR.y = clampf(EditorGUI::editor_colorConverter.ColorBR.y, -0.5f, 0.5f);

    // write settings
    __int64 cfptr = Game::ObjectList_GetPtrLightsAndFog();
    ColorConvertSettings::SetSettings(cfptr, &EditorGUI::editor_colorConverter);

    ImGui::End();
}


static void DrawRadialColorWindow(bool* p_open, int pl1_frame, int pl2_frame)
{
    static float outerPadding = 1.00f;
    static int playerIndex = 0; // 0 => Player 1, 1 => Player 2
    ImGui::SetNextWindowSize(ImVec2(370, 580), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Radial Color Filter Editor", p_open, ImGuiWindowFlags_NoCollapse))
    {
        ImGui::End();
        return;
    }

    // Header: Apply checkbox
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 6.0f);
    ImGui::BeginChild("header_child", ImVec2(0, 40), false, ImGuiWindowFlags_NoScrollbar);
    ImGui::SetCursorPosX(8.0f);
    ImGui::Checkbox("Apply", &EditorGUI::editor_colorFilterRadial.enable);
    ImGui::SameLine();
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 6.0f);
    

    ImGui::Dummy(ImVec2(0, 6));
    if (ImGui::Button("Output FCURVE", ImVec2(100, 0)))
    {
        int frame = 0;
        if (playerIndex == 0) {

            frame = pl1_frame;
        }
        else {

            frame = pl2_frame;
        }
        auto& s = EditorGUI::editor_colorFilterRadial;
        Console::PrintOut("=========COLOR RADIAL==========\n");
        Console::PrintOutY("%d, %.6f, %.6f, "                  // position.x, position.y
            "%.6f, %.6f, %.6f, %.6f, "      // colorA.rgba
            "%.6f, %.6f, %.6f, %.6f, "      // colorB.rgba
            "%.6f, %.6f, %.6f, %.6f, "      // colorC.rgba
            "%.6f, %.6f, "                  // scale.x, scale.y
            "%.6f, %d,\n", frame,               // middlePoint, alphaBlend
            s.position.x, s.position.y,
            s.colorA.x, s.colorA.y, s.colorA.z, s.colorA.w,
            s.colorB.x, s.colorB.y, s.colorB.z, s.colorB.w,
            s.colorC.x, s.colorC.y, s.colorC.z, s.colorC.w,
            s.scale.x, s.scale.y,
            s.middlePoint, s.alphaBlend);
    }
    // combobox right after the button on the same row
    ImGui::SameLine();
    ImGui::PushItemWidth(120.0f);
    const char* players[] = { "Player 1", "Player 2" };
    ImGui::Combo("##player_select", &playerIndex, players, IM_ARRAYSIZE(players));
    ImGui::PopItemWidth();

    ImGui::PopStyleVar();
    ImGui::EndChild();
    ImGui::Columns(2, nullptr, false);

    float totalW = ImGui::GetWindowContentRegionMax().x - ImGui::GetWindowContentRegionMin().x;
    ImGui::SetColumnWidth(0, totalW * 0.60f);

    // LEFT
    ImGui::BeginChild("controls", ImVec2(0, 0), true);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(6, 6));

    ImGui::TextUnformatted("MID");
    ImGui::SliderFloat("##mid", &EditorGUI::editor_colorFilterRadial.middlePoint, 0.0f, 1.0f, "%.2f");

    ImGui::Spacing();
    ImGui::TextUnformatted("Center");
    ImGui::SliderFloat("X##centerX", &EditorGUI::editor_colorFilterRadial.position.x, 0.0f, 1.0f, "%.2f");
    ImGui::SliderFloat("Y##centerY", &EditorGUI::editor_colorFilterRadial.position.y, 0.0f, 1.0f, "%.2f");

    ImGui::Spacing();
    ImGui::TextUnformatted("Scale");
    ImGui::SliderFloat("X##scaleX", &EditorGUI::editor_colorFilterRadial.scale.x, 0.01f, 5.0f, "%.2f");
    ImGui::SliderFloat("Y##scaleY", &EditorGUI::editor_colorFilterRadial.scale.y, 0.01f, 5.0f, "%.2f");

    ImGui::Spacing();
    ImGui::TextUnformatted("Blend Type");
    ImGui::Indent(4.0f);
    ImGui::RadioButton("Normal", &EditorGUI::editor_colorFilterRadial.alphaBlend, 1);
    ImGui::RadioButton("Add", &EditorGUI::editor_colorFilterRadial.alphaBlend, 2);
    ImGui::RadioButton("Subtract", &EditorGUI::editor_colorFilterRadial.alphaBlend, 3);
    ImGui::Unindent(4.0f);

    ImGui::PopStyleVar();
    ImGui::EndChild();

    // RIGHT
    ImGui::NextColumn();
    float leftColW = ImGui::GetColumnWidth(0);
    float rightColW = totalW - leftColW;
    if (rightColW < 1.0f) rightColW = ImGui::GetColumnWidth(1);

    const float horizontalPadding = 16.0f;
    float maxPreview = rightColW - horizontalPadding;
    if (maxPreview < 32.0f) maxPreview = 32.0f;
    const float desiredPreview = 150.0f;
    const float previewSize = (maxPreview < desiredPreview) ? maxPreview : desiredPreview;

    ImGui::BeginChild("colors_preview", ImVec2(0, 0), false);
    ImGui::PushItemWidth(previewSize);

    ImDrawList* win_draw = ImGui::GetWindowDrawList();
    const float rounding = 8.0f;
    const ImGuiColorEditFlags pickerFlags = ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoSidePreview;

    auto draw_color_block = [&](Vector4* colVec, const char* label, int idx)
        {
            ImGui::TextUnformatted(label);
            ImGui::Spacing();

            ImVec2 cursor = ImGui::GetCursorScreenPos();
            float colAvailW = ImGui::GetContentRegionAvail().x;
            float offsetX = (colAvailW - previewSize) * 0.5f;
            if (offsetX < 0.0f) offsetX = 0.0f;
            ImVec2 pos = ImVec2(cursor.x + offsetX, cursor.y);
            ImVec2 posEnd = ImVec2(pos.x + previewSize, pos.y + previewSize);

            ImVec4 colIm = ImVec4(colVec->x, colVec->y, colVec->z, colVec->w);
            ImU32 col = ImGui::ColorConvertFloat4ToU32(colIm);
            win_draw->AddRectFilled(pos, posEnd, col, rounding);
            win_draw->AddRect(pos, posEnd, IM_COL32(255, 255, 255, 120), rounding, 0, 2.0f);

            std::string btn_id = std::string("col_btn_") + std::to_string(idx);
            ImGui::SetCursorScreenPos(pos);
            ImGui::InvisibleButton(btn_id.c_str(), ImVec2(previewSize, previewSize));
            ImGui::SetCursorScreenPos(ImVec2(cursor.x, cursor.y + previewSize));

            if (ImGui::IsItemClicked())
            {
                std::string popup_id = std::string("col_popup_") + std::to_string(idx);
                ImGui::OpenPopup(popup_id.c_str());
            }

            ImGui::Dummy(ImVec2(0.0f, 8.0f));

            std::string popup_id_begin = std::string("col_popup_") + std::to_string(idx);
            if (ImGui::BeginPopup(popup_id_begin.c_str()))
            {
                ImGui::TextUnformatted(label);
                ImGui::Separator();
                std::string picker_id = std::string("##picker_") + std::to_string(idx);
                ImGui::ColorPicker4(picker_id.c_str(), (float*)colVec, pickerFlags, nullptr);
                ImGui::EndPopup();
            }
        };

    draw_color_block(&EditorGUI::editor_colorFilterRadial.colorA, "Inner layer", 0);
    draw_color_block(&EditorGUI::editor_colorFilterRadial.colorB, "Central layer", 1);
    draw_color_block(&EditorGUI::editor_colorFilterRadial.colorC, "Outer layer", 2);

    ImGui::PopItemWidth();
    ImGui::EndChild();

    ImGui::Columns(1);
    
    ImGui::End();

    // Overlay ellipses
    ImGuiIO& io = ImGui::GetIO();
    ImDrawList* draw_list = ImGui::GetForegroundDrawList();
    ImVec2 screenSize = io.DisplaySize;
    float minDim = (screenSize.x < screenSize.y) ? screenSize.x : screenSize.y;
    ImVec2 center = ImVec2(screenSize.x * EditorGUI::editor_colorFilterRadial.position.x,
        screenSize.y * EditorGUI::editor_colorFilterRadial.position.y);

    float base = minDim * 0.5f;
    float innerRX = base * EditorGUI::editor_colorFilterRadial.scale.x * EditorGUI::editor_colorFilterRadial.middlePoint;
    float innerRY = base * EditorGUI::editor_colorFilterRadial.scale.y * EditorGUI::editor_colorFilterRadial.middlePoint;
    float outerRX = base * EditorGUI::editor_colorFilterRadial.scale.x * (1.0f + outerPadding * EditorGUI::editor_colorFilterRadial.middlePoint);
    float outerRY = base * EditorGUI::editor_colorFilterRadial.scale.y * (1.0f + outerPadding * EditorGUI::editor_colorFilterRadial.middlePoint);

    const int SEGMENTS = 128;

    {
        ImVec2 pts[SEGMENTS];
        for (int i = 0; i < SEGMENTS; ++i)
        {
            float a = (2.0f * 3.14159265358979323846f) * (float)i / (float)SEGMENTS;
            pts[i].x = center.x + innerRX * cosf(a);
            pts[i].y = center.y + innerRY * sinf(a);
        }
        draw_list->AddPolyline(pts, SEGMENTS, IM_COL32(255, 255, 255, 200), true, 2.5f);
    }

    {
        ImVec2 pts[SEGMENTS];
        for (int i = 0; i < SEGMENTS; ++i)
        {
            float a = (2.0f * 3.14159265358979323846f) * (float)i / (float)SEGMENTS;
            pts[i].x = center.x + outerRX * cosf(a);
            pts[i].y = center.y + outerRY * sinf(a);
        }
        draw_list->AddPolyline(pts, SEGMENTS, IM_COL32(255, 255, 255, 120), true, 1.8f);
    }
    
    __int64 cfptr = Game::ObjectList_GetPtrLightsAndFog();
    ColorFilterRadialSettings::SetSettings(cfptr, &EditorGUI::editor_colorFilterRadial);
}
// --- utility ---

static inline void AngleDegToMemory(float angleDeg, float& outA, float& outB)
{
    const float PI = 3.14159265358979323846f;
    float rad = angleDeg * PI / 180.0f;
    float s = sinf(rad);
    float c = cosf(rad);
    outA = -s;
    outB = c;
}

static inline float MemoryToAngleDeg(float a, float b)
{
    const float PI = 3.14159265358979323846f;
    float s = -a;
    float c = b;
    float rad = atan2f(s, c);
    float deg = rad * 180.0f / PI;
    if (deg > 180.0f) deg -= 360.0f;
    if (deg <= -180.0f) deg += 360.0f;
    return deg;
}

static void DrawDirectionalColorWindow(bool* p_open, int pl1_frame, int pl2_frame)
{
    static int playerIndex = 0; // 0 => Player 1, 1 => Player 2
    static float gap = 0.5f;
    ImGui::SetNextWindowSize(ImVec2(370, 380), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Directional Color Filter Editor", p_open, ImGuiWindowFlags_NoCollapse))
    {
        ImGui::End();
        return;
    }

    // init once
    if (ImGui::IsWindowAppearing())
    {
        EditorGUI::editor_colorFilterDirectional.angleDeg = MemoryToAngleDeg(
            EditorGUI::editor_colorFilterDirectional.angle.x,
            EditorGUI::editor_colorFilterDirectional.angle.y
        );
        if (EditorGUI::editor_colorFilterDirectional.middlePoint == 0.0f)
            EditorGUI::editor_colorFilterDirectional.middlePoint = 0.5f;
        // gap: fraction of screen height used as FULL gap (default ~1/3)
        if (gap == 0.0f)
            gap = 1.0f / 3.0f;
    }

    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 6.0f);
    ImGui::BeginChild("header_child_dir", ImVec2(0, 40), false, ImGuiWindowFlags_NoScrollbar);
    ImGui::SetCursorPosX(8.0f);
    ImGui::Checkbox("Apply", &EditorGUI::editor_colorFilterDirectional.enable);
    ImGui::SameLine();
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 6.0f);

    ImGui::Dummy(ImVec2(0, 6));
    if (ImGui::Button("Output FCURVE", ImVec2(120, 0)))
    {
        int frame = 0;
        if (playerIndex == 0) {

            frame = pl1_frame;
        }
        else {

            frame = pl2_frame;
        }
        auto& s = EditorGUI::editor_colorFilterDirectional;
        AngleDegToMemory(s.angleDeg, s.angle.x, s.angle.y);
        Console::PrintOut("======COLOR DIRECTIONAL======\n");
        Console::PrintOutY("%d, %.6f, %.6f, %.6f, %.6f, "      // colorA.rgba
            "%.6f, %.6f, %.6f, %.6f, "                // colorB.rgba
            "%.6f, %.6f, %.6f, %.6f, "                // colorC.rgba
            "%.6f, %.6f, %.6f, %d,\n",               // memA, memB, middlePoint, alphaBlend
            frame,
            s.angle.x, s.angle.y,
            s.colorA.x, s.colorA.y, s.colorA.z, s.colorA.w,
            s.colorB.x, s.colorB.y, s.colorB.z, s.colorB.w,
            s.colorC.x, s.colorC.y, s.colorC.z, s.colorC.w,
            s.middlePoint, s.alphaBlend);
    }
    // combobox right after the button on the same row
    ImGui::SameLine();
    ImGui::PushItemWidth(120.0f);
    const char* players[] = { "Player 1", "Player 2" };
    ImGui::Combo("##player_select", &playerIndex, players, IM_ARRAYSIZE(players));
    ImGui::PopItemWidth();

    ImGui::PopStyleVar();
    ImGui::EndChild();

    ImGui::Columns(2, nullptr, false);
    float totalW = ImGui::GetWindowContentRegionMax().x - ImGui::GetWindowContentRegionMin().x;
    ImGui::SetColumnWidth(0, totalW * 0.60f);

    // compute geometry params early (for dynamic middle slider limits)
    ImGuiIO& io = ImGui::GetIO();
    ImVec2 screenSize = io.DisplaySize;
    float W = screenSize.x;
    float H = screenSize.y;


    // LEFT: controls
    ImGui::BeginChild("dir_controls", ImVec2(0, 0), true);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(6, 6));

   /* ImGui::TextUnformatted("Gap (fraction of screen height)");
    ImGui::SliderFloat("##dir_gap", &gap, 0.01f, 0.9f, "%.3f");*/

    ImGui::Spacing();
    ImGui::TextUnformatted("MID");
    // use dynamic bounds so slider stops when lines hit edges
    ImGui::SliderFloat("##dir_mid", &EditorGUI::editor_colorFilterDirectional.middlePoint, 0.0f, 1.0f, "%.3f");

    ImGui::Spacing();
    ImGui::TextUnformatted("Angle (degrees)");
    ImGui::SliderFloat("##dir_angle", &EditorGUI::editor_colorFilterDirectional.angleDeg, 0.0f, 360.0f, "%.1f");

    ImGui::Spacing();
    ImGui::TextUnformatted("Blend Type");
    ImGui::Indent(4.0f);
    ImGui::RadioButton("Normal", &EditorGUI::editor_colorFilterDirectional.alphaBlend, 1);
    ImGui::RadioButton("Add", &EditorGUI::editor_colorFilterDirectional.alphaBlend, 2);
    ImGui::RadioButton("Subtract", &EditorGUI::editor_colorFilterDirectional.alphaBlend, 3);
    ImGui::Unindent(4.0f);

    ImGui::PopStyleVar();
    ImGui::EndChild();

    // RIGHT: color pickers preview
    ImGui::NextColumn();
    float leftColW = ImGui::GetColumnWidth(0);
    float rightColW = totalW - leftColW;
    if (rightColW < 1.0f) rightColW = ImGui::GetColumnWidth(1);

    const float horizontalPadding = 16.0f;
    float maxPreview = rightColW - horizontalPadding;
    if (maxPreview < 32.0f) maxPreview = 32.0f;
    const float desiredPreview = 150.0f;
    const float previewSize = (maxPreview < desiredPreview) ? maxPreview : desiredPreview;

    ImGui::BeginChild("dir_colors_preview", ImVec2(0, 0), false);
    ImGui::PushItemWidth(previewSize);

    ImDrawList* win_draw = ImGui::GetWindowDrawList();
    const float rounding = 6.0f;
    const ImGuiColorEditFlags pickerFlags = ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoSidePreview;

    auto draw_color_block = [&](Vector4* colVec, const char* label, int idx)
        {
            ImGui::TextUnformatted(label);
            ImGui::Spacing();

            ImVec2 cursor = ImGui::GetCursorScreenPos();
            float colAvailW = ImGui::GetContentRegionAvail().x;
            float offsetX = (colAvailW - previewSize) * 0.5f;
            if (offsetX < 0.0f) offsetX = 0.0f;
            ImVec2 pos = ImVec2(cursor.x + offsetX, cursor.y);
            ImVec2 posEnd = ImVec2(pos.x + previewSize, pos.y + previewSize * 0.3f);

            ImVec4 colIm = ImVec4(colVec->x, colVec->y, colVec->z, colVec->w);
            ImU32 col = ImGui::ColorConvertFloat4ToU32(colIm);
            win_draw->AddRectFilled(pos, posEnd, col, rounding);
            win_draw->AddRect(pos, posEnd, IM_COL32(255, 255, 255, 120), rounding, 0, 2.0f);

            std::string btn_id = std::string("dir_col_btn_") + std::to_string(idx);
            ImGui::SetCursorScreenPos(pos);
            ImGui::InvisibleButton(btn_id.c_str(), ImVec2(previewSize, previewSize * 0.3f));
            ImGui::SetCursorScreenPos(ImVec2(cursor.x, cursor.y + previewSize * 0.3f + 6.0f));

            if (ImGui::IsItemClicked())
            {
                std::string popup_id = std::string("dir_col_popup_") + std::to_string(idx);
                ImGui::OpenPopup(popup_id.c_str());
            }

            std::string popup_id_begin = std::string("dir_col_popup_") + std::to_string(idx);
            if (ImGui::BeginPopup(popup_id_begin.c_str()))
            {
                ImGui::TextUnformatted(label);
                ImGui::Separator();
                std::string picker_id = std::string("##dir_picker_") + std::to_string(idx);
                ImGui::ColorPicker4(picker_id.c_str(), (float*)colVec, pickerFlags, nullptr);
                ImGui::EndPopup();
            }

            ImGui::Dummy(ImVec2(0.0f, 8.0f));
        };

    draw_color_block(&EditorGUI::editor_colorFilterDirectional.colorA, "Top layer", 0);
    draw_color_block(&EditorGUI::editor_colorFilterDirectional.colorB, "Middle layer", 1);
    draw_color_block(&EditorGUI::editor_colorFilterDirectional.colorC, "Bottom layer", 2);

    ImGui::PopItemWidth();
    ImGui::EndChild();

    ImGui::Columns(1);
    ImGui::End();
    // ===== Overlay: parallel lines (band) rotating about screen center =====
    ImDrawList* dl = ImGui::GetForegroundDrawList();

    // Viewport (screen space)
    ImGuiViewport* vp = ImGui::GetMainViewport();
    const ImVec2 vpPos = vp->Pos;
    const ImVec2 vpSize = vp->Size;
    const float  vw = vpSize.x;
    const float  vh = vpSize.y;
    const ImVec2 pivot = ImVec2(vw * 0.5f, vh * 0.5f);   // fixed rotation pivot (screen center)

    // Orientation
    const float PI = 3.14159265358979323846f;
    const float ang = EditorGUI::editor_colorFilterDirectional.angleDeg * (PI / 180.0f);
    const ImVec2 dir = ImVec2(cosf(ang), sinf(ang));      // tangent
    const ImVec2 nrm = ImVec2(-sinf(ang), cosf(ang));     // unit normal

    // Gap in pixels (still height-based)
    float gapFrac = ImClamp(gap, 0.01f, 0.90f);
    const float gapPx = gapFrac * vh;
    const float halfGapPx = 0.5f * gapPx;

    // --- MID uses BOTH width & height via the viewport span along the normal ---
    // Full span of the viewport along 'nrm': S = |n.x|*W + |n.y|*H
    const float S = fabsf(nrm.x) * vw + fabsf(nrm.y) * vh;

    // Inverted MID (as you asked earlier), linear 0..1
    float mid = ImClamp(EditorGUI::editor_colorFilterDirectional.middlePoint, 0.0f, 1.0f);
    //mid = 1.0f - mid;

    // Band center slides from touching one edge to the other:
    // s_min = sPivot - S/2, s_max = sPivot + S/2
    // center(mid) = lerp(s_min + halfGapPx, s_max - halfGapPx, mid)
    //             = sPivot + (mid - 0.5f) * (S - gapPx)
    const float sPivot = nrm.x * pivot.x + nrm.y * pivot.y;
    const float slideLen = ImMax(S - gapPx, 0.0f);                  // never negative
    const float sCenter = sPivot + (mid - 0.5f) * slideLen;

    // Lines
    const float s0 = sCenter - halfGapPx;   // first line
    const float s1 = sCenter + halfGapPx;   // second line

    // Clip a line (nrm·p == s) to the viewport rect (local coords: 0..W, 0..H)
    const ImVec2 corners[4] = { ImVec2(0,0), ImVec2(vw,0), ImVec2(vw,vh), ImVec2(0,vh) };
    auto clip_line = [&](float s, ImVec2& A, ImVec2& B)->bool {
        ImVec2 pts[4]; int pc = 0; const float eps = 1e-6f;
        for (int i = 0; i < 4; ++i) {
            ImVec2 P = corners[i], Q = corners[(i + 1) & 3], PQ = ImVec2(Q.x - P.x, Q.y - P.y);
            float den = nrm.x * PQ.x + nrm.y * PQ.y;
            if (fabsf(den) < eps) {
                float sp = nrm.x * P.x + nrm.y * P.y;
                if (fabsf(sp - s) < 1e-3f) { if (pc < 4) pts[pc++] = P; if (pc < 4) pts[pc++] = Q; }
                continue;
            }
            float t = (s - (nrm.x * P.x + nrm.y * P.y)) / den;
            if (t >= -1e-6f && t <= 1.0f + 1e-6f) {
                ImVec2 I = ImVec2(P.x + PQ.x * t, P.y + PQ.y * t);
                bool dup = false; for (int k = 0; k < pc; ++k)
                    if (fabsf(pts[k].x - I.x) < 1e-3f && fabsf(pts[k].y - I.y) < 1e-3f) { dup = true; break; }
                if (!dup && pc < 4) pts[pc++] = I;
            }
        }
        if (pc < 2) return false;
        // Take farthest pair along the direction to span the rect
        float minPr = FLT_MAX, maxPr = -FLT_MAX; ImVec2 Pmin = pts[0], Pmax = pts[0];
        for (int k = 0; k < pc; ++k) {
            float p = pts[k].x * dir.x + pts[k].y * dir.y;
            if (p < minPr) { minPr = p; Pmin = pts[k]; } if (p > maxPr) { maxPr = p; Pmax = pts[k]; }
        }
        A = Pmin; B = Pmax; return true;
        };

    ImVec2 a0, b0, a1, b1;
    if (clip_line(s0, a0, b0))
        dl->AddLine(ImVec2(vpPos.x + a0.x, vpPos.y + a0.y),
            ImVec2(vpPos.x + b0.x, vpPos.y + b0.y),
            IM_COL32(255, 255, 255, 200), 3.0f);
    if (clip_line(s1, a1, b1))
        dl->AddLine(ImVec2(vpPos.x + a1.x, vpPos.y + a1.y),
            ImVec2(vpPos.x + b1.x, vpPos.y + b1.y),
            IM_COL32(255, 255, 255, 200), 3.0f);

    // (settings commit unchanged)
    {
        auto& s = EditorGUI::editor_colorFilterDirectional;
        AngleDegToMemory(s.angleDeg, s.angle.x, s.angle.y);
        __int64 cfptr = Game::ObjectList_GetPtrLightsAndFog();
        ColorFilterDirectionalSettings::SetSettings(cfptr, &s);
    }




   
}


// предполагается, что Vector3 имеет поля x,y,z и конструктор Vector3(float,float,float)
static inline void Normalize3(Vector3& v) {
    float l = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    if (l > 1e-6f) { v.x /= l; v.y /= l; v.z /= l; }
    else { v.x = 0.f; v.y = 0.f; v.z = 1.f; }
}

static inline void EulerToDir(float pitch, float yaw, float roll, Vector3& out) {
    // pitch (X), yaw (Y), roll (Z) в градусах -> направляющий вектор
    const float D = 3.14159265358979323846f / 180.0f;
    float cx = cosf(pitch * D), sx = sinf(pitch * D);
    float cy = cosf(yaw * D), sy = sinf(yaw * D);
    float cz = cosf(roll * D), sz = sinf(roll * D);

    // используем форвард (0,0,1) и вращаем: простая композиция для визуально интуитивного поведения
    out.x = sy * cx + sz * sx * cy - cz * sx * sy; // упрощённая, но рабочая формула
    out.y = -sx * cy + sz * cz * cx;                 // приближённая
    out.z = cy * cx - sz * sx * sy;
    Normalize3(out);
}

static inline void DirToEuler(const Vector3& dir, float& pitch, float& yaw, float& roll) {
    float dx = dir.x, dy = dir.y, dz = dir.z;
    yaw = atan2f(dx, dz) * 180.0f / 3.14159265358979323846f;
    pitch = atan2f(-dy, std::sqrt(dx * dx + dz * dz)) * 180.0f / 3.14159265358979323846f;
    roll = 0.0f;
}

// Простой 2D gizmo (без матриц). Изменяет eulerDeg и возвращает направление в outDir.
static void DrawRotationGizmo2D(const char* id, ImVec2 size, float eulerDeg[3], Vector3& outDir) {
    ImGuiIO& io = ImGui::GetIO();
    ImDrawList* dl = ImGui::GetWindowDrawList();
    ImVec2 pos = ImGui::GetCursorScreenPos();
    ImVec2 center = ImVec2(pos.x + size.x * 0.5f, pos.y + size.y * 0.5f);
    ImGui::InvisibleButton(id, size);
    bool active = ImGui::IsItemActive();

    if (active && io.MouseDown[0]) {
        ImVec2 md = io.MouseDelta;
        eulerDeg[1] += md.x * 0.6f; // yaw
        eulerDeg[0] += md.y * 0.6f; // pitch
    }
    if (active && io.MouseDown[1]) {
        ImVec2 md = io.MouseDelta;
        eulerDeg[2] += md.x * 0.6f; // roll
    }
    if (eulerDeg[0] > 89.9f) eulerDeg[0] = 89.9f;
    if (eulerDeg[0] < -89.9f) eulerDeg[0] = -89.9f;

    EulerToDir(eulerDeg[0], eulerDeg[1], eulerDeg[2], outDir);

    dl->AddRectFilled(pos, ImVec2(pos.x + size.x, pos.y + size.y), ImGui::GetColorU32(ImGuiCol_FrameBg));
    dl->AddCircle(center, 4.0f, ImGui::GetColorU32(ImGuiCol_Border));

    // проекция трёх осей (эвристика)
    auto proj = [&](const Vector3& v)->ImVec2 {
        float scale = size.x * 0.35f;
        return ImVec2(center.x + v.x * scale, center.y - v.y * scale);
        };

    Vector3 vx, vy, vz;
    EulerToDir(eulerDeg[0], eulerDeg[1] - 90.0f, eulerDeg[2], vx);
    EulerToDir(eulerDeg[0] + 90.0f, eulerDeg[1], eulerDeg[2], vy);
    EulerToDir(eulerDeg[0], eulerDeg[1], eulerDeg[2], vz);

    ImU32 colX = IM_COL32(255, 80, 80, 255);
    ImU32 colY = IM_COL32(80, 255, 80, 255);
    ImU32 colZ = IM_COL32(120, 140, 255, 255);

    ImVec2 pX = proj(vx), pY = proj(vy), pZ = proj(vz);
    dl->AddLine(center, pX, colX, 3.0f);
    dl->AddLine(center, pY, colY, 3.0f);
    dl->AddLine(center, pZ, colZ, 3.0f);

    auto draw_head = [&](ImVec2 a, ImVec2 b, ImU32 col) {
        ImVec2 dir = ImVec2(b.x - a.x, b.y - a.y);
        float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        if (len < 1e-6f) return;
        dir.x /= len; dir.y /= len;
        ImVec2 perp = ImVec2(-dir.y, dir.x);
        float s = 8.0f;
        dl->AddTriangleFilled(b, ImVec2(b.x - dir.x * s + perp.x * (s * 0.6f), b.y - dir.y * s + perp.y * (s * 0.6f)),
            ImVec2(b.x - dir.x * s - perp.x * (s * 0.6f), b.y - dir.y * s - perp.y * (s * 0.6f)), col);
        };
    draw_head(center, pX, colX);
    draw_head(center, pY, colY);
    draw_head(center, pZ, colZ);

    ImGui::SetCursorScreenPos(ImVec2(pos.x, pos.y + size.y + 4));
    ImGui::TextDisabled("Left-drag: yaw/pitch  Right-drag: roll");
    ImGui::SetCursorScreenPos(ImVec2(pos.x + size.x, pos.y));
}
// helper: build orthonormal basis from Euler (degrees). pitch=X, yaw=Y, roll=Z
static inline void EulerToBasis(float pitch, float yaw, float roll, Vector3& vx, Vector3& vy, Vector3& vz) {
    const float D = 3.14159265358979323846f / 180.0f;
    float cx = cosf(pitch * D), sx = sinf(pitch * D);
    float cy = cosf(yaw * D), sy = sinf(yaw * D);
    float cz = cosf(roll * D), sz = sinf(roll * D);

    // compute R = Rz * Rx * Ry (see derivation)
    float R00 = cz * cy - sz * (sx * sy);
    float R01 = -sz * cx;
    float R02 = cz * sy + sz * (sx * cy);

    float R10 = sz * cy + cz * (sx * sy);
    float R11 = cz * cx;
    float R12 = sz * sy - cz * (sx * cy);

    float R20 = -cx * sy;
    float R21 = sx;
    float R22 = cx * cy;

    // columns of R are basis vectors for X,Y,Z in world
    vx.x = R00; vx.y = R10; vx.z = R20;
    vy.x = R01; vy.y = R11; vy.z = R21;
    vz.x = R02; vz.y = R12; vz.z = R22;

    // normalize just in case of FP drift
    auto norm = [](Vector3& v) {
        float l = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
        if (l > 1e-6f) { v.x /= l; v.y /= l; v.z /= l; }
        };
    norm(vx); norm(vy); norm(vz);
}

// Draw spherical gizmo with axis markers and arrows inside sphere.
// added param normalizeDir default true (keeps backward compatible)
static void DrawRotationSphereGizmo(const char* id, ImVec2 size, float eulerDeg[3], Vector3& outDir, bool normalizeDir = true) {
    ImGuiIO& io = ImGui::GetIO();
    ImDrawList* dl = ImGui::GetWindowDrawList();
    ImVec2 pos = ImGui::GetCursorScreenPos();
    ImVec2 center = ImVec2(pos.x + size.x * 0.5f, pos.y + size.y * 0.5f);
    float radius = fminf(size.x, size.y) * 0.45f;

    ImGui::InvisibleButton(id, size);
    bool active = ImGui::IsItemActive();

    // mouse control
    if (active && io.MouseDown[0]) {
        ImVec2 md = io.MouseDelta;
        eulerDeg[1] += md.x * 0.6f; // yaw
        eulerDeg[0] += md.y * 0.6f; // pitch
    }
    if (active && io.MouseDown[1]) {
        ImVec2 md = io.MouseDelta;
        eulerDeg[2] += md.x * 0.6f; // roll
    }
    if (eulerDeg[0] > 89.9f) eulerDeg[0] = 89.9f;
    if (eulerDeg[0] < -89.9f) eulerDeg[0] = -89.9f;

    // build orthonormal basis
    Vector3 vx, vy, vz;
    EulerToBasis(eulerDeg[0], eulerDeg[1], eulerDeg[2], vx, vy, vz);

    // output forward
    outDir.x = vz.x; outDir.y = vz.y; outDir.z = vz.z;
    if (normalizeDir) {
        float l = sqrtf(outDir.x * outDir.x + outDir.y * outDir.y + outDir.z * outDir.z);
        if (l > 1e-6f) { outDir.x /= l; outDir.y /= l; outDir.z /= l; }
    }

    // draw sphere (true circle)
    dl->AddCircleFilled(center, radius, ImGui::GetColorU32(ImGuiCol_FrameBg));
    dl->AddCircle(center, radius, ImGui::GetColorU32(ImGuiCol_Border), 64, 1.0f);

    // projection (orthographic). no non-uniform scaling -> no squish
    auto proj = [&](const Vector3& v, float depthScale = 1.0f)->ImVec2 {
        return ImVec2(center.x + v.x * radius * depthScale, center.y - v.y * radius * depthScale);
        };

    // axis points
    ImVec2 pX = proj(vx);
    ImVec2 pY = proj(vy);
    ImVec2 pZ = proj(vz);

    // draw small axes lines inside sphere (from center towards axis)
    float lineLen = radius * 0.72f;
    ImVec2 lX = ImVec2(center.x + vx.x * lineLen, center.y - vx.y * lineLen);
    ImVec2 lY = ImVec2(center.x + vy.x * lineLen, center.y - vy.y * lineLen);
    ImVec2 lZ = ImVec2(center.x + vz.x * lineLen, center.y - vz.y * lineLen);

    ImU32 colX = IM_COL32(255, 80, 80, 255);
    ImU32 colY = IM_COL32(80, 255, 80, 255);
    ImU32 colZ = IM_COL32(120, 140, 255, 255);

    dl->AddLine(center, lX, colX, 2.5f);
    dl->AddLine(center, lY, colY, 2.5f);
    dl->AddLine(center, lZ, colZ, 2.5f);

    // arrow heads (small triangles) at end of lines
    auto draw_arrow_head = [&](ImVec2 a, ImVec2 b, ImU32 color) {
        ImVec2 dir = ImVec2(b.x - a.x, b.y - a.y);
        float len = sqrtf(dir.x * dir.x + dir.y * dir.y);
        if (len < 1e-5f) return;
        dir.x /= len; dir.y /= len;
        ImVec2 perp = ImVec2(-dir.y, dir.x);
        float s = radius * 0.06f; // size relative to gizmo
        dl->AddTriangleFilled(b,
            ImVec2(b.x - dir.x * s + perp.x * (s * 0.6f), b.y - dir.y * s + perp.y * (s * 0.6f)),
            ImVec2(b.x - dir.x * s - perp.x * (s * 0.6f), b.y - dir.y * s - perp.y * (s * 0.6f)),
            color);
        };

    draw_arrow_head(center, lX, colX);
    draw_arrow_head(center, lY, colY);
    draw_arrow_head(center, lZ, colZ);

    // dots slightly outside line ends to emphasize
    float dotBase = radius * 0.07f;
    float depthFactorZ = (vz.z + 1.0f) * 0.25f; // in [0,0.5]
    float dotX = dotBase * (1.0f + vx.z * 0.35f);
    float dotY = dotBase * (1.0f + vy.z * 0.35f);
    float dotZ = dotBase * (1.0f + vz.z * 0.35f);
    dl->AddCircleFilled(pX, dotX, colX);
    dl->AddCircleFilled(pY, dotY, colY);
    dl->AddCircleFilled(pZ, dotZ, colZ);

    // labels
    ImVec2 labelOffset = ImVec2(6, -6);
    dl->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(pX.x + labelOffset.x, pX.y + labelOffset.y), colX, "X");
    dl->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(pY.x + labelOffset.x, pY.y + labelOffset.y), colY, "Y");
    dl->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(pZ.x + labelOffset.x, pZ.y + labelOffset.y), colZ, "Z");

    // hint
    ImGui::SetCursorScreenPos(ImVec2(pos.x, pos.y + size.y + 4));
    ImGui::TextDisabled("Left-drag: yaw/pitch  Right-drag: roll");
    ImGui::SetCursorScreenPos(ImVec2(pos.x + size.x, pos.y));
}
// Главное окно. Не читает память; пишет через LightShadowSettings::SetSettings при enable==true или при Commit.
static void DrawLightSettingsWindow(bool* p_open) {
    __int64 lightPtr = Game::ObjectList_GetPtrLightsAndShadow();
    if (!p_open) return;
    if (!ImGui::Begin("Light & Shadow Settings", p_open)) { ImGui::End(); return; }

    LightShadowSettings& S = EditorGUI::editor_lightShadow;

    // Light color
    float lightColor[3] = { S.LightColor.x, S.LightColor.y, S.LightColor.z };
    if (ImGui::ColorEdit3("Light Color", lightColor, ImGuiColorEditFlags_Float)) {
        S.LightColor.x = lightColor[0];
        S.LightColor.y = lightColor[1];
        S.LightColor.z = lightColor[2];
        if (S.enable && lightPtr) LightShadowSettings::SetSettings(lightPtr, &S);
    }

    ImGui::Separator();

    // Ambient color
    float ambientColor[3] = { S.AmbientColor.x, S.AmbientColor.y, S.AmbientColor.z };
    if (ImGui::ColorEdit3("Ambient Color", ambientColor, ImGuiColorEditFlags_Float)) {
        S.AmbientColor.x = ambientColor[0];
        S.AmbientColor.y = ambientColor[1];
        S.AmbientColor.z = ambientColor[2];
        if (S.enable && lightPtr) LightShadowSettings::SetSettings(lightPtr, &S);
    }

    ImGui::Separator();

    // Fog color
    float fogColor[3] = { S.FogColor.x, S.FogColor.y, S.FogColor.z };
    if (ImGui::ColorEdit3("Fog Color", fogColor, ImGuiColorEditFlags_Float)) {
        S.FogColor.x = fogColor[0];
        S.FogColor.y = fogColor[1];
        S.FogColor.z = fogColor[2];
        if (S.enable && lightPtr) LightShadowSettings::SetSettings(lightPtr, &S);
    }

    ImGui::Separator();

    // Light direction (save changes)
    float ldir[3] = { S.LightDirection.x, S.LightDirection.y, S.LightDirection.z };
    if (ImGui::InputFloat3("Light Dir", ldir)) {
        S.LightDirection.x = ldir[0];
        S.LightDirection.y = ldir[1];
        S.LightDirection.z = ldir[2];
        if (S.enable && lightPtr) LightShadowSettings::SetSettings(lightPtr, &S);
    }

    // Apply checkbox
    if (ImGui::Checkbox("Apply", &S.enable)) {
        if (S.enable && lightPtr) LightShadowSettings::SetSettings(lightPtr, &S);
    }

    // Ensure settings are written each frame while enabled
    if (lightPtr) {
        LightShadowSettings::SetSettings(lightPtr, &S);
    }

    ImGui::End();
}