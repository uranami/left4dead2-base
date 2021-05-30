#pragma once
#include <map>

class i_netchannel;

class clientstate
{
public:
	char pad1[0x70]; //0x0000
	int32_t m_signonstate; //0x0070
	char pad2[0x8]; //0x0074
	float m_nextcmdtime; //0x007C
	int32_t m_servercount; //0x0080
	char pad3[0x44]; //0x0084
	int32_t m_curseq; //0x00C8
	int32_t N00000082; //0x00CC
	int32_t m_servertick; //0x00D0
	int32_t m_delta_tick; //0x00D4
	char pad4[0x4968]; //0x00D8
	int32_t m_oldtickcount; //0x4A40
	float m_tickremainder; //0x4A44
	float m_frametime; //0x4A48
	int32_t m_lastougoingcommand; //0x4A4C
	int32_t m_chokecommand; //0x4A50
	int32_t last_command_ack; //0x4A54
	int32_t command_ack; //0x4A58
	char pad5[0x50];  //0x4A5C
	QAngle viewangle; //0x4AAC
};