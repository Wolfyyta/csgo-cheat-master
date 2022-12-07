#pragma once
#include <string>

#include "../utils/imgui/imgui.h"
#include "../utils/imgui/imgui_impl_dx9.h"
#include "../utils/imgui/imgui_impl_win32.h"

namespace screen
{
	void DrawOnScreen(ImDrawList* drawList);
}