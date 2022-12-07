#pragma once
#include "../utils/utils.h"
#include <cstdint>

class IVPanel
{
public:
	constexpr const char* GetName(std::uint32_t panel) noexcept
	{
		return utils::Call<const char*>(this, 36, panel);
	}

	void SetMouseInputEnable(unsigned int panel, bool state) 
	{
		//using original_fn = void(__thiscall*)(IVPanel*, unsigned int, bool);
		//return (*(original_fn**)this)[32](this, panel, state);
		return utils::Call<void>(this, 32, panel, state);
	}
};
