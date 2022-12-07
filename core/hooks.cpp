#include <intrin.h>

#include "hooks.h"
#include "../utils/minhook/minhook.h"

#include "../features/menu.h"
#include "../features/misc.h"
#include "../features/screen.h"

#include "../globals.h"
#include "../features/variables.h"

LONG  __stdcall hooks::EndScene(IDirect3DDevice9* device) noexcept
{
	static const auto retAddr = _ReturnAddress();
	const auto result = EndSceneOriginal(device, device);

	if (_ReturnAddress() == retAddr)
		return result;

	menu::Setup(device);

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();

	screen::DrawOnScreen(ImGui::GetBackgroundDrawList());
	menu::Render();

	ImGui::EndFrame();

	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	return result;
}

HRESULT __stdcall hooks::Reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params) noexcept
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	const auto result = ResetOriginal(device, device, params);
	ImGui_ImplDX9_CreateDeviceObjects();

	return result;
}

WNDPROC oldWindow = reinterpret_cast<WNDPROC>(SetWindowLongPtr(FindWindowA("Valve001", nullptr), GWL_WNDPROC, reinterpret_cast<LONG_PTR>(hooks::WndProcess)));
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall hooks::WndProcess(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (GetAsyncKeyState(GUI_KEY) & 1)
		menu::Press();

	if (menu::IsOpen() && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return 1L;

	return CallWindowProc(oldWindow, hWnd, uMsg, wParam, lParam);
}

bool __stdcall hooks::CreateMove(float frameTime, CUserCmd* cmd) noexcept
{
	const auto result = CreateMoveOriginal(interfaces::clientMode, frameTime, cmd);
	if (!cmd || !cmd->commandNumber)
		return result;

	globals::cmd = cmd;

	if (globals::local && globals::local->IsAlive())
	{
		misc::BunnyHop(cmd);
	}

	return false;
}

void __stdcall hooks::PaintTraverse(unsigned int panel, bool forceRepaint, bool allowForce)
{
	if (strstr("HudZoom", interfaces::panel->GetName(panel)) && variables::screen::removeScope)
		return;

	PaintTraverseOriginal(interfaces::panel, panel, forceRepaint, allowForce);

	if (strstr("FocusOverlayPanel", interfaces::panel->GetName(panel)))
	{
		interfaces::panel->SetMouseInputEnable(panel, menu::IsOpen());
	}
}

float __stdcall hooks::GetViewModelFOV()
{
	if (!globals::local)
		return GetViewModelFOVOriginal(interfaces::clientMode);

	if (globals::local->IsScoped())
		return GetViewModelFOVOriginal(interfaces::clientMode);

	return GetViewModelFOVOriginal(interfaces::clientMode) + variables::world::viewmodelFov;
}

void __stdcall hooks::OverrideView(CViewSetup* setup)
{
	if (!globals::local)
		return OverrideViewOriginal(interfaces::clientMode, setup);

	if (globals::local->IsScoped() && !variables::world::keepFovInScope)
		return OverrideViewOriginal(interfaces::clientMode, setup);

	if (variables::world::keepFovInScope && globals::local->IsScoped())
	{
		setup->fov = setup->fov + variables::world::worldFov + 10.f; // todo: find proper and working method xd
	}
	else
	{
		setup->fov = setup->fov + variables::world::worldFov;
	}

	static bool thirdperson = false;
	if (GetAsyncKeyState(VK_ADD) & 1)
		thirdperson = !thirdperson;

	if (thirdperson)
	{
		
	}

	OverrideViewOriginal(interfaces::clientMode, setup);
}

/* credits: cazz/kakhack */
bool __stdcall hooks::DispatchUserMessage(int type, uint32_t flags, int size, const void* message)
{
	switch (type)
	{
	case CS_UM_VoteStart:
	{
		interfaces::hudChat->ChatPrintf(0, 0, " \x03[csgo]\x01 Vote started\n");
		break;
	}
	case CS_UM_VotePass:
		interfaces::hudChat->ChatPrintf(0, 0, " \x03[csgo]\x01 Vote \x04Passed\x01\n");
		break;

	case CS_UM_VoteFailed:
		interfaces::hudChat->ChatPrintf(0, 0, " \x03[csgo]\x01 \x02Vote\x02 Failed\x01\n");
		break;
	}

	return DispatchUserMessageOriginal(interfaces::client, type, flags, size, message);
}

void __stdcall hooks::FrameStageNotify(CClientFrameStage stage)
{
	globals::local = interfaces::entityList->GetEntityFromIndex(interfaces::engine->GetLocalPlayerIndex());

	switch (stage)
	{
	case FRAME_RENDER_START:
		// todo: remove post processing (avoid convar manipulation)
		// todo: animation fix
		// todo: skin changer
		// todo: remove flash (maybe find a way to avoid netvar manipulation)
		break;
	}

	FrameStageNotifyOriginal(interfaces::client, stage);
}

void __fastcall hooks::SettingsChatText(void* thisptr, void* edx, const char* text)
{
	if (strstr("#SFUI_Settings_Chat_Say", text))
	{
		return SettingsChatTextOriginal(thisptr, "[csgo] Global chat.");
	}

	if (strstr("#SFUI_Settings_Chat_SayTeam", text))
	{
		return SettingsChatTextOriginal(thisptr, "[csgo] Team chat.");
	}

	SettingsChatTextOriginal(thisptr, text);
}

int __fastcall hooks::GetPlayerMoney(void* thisptr, void* edx, int entityIndex)
{
	const auto player = interfaces::entityList->GetEntityFromIndex(entityIndex);

	if (!player || !player->IsPlayer())
		return GetPlayerMoneyOriginal(thisptr, entityIndex);

	if (player->GetTeam() == globals::local->GetTeam())
		return GetPlayerMoneyOriginal(thisptr, entityIndex);

	return player->Account();
}

int __stdcall hooks::ListLeavesInBox(const CVector& mins, const CVector& maxs, unsigned short* list, int listMax)
{
	static const auto insertIntoTree = reinterpret_cast<std::uintptr_t>(utils::PatternScan("client.dll", "56 52 FF 50 18") + 5);

	if (reinterpret_cast<std::uintptr_t>(_ReturnAddress()) != insertIntoTree)
		return ListLeavesInBoxOriginal(interfaces::engine->GetBSPTreeQuery(), mins, maxs, list, listMax);

	const auto info = *reinterpret_cast<CRenderableInfo**>(reinterpret_cast<std::uintptr_t>(_AddressOfReturnAddress()) + 0x14);

	if (!info || !info->renderable)
		return ListLeavesInBoxOriginal(interfaces::engine->GetBSPTreeQuery(), mins, maxs, list, listMax);

	const auto entity = info->renderable->GetIClientUnknown()->GetBaseEntity();

	if (!entity || !entity->IsPlayer())
		return ListLeavesInBoxOriginal(interfaces::engine->GetBSPTreeQuery(), mins, maxs, list, listMax);

	if (entity->GetTeam() == globals::local->GetTeam())
		return ListLeavesInBoxOriginal(interfaces::engine->GetBSPTreeQuery(), mins, maxs, list, listMax);

	info->flags &= ~RENDER_FLAGS_FORCE_OPAQUE_PASS;
	info->flags2 |= RENDER_FLAGS_BOUNDS_ALWAYS_RECOMPUTE;

	constexpr float maxCoord = 16384.0f;
	constexpr float minCoord = -maxCoord;

	constexpr CVector min{ minCoord, minCoord, minCoord };
	constexpr CVector max{ maxCoord, maxCoord, maxCoord };

	return ListLeavesInBoxOriginal(interfaces::engine->GetBSPTreeQuery(), min, max, list, listMax);
}

void hooks::SetupHooks()
{
	MH_Initialize();
	{
		static auto settingsChatTextSig = utils::PatternScan("client.dll", "55 8B EC 56 8B F1 83 BE ? ? ? ? ? 75 4B");
		static auto getPlayerMoneySig = utils::PatternScan("client.dll", "55 8B EC 56 8B 75 08 83 FE 3F 0F 87 ? ? ? ?");

		MH_CreateHook(utils::Get(interfaces::device, 42), &EndScene, reinterpret_cast<void**>(&EndSceneOriginal));
		MH_CreateHook(utils::Get(interfaces::device, 16), &Reset, reinterpret_cast<void**>(&ResetOriginal));
		MH_CreateHook(utils::Get(interfaces::clientMode, 24), &CreateMove, reinterpret_cast<void**>(&CreateMoveOriginal));
		MH_CreateHook(utils::Get(interfaces::panel, 41), &PaintTraverse, reinterpret_cast<void**>(&PaintTraverseOriginal));
		MH_CreateHook(utils::Get(interfaces::clientMode, 35), &GetViewModelFOV, reinterpret_cast<void**>(&GetViewModelFOVOriginal));
		MH_CreateHook(utils::Get(interfaces::clientMode, 18), &OverrideView, reinterpret_cast<void**>(&OverrideViewOriginal));
		MH_CreateHook(utils::Get(interfaces::client, 38), &DispatchUserMessage, reinterpret_cast<void**>(&DispatchUserMessageOriginal));
		MH_CreateHook(utils::Get(interfaces::client, 37), &FrameStageNotify, reinterpret_cast<void**>(&FrameStageNotifyOriginal));

		MH_CreateHook(utils::Get(interfaces::engine->GetBSPTreeQuery(), 6), &ListLeavesInBox, reinterpret_cast<void**>(&ListLeavesInBoxOriginal));

		MH_CreateHook(reinterpret_cast<void*>(settingsChatTextSig), &SettingsChatText, reinterpret_cast<void**>(&SettingsChatTextOriginal));
		MH_CreateHook(reinterpret_cast<void*>(getPlayerMoneySig), &GetPlayerMoney, reinterpret_cast<void**>(&GetPlayerMoneyOriginal));
	}
	MH_EnableHook(MH_ALL_HOOKS);
}