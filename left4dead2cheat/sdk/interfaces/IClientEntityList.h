#pragma once
#include "..\other\Misc.h"
#include "CHandleBase.h"
#include "IClientNetworkable.h"
#include "IClientUnknown.h"
#include "IClientEntity.h"

class IClientEntityList
{
public:
	virtual IClientNetworkable* GetClientNetworkable(int entindex) = 0;
	virtual IClientNetworkable* GetClientNetworkableFromHandle(HANDLE hEntity) = 0;
	virtual IClientUnknown* getclientinknownfromhandle(CBaseHandle hEnt) = 0;
	virtual IClientEntity* getcliententity(int entindex) = 0;
	virtual IClientEntity* getcliententityfromhandle(CBaseHandle hEnt) = 0;
	virtual int NumberOfEntities(bool include_non_networkable) = 0;
	virtual int maximum_entity_index(void) = 0;
	virtual void SetMaxEntities(int maxents) = 0;
	virtual int GetMaxEntities() = 0;
};

