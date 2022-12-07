#pragma once

struct ImVec4;
namespace variables
{
	namespace misc
	{
		inline bool bunnyHop = false;
	}

	namespace players
	{
		inline bool boxEsp = false;
	}

	namespace world
	{
		inline float viewmodelFov = 0.f;
		inline float worldFov = 0.f;
		inline bool keepFovInScope = false;
		inline bool modulateMolotovColor = false;
		
		inline float molotovColor[3];
	}

	namespace screen
	{
		inline bool debugInfo = false;
		inline bool removeScope = false;
	}
}