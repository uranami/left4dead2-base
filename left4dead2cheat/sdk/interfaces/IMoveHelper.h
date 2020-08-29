#pragma once

class IMoveHelper
{
public:

	void set_host(IClientEntity* player)
	{
		callvtable<void(__thiscall*)(IMoveHelper*, IClientEntity*)>(this, 1)(this, player);
	}

};