#pragma once
#include "checksum_crc.h"
#include "../math/vector.h"
#include <Windows.h>
#include <cstdint>

class cusercmd
{
public:
	CRC32_t getchecksum() const;

	LPVOID __vtable;
	int command_number;
	int tick_count;
	QAngle viewangles;
	float forwardmove;
	float sidemove;
	float upmove;
	int buttons;
	uint8_t impulse;
	int weaponselect;
	int weaponsubtype;
	int random_seed;
	int mousedx;
	short mousedy;
	bool hasbeenpredicted;
	Vector headangles;
	Vector headoffset;
};

class cverifiedusercmd
{
public:
	cusercmd	m_cmd;
	CRC32_t		m_crc;
};
