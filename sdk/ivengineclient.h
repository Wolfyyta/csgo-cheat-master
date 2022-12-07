#pragma once
#include "../utils/utils.h"

#include "cvector.h"
#include "cmatrix.h"
#include "ispatialquery.h"

class IVEngineClient
{
public:
	constexpr void GetScreenSize(std::int32_t& width, std::int32_t& height) noexcept
	{
		utils::Call<void>(this, 5, std::ref(width), std::ref(height));
	}

	constexpr std::int32_t GetLocalPlayerIndex() noexcept 
	{
		return utils::Call<std::int32_t>(this, 12);
	}

	constexpr void SetViewAngles(const CVector& viewAngles) noexcept 
	{
		utils::Call<void, const CVector&>(this, 19, viewAngles);
	}

	constexpr bool IsInGame() noexcept 
	{
		return utils::Call<bool>(this, 26);
	}

	constexpr const CMatrix4x4& WorldToScreenMatrix() noexcept
	{
		return utils::Call<const CMatrix4x4&>(this, 37);
	}

	constexpr ISpacialQuery* GetBSPTreeQuery() noexcept
	{
		return utils::Call<ISpacialQuery*>(this, 43);
	}
};
