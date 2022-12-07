#pragma once
#include <d3d9.h>

#include "interfaces.h"

#include "../utils/imgui/imgui.h"
#include "../utils/imgui/imgui_impl_dx9.h"
#include "../utils/imgui/imgui_impl_win32.h"

namespace hooks
{
	void SetupHooks();

	using EndSceneFn = long(__thiscall*)(void*, IDirect3DDevice9*) noexcept;
	inline EndSceneFn EndSceneOriginal = nullptr;
	long __stdcall EndScene(IDirect3DDevice9*) noexcept;

	using ResetFn = HRESULT(__thiscall*)(void*, IDirect3DDevice9*, D3DPRESENT_PARAMETERS*) noexcept;
	inline ResetFn ResetOriginal = nullptr;
	HRESULT __stdcall Reset(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*) noexcept;

	static LRESULT __stdcall WndProcess(HWND, UINT, WPARAM, LPARAM);

	using CreateMoveFn = bool(__thiscall*)(void*, float, CUserCmd*) noexcept;
	inline CreateMoveFn CreateMoveOriginal = nullptr;
	bool __stdcall CreateMove(float, CUserCmd*) noexcept;

	using PaintTraverseFn = void(__thiscall*)(void*, unsigned int, bool, bool);
	inline PaintTraverseFn PaintTraverseOriginal = nullptr;
	void __stdcall PaintTraverse(unsigned int, bool, bool);

	using GetViewModelFOVFn = float(__thiscall*)(void*);
	inline GetViewModelFOVFn GetViewModelFOVOriginal = nullptr;
	float __stdcall GetViewModelFOV();

	using OverrideViewFn = void(__thiscall*)(void*, CViewSetup*);
	inline OverrideViewFn OverrideViewOriginal = nullptr;
	void __stdcall OverrideView(CViewSetup*);

	using DispatchUserMessageFn = int(__thiscall*)(void*, int, uint32_t, int, const void*);
	inline DispatchUserMessageFn DispatchUserMessageOriginal = nullptr;
	bool __stdcall DispatchUserMessage(int, uint32_t, int, const void*);

	using FrameStageNotifyFn = void(__thiscall*)(void*, CClientFrameStage);
	inline FrameStageNotifyFn FrameStageNotifyOriginal = nullptr;
	void __stdcall FrameStageNotify(CClientFrameStage);

	using SettingsChatTextFn = void(__thiscall*)(void*, const char*);
	inline SettingsChatTextFn SettingsChatTextOriginal = nullptr;
	void __fastcall SettingsChatText(void*, void*, const char*);

	using GetPlayerMoneyFn = int(__thiscall*)(void*, int);
	inline GetPlayerMoneyFn GetPlayerMoneyOriginal = nullptr;
	int __fastcall GetPlayerMoney(void*, void*, int);

	using ListLeavesInBoxFn = int(__thiscall*)(void*, const CVector&, const CVector&, unsigned short*, int);
	inline ListLeavesInBoxFn ListLeavesInBoxOriginal = { nullptr };
	int __stdcall ListLeavesInBox(const CVector&, const CVector&, unsigned short*, int);
}