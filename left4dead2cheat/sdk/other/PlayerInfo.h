#pragma once
#include <cstdint>
#include <Windows.h>

class player_info_t
{
public:
	BYTE __pad00[0x08];		// 0x00
	char name[32];			// 0x08
	int32_t userId;			// 0x28
	char steamId[33];		// 0x2C
	BYTE __pad01[0x27];		// 0x4D
	bool isBot;				// 0x74
	BYTE __pad02[0x1B];		// 0x75
};	// sizeof 0x90
