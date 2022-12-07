#pragma once
#include "../utils/utils.h"
#include "cvector.h"

// todo: get the full class
class IPrediction
{
public:
	constexpr void GetLocalViewAngles(CVector& viewAngles) noexcept
	{
		utils::Call<void>(this, 12, std::ref(viewAngles));
	}

	constexpr void SetLocalViewAngles(CVector& viewAngles) noexcept
	{
		utils::Call<void>(this, 13, std::ref(viewAngles));
	}
};