#pragma once


class IPrediction
{
public:
	void SetupMove(IClientEntity* player, cusercmd* cmd, IMoveHelper* pHelper, CMoveData* move)
	{
		callvtable<void(__thiscall*)(IPrediction*, IClientEntity*, cusercmd*, IMoveHelper*, CMoveData*)>(this, 19)(this, player, cmd, pHelper, move);
	}

	void RunCommand(IClientEntity* player, cusercmd* cmd, IMoveHelper* moveHelper)
	{
		callvtable<void(__thiscall*)(IPrediction*, IClientEntity*, cusercmd*, IMoveHelper*)>(this, 18)(this, player, cmd, moveHelper);
	}

	void FinishMove(IClientEntity* player, cusercmd* cmd, CMoveData* move)
	{
		callvtable<void(__thiscall*)(IPrediction*, IClientEntity*, cusercmd*, CMoveData*)>(this, 20)(this, player, cmd, move);
	}

	void set_local_angle(QAngle& angle)
	{
		callvtable<void(__thiscall*)(void*, QAngle&)>(this, 13)(this, angle);
	}

	bool in_prediction(void* _this, int edx)
	{
		return callvtable<bool(__thiscall*)(void*, void*, int)>(this, 14)(this, _this, edx);
	}
};