#include <Windows.h>

#include "interfaces.h"

/* capture an interface by name and module */
/* credits: cazz/based */
template <typename Interface>
Interface* Get(const char* moduleName, const char* interfaceName) noexcept
{
	const HINSTANCE handle = GetModuleHandle(moduleName);

	if (!handle)
		return nullptr;

	using Fn = Interface * (__cdecl*)(const char*, int*);
	const Fn createInterface = reinterpret_cast<Fn>(GetProcAddress(handle, "CreateInterface"));

	return createInterface(interfaceName, nullptr);
}

void interfaces::SetupInterfaces()
{
	client = Get<IBaseClientDLL>("client.dll", "VClient018");
	entityList = Get<IClientEntityList>("client.dll", "VClientEntityList003");
	clientMode = **reinterpret_cast<IClientModeShared***>((*reinterpret_cast<unsigned int**>(client))[10] + 5);
	engineTrace = Get<IEngineTrace>("engine.dll", "EngineTraceClient004");
	engineVGui = Get<IEngineVGui>("engine.dll", "VEngineVGui001");
	globals = **reinterpret_cast<IGlobalVars***>((*reinterpret_cast<uintptr_t**>(client))[11] + 10);
	glow = *reinterpret_cast<IGlowManager**>(utils::PatternScan("client.dll", "0F 11 05 ? ? ? ? 83 C8 01") + 3);
	materialSystem = Get<IMaterialSystem>("materialsystem.dll", "VMaterialSystem080");
	studioRender = Get<IStudioRender>("studiorender.dll", "VStudioRender026");
	surface = Get<ISurface>("vguimatsurface.dll", "VGUI_Surface031");
	debugOverlay = Get<IVDebugOverlay>("engine.dll", "VDebugOverlay004");
	engine = Get<IVEngineClient>("engine.dll", "VEngineClient014");
	modelInfo = Get<IVModelInfo>("engine.dll", "VModelInfoClient004");
	panel = Get<IVPanel>("vgui2.dll", "VGUI_Panel009");
	device = **reinterpret_cast<IDirect3DDevice9***>(utils::PatternScan("shaderapidx9.dll", "A1 ? ? ? ? 50 8B 08 FF 51 0C") + 0x1);
	hud = *reinterpret_cast<CHud**>(utils::PatternScan("client.dll", "B9 ? ? ? ? E8 ? ? ? ? 85 C0 0F 84 ? ? ? ? 83 C0 EC 0F 84 ? ? ? ?") + 1);
	hudChat = hud->FindElement<CHudChat>("CHudChat");
	prediction = Get<IPrediction>("client.dll", "VClientPrediction001");

	if (const HINSTANCE handle = GetModuleHandle("vstdlib.dll"); handle)
		keyValuesSystem = reinterpret_cast<void* (__cdecl*)()>(GetProcAddress(handle, "KeyValuesSystem"))();
}
