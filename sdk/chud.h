#pragma once
#include "../utils/utils.h"

class CHud
{
public:
	template <typename T>
	T* FindElement(const char* name)
	{
		using FindElementFn = T * (__thiscall*)(void*, const char*);
		static const auto Function = reinterpret_cast<FindElementFn>(utils::PatternScan("client.dll", "55 8B EC 53 8B 5D 08 56 57 8B F9 33 F6 39 77 28 7E 1E"));
		return Function(this, name);
	}
};

class CHudChat
{
public:
	enum ChatFilters : int
	{
		NONE = 0,
		JOINLEAVE = 0x000001,
		NAMECHANGE = 0x000002,
		PUBLICCHAT = 0x000004,
		SERVERMSG = 0x000008,
		TEAMCHANGE = 0x000010,
		ACHIEVEMENT = 0x000020
	};

	void ChatPrintf(int index, int filter, const char* format, ...)
	{
		using Fn = void(__cdecl*)(void*, int, int, const char*, ...);
		return (*(Fn**)this)[27](this, index, filter, format);
	}
};