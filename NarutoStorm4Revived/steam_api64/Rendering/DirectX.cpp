#include "DirectX.h"
#include <Shlwapi.h>

#include <wrl.h>
#include <d3d11.h>
#include <d3d12.h>
#include <D3Dcompiler.h>
#include <dxgi.h>
#include <dxgiformat.h>
#include <iostream>

#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "D3Dcompiler.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "winmm.lib")

#include "EditorGUI.h"
#include "UltimateStormAPI.h"
#include "Common.h"

// Main D3D11 Objects
ID3D11DeviceContext *pContext = NULL;
ID3D11Device *pDevice = NULL;
ID3D11RenderTargetView *mainRenderTargetView;
static IDXGISwapChain*  pSwapChain = NULL;
HWND window = nullptr;
BOOL g_bInitialised = false;

__int64 DirectX::dxgiAddress = 0;
char DirectX::UnhookDxgi[19];

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
	case WM_SIZE:
		if (pDevice != NULL && wParam != SIZE_MINIMIZED)
		{
			/*if (mainRenderTargetView) { mainRenderTargetView->Release(); mainRenderTargetView = NULL; }

			pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);

			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();*/
		}
		return 0;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
		break;
	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0;
	}
	return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

__int64 test = 0;
__int64 DirectX::theWindow = 0;
ImGuiContext* DirectX::guiContext;
__int64 realPresent = 0;
bool DirectX::isHookDone = false;
__int64 DirectX::DxgiHook(__int64 ppSwapChain, int a2, int a3)
{
	// 1FE0
	if (g_bInitialised == false)
	{
		g_bInitialised = true;

		// Do all the garbage:
		pSwapChain = (IDXGISwapChain*)ppSwapChain;
	
		std::cout << "UltimateStormAPI :: Hooked DX11" << std::endl;
		std::cout << "D3D SwapChain: " << std::hex << (__int64)pSwapChain << std::endl;

		pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)(&pDevice));
		std::cout << "D3D Device: " << std::hex << (__int64)pDevice << std::endl;

		pDevice->GetImmediateContext((&pContext));
		std::cout << "D3D Context: " << std::hex << (__int64)pContext << std::endl;

		ID3D11Texture2D* pBackBuffer;
		pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));

		ID3D11DepthStencilView* oldDSV = NULL;
		pContext->OMGetRenderTargets(0, &mainRenderTargetView, &oldDSV);

		pBackBuffer->Release();

		// IMGUI SPECIFIC
		DXGI_SWAP_CHAIN_DESC desc;
		pSwapChain->GetDesc(&desc);
		theWindow = (__int64)(desc.OutputWindow);

		IMGUI_CHECKVERSION();
		guiContext = ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		ImGui::StyleColorsDark();
		ImGui_ImplWin32_Init((HWND)theWindow);
		ImGui_ImplDX11_Init(pDevice, pContext);

		//test = GetWindowLongPtr((HWND)theWindow, GWLP_WNDPROC);

		//bool show_demo_window = true;
		//bool show_another_window = true;
		//ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		ImGui_ImplDX11_InvalidateDeviceObjects();
		ImGui_ImplDX11_CreateDeviceObjects();

	}

	if (GetAsyncKeyState(VK_F10) & 0x01) //Key for opening API Menu
	{
		EditorGUI::Show = !EditorGUI::Show;

		if (EditorGUI::Show == true)
		{
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			io.WantCaptureMouse = true;
			SetWindowLongPtr((HWND)theWindow, GWLP_WNDPROC, (LONG_PTR)WndProc);
		}
		else
		{
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			io.WantCaptureMouse = false;
			SetWindowLongPtr((HWND)theWindow, GWLP_WNDPROC, (LONG_PTR)test);
		}
	}

	ShowCursor(true);

	if (false)
	{
		MSG msg;
		while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}

	// Do pre-render
	UltimateStormAPI::PreRender();
	if (GameVersion && (std::strcmp(GameVersion, "1.60") == 0 || std::strcmp(GameVersion, "1.09") == 0)) {
		EditorGUI::LoopGUI();
	}
	

	// Do real present function
	typedef __int64(__fastcall * fc)(__int64 ppSwapChain, int a2, int a3);
	fc f = (fc)(realPresent);
	__int64 result = f(ppSwapChain, a2, a3);

	// Do post-render
	UltimateStormAPI::PostRender();

	//ImGui_ImplDX11_InvalidateDeviceObjects();
	//ImGui_ImplDX11_CreateDeviceObjects();

	return result;
}

