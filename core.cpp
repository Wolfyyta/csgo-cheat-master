#include <Windows.h>
#include <thread>

#include "core/interfaces.h"
#include "core/hooks.h"
#include "utils/netvars/netvars.h"

DWORD WINAPI MainThread(LPVOID lpParameter)
{
	while (!GetModuleHandle("serverbrowser.dll"))
		std::this_thread::sleep_for(std::chrono::milliseconds(200));

	try
	{
		interfaces::SetupInterfaces();
		netvars::SetupNetvars();
		hooks::SetupHooks();
	}
	catch (std::exception& ex)
	{
		_RPT0(_CRT_ERROR, ex.what());
		FreeLibraryAndExitThread(static_cast<HMODULE>(lpParameter), EXIT_FAILURE);
	}

	return 1UL;
}

BOOL WINAPI DllMain(HMODULE dllModule, DWORD callingReason, LPVOID lpParameter)
{
	if (dllModule)
		DisableThreadLibraryCalls(dllModule);

	if (callingReason == DLL_PROCESS_ATTACH)
	{
		const HANDLE threadHandle = CreateThread(NULL, NULL, MainThread, dllModule, NULL, NULL);

		if (threadHandle)
			CloseHandle(threadHandle);
	}

	return TRUE;
}