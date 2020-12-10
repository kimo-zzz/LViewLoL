#pragma once
#include "Structs.h"
#include "LeagueMemoryReader.h"
#include "BaseView.h"

#include <chrono>
#include <map>
#include <list>

#include "windows.h"
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"

#include <d3d9.h>
#include <dinput.h>


using namespace std::chrono;

struct ViewBenchmark {
	float drawSettingsMs;
	float drawPanelMs;
	float drawWorldOverlayMs;
	float drawMinimapOverlayMs;
};

struct UIBenchmark {
	float renderTimeMs;
};

class UI {

public:
	               UI(std::list<BaseView*> views);
	void           Start();
	void           Update(LeagueMemoryReader& reader);

private:
	bool           CreateDeviceD3D(HWND hWnd);
	void           CleanupDeviceD3D();
	static void    ResetDevice();
	static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private: 
	HWND                               hWindow;

	Renderer                           renderer;
	std::list<BaseView*>               views;

	// DirectX stuff
	static LPDIRECT3D9                 g_pD3D;
	static LPDIRECT3DDEVICE9           g_pd3dDevice;
	static D3DPRESENT_PARAMETERS       g_d3dpp;

public:

	/* Font sizes are not dynamic in imgui so we have to create separate fonts */
	ImFontConfig                       fontConfigSmall;
	ImFontConfig                       fontConfigNormal;
	ImFont*                            fontSmall;
	ImFont*                            fontNormal;

	/* Contains general benchmarking for the registered views */
	std::map<BaseView*, ViewBenchmark> viewBenchmarks;
	UIBenchmark                        generalBenchmarks;

};