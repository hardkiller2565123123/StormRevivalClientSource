#pragma once
#include "Vector3.h"
#include "Common.h"

class CommonRender
{
public:


	static void __fastcall ccEnableColorFilterRadial(int a1, int a2, int a3, int a4, float a5, float a6, int a7, float a8, float a9)
	{

		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

			typedef void(__fastcall* funct)(int a1, int a2, int a3, int a4, float a5, float a6, int a7, float a8, float a9);
			funct fc = (funct)(moduleBase + 0x5B4650);
			return fc(a1,a2,a3,a4,a5,a6,a7,a8,a9);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			typedef void(__fastcall* funct)(int a1, int a2, int a3, int a4, float a5, float a6, int a7, float a8, float a9);
			funct fc = (funct)(moduleBase + 0x536500); //S4
			return fc(a1, a2, a3, a4, a5, a6, a7, a8, a9);
		}

	}

};

class BlurSettings
{
public:
	bool enable = false;
	int type = 0;
	Vector2 DirectionCenterXY = Vector2(1.0f, 0.0f);
	Vector2 RadialPosXY = Vector2(50.0f, 50.0f);
	float width = 1;
	float alpha = 1;
	int blurAccuracy = 0;



	static void SetSettings(__int64 lightsAndFogPtr, BlurSettings* settings)
	{
		__int64 ptr = lightsAndFogPtr;
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {


			*(bool*)(ptr + 0x570) = settings->enable;
			*(float*)(ptr + 0x574) = settings->type;
			if (settings->type == 0) {

				*(float*)(ptr + 0x578) = settings->RadialPosXY.x;
				*(float*)(ptr + 0x57C) = settings->RadialPosXY.y;
			}
			else {

				*(float*)(ptr + 0x578) = settings->DirectionCenterXY.x;
				*(float*)(ptr + 0x57C) = settings->DirectionCenterXY.y;
			}
			*(float*)(ptr + 0x580) = settings->width;
			*(float*)(ptr + 0x584) = settings->alpha;
			*(float*)(ptr + 0x588) = settings->blurAccuracy;
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			*(bool*)(ptr + 0x6D8) = settings->enable;
			*(float*)(ptr + 0x6DC) = settings->type;
			if (settings->type == 0) {

				*(float*)(ptr + 0x6E0) = settings->RadialPosXY.x;
				*(float*)(ptr + 0x6E4) = settings->RadialPosXY.y;
			}
			else {

				*(float*)(ptr + 0x6E0) = settings->DirectionCenterXY.x;
				*(float*)(ptr + 0x6E4) = settings->DirectionCenterXY.y;
			}
			*(float*)(ptr + 0x6E8) = settings->width;
			*(float*)(ptr + 0x6EC) = settings->alpha;
			*(float*)(ptr + 0x6F0) = settings->blurAccuracy;
		}

	}
};


class GlareSettings
{
public:
	bool enable = true;
	float luminanceThreshold = 0.5f;
	float subtractedValue = 0.3f;
	float CompositionStrength = 1;



	static void SetSettings(__int64 lightsAndFogPtr, GlareSettings* settings)
	{
		__int64 ptr = lightsAndFogPtr;
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {


			*(bool*)(ptr + 0x430) = settings->enable;
			*(float*)(ptr + 0x434) = settings->luminanceThreshold;
			*(float*)(ptr + 0x438) = settings->subtractedValue;
			*(float*)(ptr + 0x43C) = settings->CompositionStrength;
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			*(bool*)(ptr + 0x5A0) = settings->enable;
			*(float*)(ptr + 0x5A4) = settings->luminanceThreshold;
			*(float*)(ptr + 0x5A8) = settings->subtractedValue;
			*(float*)(ptr + 0x5AC) = settings->CompositionStrength;
		}

	}
};

class BrightnessContrastSettings
{
public:
	bool enable = true;
	float brightness = 0;
	float contrast = 1;
	


	static void SetSettings(__int64 lightsAndFogPtr, BrightnessContrastSettings* settings)
	{
		__int64 ptr = lightsAndFogPtr;
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {


			*(bool*)(ptr + 0x15D0) = settings->enable;
			*(float*)(ptr + 0x15D4) = settings->brightness;
			*(float*)(ptr + 0x15D8) = settings->contrast;
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			*(bool*)(ptr + 0x1740) = settings->enable;
			*(float*)(ptr + 0x1744) = settings->brightness;
			*(float*)(ptr + 0x1748) = settings->contrast;
		}

	}
};

class ColorConvertSettings
{
public:
	bool enable = true;
	float opacity = 0;
	int mode = 3;
	Vector2 ColorBR = Vector2(0.0f, 0.0f);
	

