#pragma once
#include <exception>
#include <memory>
#include <string>
#include <sstream>
#include <map>
#include <d3d9.h>
#include <d3dx9.h>

#include "..\tools\tools.h"
#include "math\matrix.h"
#include "math\vector.h"
#include "other\Misc.h"
#include "interfaces\IEngineClient.h"
#include "interfaces\IClientEntityList.h"
#include "interfaces\IBaseClientDll.h"
#include "interfaces\IClientMode.h"
#include "interfaces\CInput.h"
#include "interfaces\ISurface.h"
#include "interfaces\IEngineVGui.h"
#include "interfaces\IMoveHelper.h"
#include "interfaces\IGameMovement.h"
#include "interfaces\IPrediction.h"
#include "interfaces\IVModelRender.h"
#include "interfaces\IMaterialSystem.h"
#include "interfaces\IVRenderView.h"
#include "interfaces\ICvar.h"
#include "interfaces\IPanel.h"
#include "interfaces\CModelInfo.h"
#include "interfaces\EngineTrace.h"
#include "interfaces\IRenderView.h"
#include "other\CGlobalVarsBase.h"
#include "client\cbaseplayer.h"
#include "client\clientstate.h"

/*interfaces here*/
extern IEngineClient* g_engine;
extern IClientEntityList* g_entitylist;
extern CGlobalVarsBase* g_globalvars;
extern IBaseClientDll* g_baseclientdll;
extern CInput* g_input;
extern IClientMode* g_clientmode;
extern clientstate* g_clientstate;
extern ISurface* g_surfaces;
extern IEngineVGui* g_enginevgui;
extern CModelInfo* g_modelinfo;
extern IEngineTrace* g_trace;
extern IGameMovement* g_gamemovement;
extern IPrediction* g_prediction;
extern IMoveHelper* g_movehelper;
extern ICvar* g_cvar;
extern IMaterialSystem* g_matsys;
extern IVRenderView* g_renderview;
extern IVModelRender* g_modelrender;
extern IPanel* g_panel;
extern IViewRender* g_viewrender;
extern IDirect3DDevice9* g_directdevice;


extern void setup_interfaces();