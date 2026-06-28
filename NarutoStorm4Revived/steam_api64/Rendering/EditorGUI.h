#pragma once

#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "CommonRender.h"

class EditorGUI
{
public:
	static bool Show;
	static bool HideHudDuringUJ;
	static void LoopGUI();
	static bool WindowList[100];
	static float editor_cameraWindowPos[3];
	static float editor_cameraWindowLook[3];
	static bool editor_cameraWindowEnableCam;
	static int editor_cameraWindowMode;

	static void InitGUI();
	static bool showHelpWindow;
	static ColorFilterDirectionalSettings editor_colorFilterDirectional;
	static ColorFilterRadialSettings editor_colorFilterRadial;
	static ColorConvertSettings editor_colorConverter;
	static BrightnessContrastSettings editor_brightnessContrast;
	static BlurSettings editor_blur;
	static GlareSettings editor_glareConfig;
	static LightShadowSettings editor_lightShadow;


};

