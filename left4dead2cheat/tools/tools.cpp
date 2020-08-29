#include "tools.h"
#include <fstream>
#include <ctime>

#define INRANGE(x,a,b)  (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))

uintptr_t tools::findpattern(const char* szModule, const char* szSignature)
{
	MODULEINFO modInfo;
	GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(szModule), &modInfo, sizeof(MODULEINFO));
	uintptr_t startAddress = reinterpret_cast<uintptr_t>(modInfo.lpBaseOfDll);
	uintptr_t endAddress = startAddress + modInfo.SizeOfImage;
	const char* pat = szSignature;
	uintptr_t firstMatch = 0;
	for (uintptr_t pCur = startAddress; pCur < endAddress; pCur++)
	{
		if (!*pat) return firstMatch;
		if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat))
		{
			if (!firstMatch) firstMatch = pCur;
			if (!pat[2]) return firstMatch;
			if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?') pat += 3;
			else pat += 2;
		}
		else
		{
			pat = szSignature;
			firstMatch = 0;
		}
	}

	return NULL;
}

uintptr_t tools::follow_relative_jump(const uintptr_t address)
{
	return *reinterpret_cast<uintptr_t*>(address + 1) + address + 5;
}

void tools::log(const char* fmt, ...)
{
	if (!fmt) return;
	if (strlen(fmt) < 2) return;

	va_list va_alist;
	char log[256] = { 0 };

	va_start(va_alist, fmt);
	_vsnprintf(log + strlen(log), sizeof(log) - strlen(log), fmt, va_alist);
	va_end(va_alist);

	if (log[0] != '\0')
	{
		SetConsoleColor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
		printf("[%s]", get_time().data());
		SetConsoleColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		printf(": %s", log);
	}
}

std::string_view tools::get_time()
{

	time_t current_time;
	static char timeString[10];


	time(&current_time);

	strftime(timeString, sizeof(timeString), "%H:%M:%S", localtime(&current_time));
	return timeString;
}

