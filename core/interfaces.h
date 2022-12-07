#pragma once
#include "../utils/imgui/imgui.h"
#include "../utils/imgui/imgui_impl_dx9.h"
#include "../utils/imgui/imgui_impl_win32.h"

#include "../sdk/ibaseclientdll.h"
#include "../sdk/icliententitylist.h"
#include "../sdk/iclientmodeshared.h"
#include "../sdk/ienginetrace.h"
#include "../sdk/ienginevgui.h"
#include "../sdk/iglobalvars.h"
#include "../sdk/iglowmanager.h"
#include "../sdk/imaterialsystem.h"
#include "../sdk/istudiorender.h"
#include "../sdk/isurface.h"
#include "../sdk/ivdebugoverlay.h"
#include "../sdk/ivengineclient.h"
#include "../sdk/ivmodelinfo.h"
#include "../sdk/ivpanel.h"
#include "../sdk/cclientframestagenotify.h"
#include "../sdk/cviewsetup.h"
#include "../sdk/chud.h"
#include "../sdk/iprediction.h"

namespace interfaces
{
	void SetupInterfaces();

	inline IDirect3DDevice9* device = nullptr;
	inline IBaseClientDLL* client = nullptr;
	inline IClientEntityList* entityList = nullptr;
	inline IClientModeShared* clientMode = nullptr;
	inline IEngineTrace* engineTrace = nullptr;
	inline IEngineVGui* engineVGui = nullptr;
	inline IGlobalVars* globals = nullptr;
	inline IGlowManager* glow = nullptr;
	inline IMaterialSystem* materialSystem = nullptr;
	inline IStudioRender* studioRender = nullptr;
	inline ISurface* surface = nullptr;
	inline IVDebugOverlay* debugOverlay = nullptr;
	inline IVEngineClient* engine = nullptr;
	inline IVModelInfo* modelInfo = nullptr;
	inline IVPanel* panel = nullptr;
	inline void* keyValuesSystem = nullptr;
	inline CHud* hud = nullptr;
	inline CHudChat* hudChat = nullptr;
	inline IPrediction* prediction = nullptr;
}