	static void SetSettings(__int64 lightsAndFogPtr, ColorConvertSettings* settings)
	{
		__int64 ptr = lightsAndFogPtr;
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {


			*(bool*)(ptr + 0x618) = settings->enable;
			*(float*)(ptr + 0x61C) = settings->mode;
			*(float*)(ptr + 0x620) = settings->opacity;
			*(float*)(ptr + 0x624) = settings->ColorBR.x;
			*(float*)(ptr + 0x628) = settings->ColorBR.y;
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			*(bool*)(ptr + 0x780) = settings->enable;
			*(float*)(ptr + 0x784) = settings->mode;
			*(float*)(ptr + 0x788) = settings->opacity;
			*(float*)(ptr + 0x78C) = settings->ColorBR.x;
			*(float*)(ptr + 0x790) = settings->ColorBR.y;
		}

	}
};


class ColorFilterDirectionalSettings
{
public:
	bool enable = false;
	float angleDeg = 0;
	Vector2 angle = Vector2(0.0f, 1.0f);
	int alphaBlend = 1;
	Vector4 colorA = Vector4(1.0f, 0.0f, 0.0f, 0.0f);
	Vector4 colorB = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
	Vector4 colorC = Vector4(0.0f, 0.0f, 1.0f, 0.0f);
	float middlePoint = 0.5f;

	static void SetSettings(__int64 lightsAndFogPtr, ColorFilterDirectionalSettings* settings)
	{
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

			__int64 ptr = lightsAndFogPtr;

			*(bool*)(ptr + 0xB10) = settings->enable;
			*(int*)(ptr + 0xB14) = settings->alphaBlend;
			*(Vector4*)(ptr + 0xB20) = settings->colorA;
			*(Vector4*)(ptr + 0xB30) = settings->colorB;
			*(Vector4*)(ptr + 0xB40) = settings->colorC;
			*(float*)(ptr + 0xB50) = settings->angle.x;
			*(float*)(ptr + 0xB54) = settings->angle.y;
			*(float*)(ptr + 0xB58) = settings->middlePoint;
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			__int64 ptr = lightsAndFogPtr;

			*(bool*)(ptr + 0xC80) = settings->enable;
			*(int*)(ptr + 0xC84) = settings->alphaBlend;
			*(Vector4*)(ptr + 0xC90) = settings->colorA;
			*(Vector4*)(ptr + 0xCA0) = settings->colorB;
			*(Vector4*)(ptr + 0xCB0) = settings->colorC;
			*(float*)(ptr + 0xCC0) = settings->angle.x;
			*(float*)(ptr + 0xCC4) = settings->angle.y;
			*(float*)(ptr + 0xCC8) = settings->middlePoint;
		}
		
	}
};

class ColorFilterRadialSettings
{
public:
	bool enable = false;
	int alphaBlend = 1;
	Vector4 colorA = Vector4(1.0f, 0.0f, 0.0f, 0.0f);
	Vector4 colorB = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
	Vector4 colorC = Vector4(0.0f, 0.0f, 1.0f, 0.0f);
	Vector2 position = Vector2(0.5f, 0.5f);
	Vector2 scale = Vector2(1.0f, 1.0f);
	float middlePoint = 0.5f;

	static void SetSettings(__int64 lightsAndFogPtr, ColorFilterRadialSettings* settings)
	{
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

			__int64 ptr = lightsAndFogPtr;

			*(bool*)(ptr + 0x690) = settings->enable;
			*(int*)(ptr + 0x694) = settings->alphaBlend;
			*(Vector4*)(ptr + 0x6A0) = settings->colorA;
			*(Vector4*)(ptr + 0x6B0) = settings->colorB;
			*(Vector4*)(ptr + 0x6C0) = settings->colorC;
			*(Vector2*)(ptr + 0x6D0) = settings->position;
			*(Vector2*)(ptr + 0x6D8) = settings->scale;
			*(float*)(ptr + 0x6E0) = settings->middlePoint;
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			__int64 ptr = lightsAndFogPtr;

			*(bool*)(ptr + 0x800) = settings->enable;
			*(int*)(ptr + 0x804) = settings->alphaBlend;
			*(Vector4*)(ptr + 0x810) = settings->colorA;
			*(Vector4*)(ptr + 0x820) = settings->colorB;
			*(Vector4*)(ptr + 0x830) = settings->colorC;
			*(Vector2*)(ptr + 0x840) = settings->position;
			*(Vector2*)(ptr + 0x848) = settings->scale;
			*(float*)(ptr + 0x850) = settings->middlePoint;
		}

	}
};



