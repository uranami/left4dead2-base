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

	char pad1[0xB1];
	bool set_camera_to_thirdperson; //0x00B1
	char pad2[0x2];
	Vector thirdperson_camera_angle; //0x00B4
	char pad3[0x2C];
	cusercmd* m_commands; //0x00EC
	cverifiedusercmd* m_verifiedcommands; //0x00F0
};