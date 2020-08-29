#pragma once
#include "..\other\CGlobalVarsBase.h"
#include "..\other\clientclass.h"

enum framestage_t : int
{
	FRAME_UNDEFINED = -1,
	FRAME_START,
	FRAME_NET_UPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	FRAME_NET_UPDATE_END,
	FRAME_RENDER_START,
	FRAME_RENDER_END,
	FRAME_NET_FULL_FRAME_UPDATE_ON_REMOVE
};


class IBaseClientDll
{
public:

	virtual int				Init(create_interface_fn appSystemFactory,create_interface_fn physicsFactory,CGlobalVarsBase* pGlobals) = 0;
	virtual void			Shutdown(void) = 0;
	virtual bool			ReplayInit(create_interface_fn replayFactory) = 0;
	virtual bool			ReplayPostInit() = 0;
	virtual void			LevelInitPreEntity(char const* pMapName) = 0;
	virtual void			LevelInitPostEntity() = 0;
	virtual void			LevelShutdown(void) = 0;
	virtual ClientClass* GetAllClasses(void) = 0;
};