class LightShadowSettings
{
public:
	bool enable = false;
	Vector3 AmbientColor = Vector3(1.0f, 1.0f, 1.0f);
	Vector3 LightColor = Vector3(1.0f, 1.0f, 1.0f);
	Vector3 FogColor = Vector3(1.0f, 1.0f, 1.0f);
	Vector3 LightDirection = Vector3(1.0f, 1.0f, 1.0f);
	Vector3 ShadowDirection = Vector3(1.0f, 1.0f, 1.0f);

	static void SetSettings(__int64 lightsAndshadowPtr, LightShadowSettings* settings)
	{
		if (!lightsAndshadowPtr || !settings) return;
		char* base = reinterpret_cast<char*>(lightsAndshadowPtr);

		// Read from game memory into settings when Apply (enable) == false
		if (!settings->enable) {
			if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
				settings->AmbientColor.x = *reinterpret_cast<float*>(base + 0);
				settings->AmbientColor.y = *reinterpret_cast<float*>(base + 4);
				settings->AmbientColor.z = *reinterpret_cast<float*>(base + 8);

				settings->LightColor.x = *reinterpret_cast<float*>(base + 112);
				settings->LightColor.y = *reinterpret_cast<float*>(base + 116);
				settings->LightColor.z = *reinterpret_cast<float*>(base + 120);

				settings->LightDirection.x = *reinterpret_cast<float*>(base + 144);
				settings->LightDirection.y = *reinterpret_cast<float*>(base + 148);
				settings->LightDirection.z = *reinterpret_cast<float*>(base + 152);

				settings->FogColor.x = *reinterpret_cast<float*>(base + 192);
				settings->FogColor.y = *reinterpret_cast<float*>(base + 196);
				settings->FogColor.z = *reinterpret_cast<float*>(base + 200);
			}
			else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
				settings->AmbientColor.x = *reinterpret_cast<float*>(base + 0);
				settings->AmbientColor.y = *reinterpret_cast<float*>(base + 4);
				settings->AmbientColor.z = *reinterpret_cast<float*>(base + 8);

				settings->LightColor.x = *reinterpret_cast<float*>(base + 112);
				settings->LightColor.y = *reinterpret_cast<float*>(base + 116);
				settings->LightColor.z = *reinterpret_cast<float*>(base + 120);

				settings->LightDirection.x = *reinterpret_cast<float*>(base + 144);
				settings->LightDirection.y = *reinterpret_cast<float*>(base + 148);
				settings->LightDirection.z = *reinterpret_cast<float*>(base + 152);

				settings->FogColor.x = *reinterpret_cast<float*>(base + 192);
				settings->FogColor.y = *reinterpret_cast<float*>(base + 196);
				settings->FogColor.z = *reinterpret_cast<float*>(base + 200);
			}
			return; //    
		}

		// Write settings -> game memory when enabled
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
			*reinterpret_cast<float*>(base + 0) = settings->AmbientColor.x;
			*reinterpret_cast<float*>(base + 4) = settings->AmbientColor.y;
			*reinterpret_cast<float*>(base + 8) = settings->AmbientColor.z;

			*reinterpret_cast<float*>(base + 112) = settings->LightColor.x;
			*reinterpret_cast<float*>(base + 116) = settings->LightColor.y;
			*reinterpret_cast<float*>(base + 120) = settings->LightColor.z;

			*reinterpret_cast<float*>(base + 144) = settings->LightDirection.x;
			*reinterpret_cast<float*>(base + 148) = settings->LightDirection.y;
			*reinterpret_cast<float*>(base + 152) = settings->LightDirection.z;

			*reinterpret_cast<float*>(base + 192) = settings->FogColor.x;
			*reinterpret_cast<float*>(base + 196) = settings->FogColor.y;
			*reinterpret_cast<float*>(base + 200) = settings->FogColor.z;
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
			*reinterpret_cast<float*>(base + 0) = settings->AmbientColor.x;
			*reinterpret_cast<float*>(base + 4) = settings->AmbientColor.y;
			*reinterpret_cast<float*>(base + 8) = settings->AmbientColor.z;

			*reinterpret_cast<float*>(base + 112) = settings->LightColor.x;
			*reinterpret_cast<float*>(base + 116) = settings->LightColor.y;
			*reinterpret_cast<float*>(base + 120) = settings->LightColor.z;

			*reinterpret_cast<float*>(base + 144) = settings->LightDirection.x;
			*reinterpret_cast<float*>(base + 148) = settings->LightDirection.y;
			*reinterpret_cast<float*>(base + 152) = settings->LightDirection.z;

			*reinterpret_cast<float*>(base + 192) = settings->FogColor.x;
			*reinterpret_cast<float*>(base + 196) = settings->FogColor.y;
			*reinterpret_cast<float*>(base + 200) = settings->FogColor.z;
		}
	}
};