void DirectX::HookVtable(__int64 ppSwapChain)
{
	if (realPresent) return;

	std::cout << "DirectHook :: Hooking" << std::endl;

	if (!ppSwapChain) return;
	__int64 vtable = *(__int64*)(ppSwapChain);
	if (!*(__int64*)vtable) return;

	__int64 present = vtable + 64;

	DWORD dwOld = 0;
	VirtualProtect((void*)(present), 8, PAGE_EXECUTE_READWRITE, &dwOld);
	realPresent = *(__int64*)present;
	isHookDone = true;
	*(__int64*)(present) = (__int64)(DirectX::DxgiHook);
	VirtualProtect((void*)(present), 8, dwOld, &dwOld);
}


#include <cstdint>
#include <windows.h>

__int64 DirectX::GetSwapChain()
{
	// 64-bit     ULL
	const uint64_t Storm4SwapChain = 0x148D32FD0ULL;
	const uint64_t Storm4DebugSwapChain = 0x149099E48ULL;
	const uint64_t StormCSwapChain = 0x149717A80ULL;
	const uint64_t ModuleBaseOffset = 0x140000C00ULL; //     

	auto tryGet = [&](uint64_t offset) -> __int64
		{
			__int64 result = 0;

			__try
			{
				//    
				uint64_t addr = static_cast<uint64_t>(moduleBase) + offset - ModuleBaseOffset;
				if (addr == 0) return 0;

				//     
				uint64_t mmInst = *reinterpret_cast<uint64_t*>(addr);
				if (mmInst == 0) return 0;

				//    +8     
				uint64_t ptr_at_plus8 = *reinterpret_cast<uint64_t*>(mmInst + 8);
				if (ptr_at_plus8 == 0) return 0;

				//      : **(__int64**)(mmInst + 8)
				//    ,   
				uint64_t first_deref = *reinterpret_cast<uint64_t*>(ptr_at_plus8);
				if (first_deref == 0) return 0;

				//     +32     
				uint64_t func_ptr_addr = first_deref + 32;
				if (func_ptr_addr == 0) return 0;

				uint64_t pSwapChain_funct = *reinterpret_cast<uint64_t*>(func_ptr_addr);
				if (pSwapChain_funct == 0) return 0;

				//          *(__int64*)(mmInst + 8)
				uint64_t pSwapChain_param = ptr_at_plus8;
				if (pSwapChain_param == 0) return 0;

				//    (fastcall       )
				using Fn_t = uint64_t(__fastcall*)(uint64_t);
				Fn_t fn = reinterpret_cast<Fn_t>(pSwapChain_funct);
				uint64_t pSwapChainVar = fn(pSwapChain_param);
				if (pSwapChainVar == 0) return 0;

				//  : actualSwapChain = *(__int64*)(pSwapChainVar + 96)
				uint64_t actualSwapChain = *reinterpret_cast<uint64_t*>(pSwapChainVar + 96);
				if (actualSwapChain == 0) return 0;

				result = static_cast<__int64>(actualSwapChain);
			}
			__except (EXCEPTION_EXECUTE_HANDLER)
			{
				//  AV    0  
				return 0;
			}

			return result;
		};

	//   
	__int64 swapChain = tryGet(Storm4SwapChain);
	if (swapChain) return swapChain;

	//       
	swapChain = tryGet(StormCSwapChain);
	if (swapChain) return swapChain;

	//       
	swapChain = tryGet(Storm4DebugSwapChain);
	return swapChain;
}

