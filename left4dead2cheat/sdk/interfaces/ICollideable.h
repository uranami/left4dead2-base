#pragma once
#include "Trace.h"

enum SolidType_t
{
	SOLID_NONE = 0,				// no solid model
	SOLID_BSP,					// a BSP tree
	SOLID_BBOX,					// an AABB
	SOLID_OBB,					// an OBB (not implemented yet)
	SOLID_OBB_YAW,				// an OBB, constrained so that it can only yaw
	SOLID_CUSTOM,				// Always call into the entity for tests
	SOLID_VPHYSICS				// solid vphysics object, get vcollide from the model and collide with that
};
class IClientUnknown;
struct model_t;
class ICollideable
{
public:
	virtual ~ICollideable() {};

	SolidType_t GetSolid()
	{
		return callvtable<SolidType_t(__thiscall*)(ICollideable*)>(this, 11)(this);
	}

	unsigned short GetSolidFlags()
	{
		return callvtable<unsigned short(__thiscall*)(ICollideable*)>(this, 12)(this);
	}
};