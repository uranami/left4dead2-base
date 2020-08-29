#include "..\hooks.h"


void __fastcall hook::createmove(IBaseClientDll* _ecx, void* _edx, int sequence_number, float input_sample_frametime, bool active)
{

	static auto originalcreatemove = chlclienthook->getoriginal< fncreatemove >(index::createmove);
	originalcreatemove(_ecx, sequence_number, input_sample_frametime, active);
	
	DWORD pebp;
	__asm mov pebp, ebp;
	bool* send_packet = reinterpret_cast<bool*>(*reinterpret_cast<byte**>(pebp) - 0x21);
	auto verifiedcmd = *(cverifiedusercmd**)((uintptr_t)g_input + 0xE0);
	if (!verifiedcmd)
		return;
	auto verified_cmd = &verifiedcmd[sequence_number % 150];

	auto cmd = g_input->usercmd(0, sequence_number);
	if (!cmd || !verified_cmd)
		return;

	c_baseplayer* me = reinterpret_cast<c_baseplayer*>(g_entitylist->getcliententity(g_engine->GetLocalPlayer()));
	if (!me)
		return;

	if (cmd->buttons & IN_JUMP && !(me->m_fFlags() & FL_ONGROUND))
		cmd->buttons &= ~IN_JUMP;

	verified_cmd->m_cmd = *cmd;
	verified_cmd->m_crc = cmd->getchecksum();
}