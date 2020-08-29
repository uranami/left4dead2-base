#pragma once
#include <map>

class i_netchannel;

class clientstate
{
public:
	char pad_0x0000[0x4A00]; //0x0000
	i_netchannel* netchannel; //0x4A00 
	__int32 oldtickcount; //0x4A04
	char pad_0x4A08[0xC]; //0x4A08
	__int32 N00001286; //0x4A14 
	char pad_0x4A18[0x34]; //0x4A18
	__int32 lastoutgoincommand; //0x4A4C
	__int32 chockcommand; //0x4A50
	__int32 command_ack; //0x4A54
	__int32 m_nsoundsquence; //0x4A58 
	bool ishltv; //0x4A5C
	char pad_0x4A60[0x4C]; //0x4A60
	QAngle viewangle; //0x4AAC
	char pad_0x4AB8[0x588]; //0x4AB8
};