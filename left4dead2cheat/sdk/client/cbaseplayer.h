#pragma once
#include "..\..\tools\netvar_tree.h"
#include "..\interfaces\CHandleBase.h"

class c_baseplayer : public IClientEntity
{
public:
	NETVAR(m_fFlags, "CBasePlayer", "m_fFlags", std::int32_t );
	NETVAR(m_Collision, "CBaseEntity", "m_Collision", Vector);
	NETVAR(collideable_mins, "CBaseEntity", "m_vecMins", Vector);
	NETVAR(collideable_maxs, "CBaseEntity", "m_vecMaxs", Vector);
	NETVAR(m_mobrush, "Infected", "m_mobRush", bool );
	NETVAR(m_hactiveweapon, "CBaseCombatCharacter", "m_hActiveWeapon", CBaseHandle);
	NETVAR(m_hObserverTarget, "CBasePlayer", "m_hObserverTarget", unsigned long );
	NETVAR(get_tick_base, "CBasePlayer", "m_nTickBase", std::uint32_t );
	NETVAR(team_num, "CBaseEntity", "m_iTeamNum", std::int32_t );
	NETVAR(m_ihealth, "CBasePlayer", "m_iHealth", std::int32_t );
	NETVAR(m_angrotation, "CBaseEntity", "m_angRotation", Vector );
	NETVAR(m_punchangle, "CBasePlayer", "m_vecPunchAngle", QAngle);
	NETVAR(m_lifestate, "CBasePlayer", "m_lifeState", std::int32_t);
	NETVAR(m_vecorigin, "CBaseEntity", "m_vecOrigin", Vector);
	NETVAR(m_vecview_offset, "CBasePlayer", "m_vecViewOffset[0]", Vector);
	NETVAR(m_nsequence, "CBaseViewModel", "m_nSequence", std::uint32_t);
	NETVAR(m_vecvelocity, "CBasePlayer", "m_vecVelocity[0]", Vector);
	NETVAR(m_eyeangle, "CCSPlayer", "m_angEyeAngles[0]", QAngle);
	NETVAR(get_next_attack, "CBaseCombatCharacter", "m_flNextAttack", float_t);
	NETVAR(m_groundentity, "CBasePlayer", "m_hGroundEntity", std::int32_t);
	NETVAR(m_waterlevel, "CBasePlayer", "m_nWaterLevel", std::int32_t);
	NETVAR(get_max_speed, "CBasePlayer", "m_flMaxspeed", std::float_t);
	NETVAR(get_max_health, "CTerrorPlayer", "m_iMaxHealth", std::int32_t);
	NETVAR(m_usSolidFlags, "CBaseEntity", "m_usSolidFlags", std::int32_t);
	NETVAR(m_rage, "Witch", "m_rage", std::float_t);
	NETVAR(m_simtime, "CBaseEntity", "m_flSimulationTime", std::float_t);

	Vector get_eye_pos()
	{
		return m_vecorigin() + m_vecview_offset();
	}

	bool is_alive()
	{
		return (m_lifestate() == 0 && m_ihealth() > 0);
	}

	inline cusercmd*& current_command()
	{
		return *reinterpret_cast<cusercmd**>(reinterpret_cast<DWORD>(this) + (tools::findpattern("client.dll", "89 BE ? ? ? ? E8 ? ? ? ? 8B 0D ? ? ? ? 89 35") + 2));
	}
};

class c_baseweapon : public c_baseplayer
{
public:

	NETVAR(get_next_primary_attack, "CBaseCombatWeapon", "m_flNextPrimaryAttack", std::float_t);
	NETVAR(get_clip, "CBaseCombatWeapon", "m_iClip1", std::int32_t);
	NETVAR(is_reload, "CBaseCombatWeapon", "m_bInReload", bool);
	NETVAR(get_swpan_weapon_id, "CWeaponSpawn", "m_weaponID", std::int32_t);
	NETVAR(m_throwtime, "CBaseCSGrenade", "m_fThrowTime", std::float_t);

	float& get_spread()
	{
		return *reinterpret_cast<float*>(reinterpret_cast<DWORD>(this) + 0xD0C);
	}

	weaponinfo_t* get_weapon_data()
	{
		using original = weaponinfo_t * (__thiscall*)(LPVOID);
		static original get_weapon_data = reinterpret_cast<original>(tools::follow_relative_jump(tools::findpattern("client.dll", "E8 ? ? ? ? 8B 10 8B C8 8B 42 04 FF D0 68")));
		return get_weapon_data(this);
	}

	void update_spread()
	{
		using original = void(__thiscall*)(c_baseweapon*);
		static original max_spread = reinterpret_cast<original>(tools::findpattern("client.dll", "53 8B DC 83 EC ? 83 E4 ? 83 C4 ? 55 8B 6B ? 89 6C ? ? 8B EC 83 EC ? 56 57 8B F9 E8"));
		return max_spread(this);
	}
};

