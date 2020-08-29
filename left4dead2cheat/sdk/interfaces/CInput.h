#pragma once
#include "..\other\CUserCmd.h"

class CInput
{
public:
	cusercmd* usercmd(int slot, int sequence_number)
	{
		return callvtable<cusercmd*(__thiscall*)(void*, int , int)>(this, 8)(this, slot, sequence_number);
	}

	int in_thirdperson(int slot = -1)
	{
		return callvtable<int(__thiscall*)(void*, int)>(this, 29)(this, slot);
	}
public:
	char pad_0x0000[0x3C]; //0x0000
	float m_mousey; //0x003C 
	float m_mousex; //0x0040 
	char pad_0x0044[0x5C]; //0x0044
	DWORD m_camintp; //0x00A0 
	float m_campitch; //0x00A4 
	float m_camyaw; //0x00A8 
	float m_camdist; //0x00AC 
	char pad_0x00B0[0x18]; //0x00B0
	float m_anglex; //0x00C8 
	float m_angley; //0x00CC 
	float m_anglez; //0x00D0 
	char pad_0x00D4[0x76C]; //0x00D4
};