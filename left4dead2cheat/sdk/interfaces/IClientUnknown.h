#pragma once
#include "CHandleBase.h"
#include "ICollideable.h"
class ICollideable;
class IClientNetworkable;
class IClientRenderable;
class IClientEntity;
class c_baseplayer;
class IClientThinkable;

class IClientUnknown : public IHandleEntity
{
public:
	virtual ICollideable* GetCollideable() = 0;
	virtual IClientNetworkable* GetClientNetworkable() = 0;
	virtual IClientRenderable* GetClientRenderable() = 0;
	virtual IClientEntity* GetIClientEntity() = 0;
	virtual c_baseplayer* GetBaseEntity() = 0;
	virtual IClientThinkable* GetClientThinkable() = 0;
};
