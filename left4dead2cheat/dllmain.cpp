// dllmain.cpp : 定义 DLL 应用程序的入口点。
#pragma warning(disable:4996)

#include <windows.h>
#include <cassert>
#include "hook\hooks.h"


DWORD WINAPI setupcheat(LPVOID module)
{

	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
	SetConsoleTitleA("left4dead2 internal debug console");

	setup_interfaces();
	g_draw::setup_font();
	hook::setup_hook();

	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,DWORD ul_reason_for_call,LPVOID lpReserved)
{

	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{

		if (hModule)
	    DisableThreadLibraryCalls(hModule);
		CreateThread(nullptr, 0, setupcheat, hModule, 0, nullptr);
		
	}

	return TRUE;
}
