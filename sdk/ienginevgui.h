#pragma once
#include "../utils/utils.h"

enum EVGuiPanel
{
	PANEL_ROOT = 0,
	PANEL_GAMEUIDLL,
	PANEL_CLIENTDLL,
	PANEL_TOOLS,
	PANEL_INGAMESCREENS,
	PANEL_GAMEDLL,
	PANEL_CLIENTDLL_TOOLS
};

class IEngineVGui
{
public:
	constexpr std::uintptr_t GetPanel(std::int32_t type) noexcept
	{
		return utils::Call<std::uintptr_t>(this, 1, type);
	}
};
