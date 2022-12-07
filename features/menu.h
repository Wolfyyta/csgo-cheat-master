#pragma once
#include <Windows.h>
#include <cstdint>

#include "../utils/imgui/imgui.h"
#include "../utils/imgui/imgui_impl_dx9.h"
#include "../utils/imgui/imgui_impl_win32.h"

/* credits to iWanheda's pull request on cazz/based */
/* also I hate imgui so dont judge me */

inline constexpr std::uint8_t GUI_KEY = VK_INSERT;

namespace menu
{
	void Setup(IDirect3DDevice9*) noexcept;
	void Render() noexcept;
	void Press() noexcept;
	bool IsOpen() noexcept;

	inline bool guiOpen = false;
	inline bool	dxSetup = false;
};