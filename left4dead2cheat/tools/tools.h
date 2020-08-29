#pragma once
#include <Windows.h>
#include <Psapi.h>
#include <string>

namespace tools 
{
	uintptr_t findpattern(const char* szModule, const char* szSignature);

	uintptr_t follow_relative_jump(const uintptr_t address);

	inline void SetConsoleColor(WORD color)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	}

	void log(const char* fmt, ...);

	std::string_view get_time();
}