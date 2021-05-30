#include "interfaces.h"

IEngineClient* g_engine = nullptr;
IClientEntityList* g_entitylist = nullptr;
CGlobalVarsBase* g_globalvars = nullptr;
IBaseClientDll* g_baseclientdll = nullptr;
CInput* g_input = nullptr;
IClientMode* g_clientmode = nullptr;
clientstate* g_clientstate = nullptr;
ISurface* g_surfaces = nullptr;
IEngineVGui* g_enginevgui = nullptr;
CModelInfo* g_modelinfo = nullptr;
IEngineTrace* g_trace = nullptr;
IGameMovement* g_gamemovement = nullptr;
IPrediction* g_prediction = nullptr;
IMoveHelper* g_movehelper = nullptr;
ICvar* g_cvar = nullptr;
IMaterialSystem* g_matsys = nullptr;
IVRenderView* g_renderview = nullptr;
IVModelRender* g_modelrender = nullptr;
IPanel* g_panel = nullptr;
IViewRender* g_viewrender = nullptr;
IDirect3DDevice9* g_directdevice = nullptr; 


create_interface_fn get_module_factory(HMODULE module)
{
	return reinterpret_cast<create_interface_fn>(GetProcAddress(module, "CreateInterface"));
}

template<typename T>
T* get_interface(create_interface_fn f, const char* ver)
{
	auto result = reinterpret_cast<T*>(f(ver, nullptr));

	if (!result) 
	{
		throw std::runtime_error(std::string("[interfaces] Failed to interfaces: ") + ver);
	}

	return result;
}

void setup_interfaces()
{
	auto enginedll  =    get_module_factory(GetModuleHandleW(L"engine.dll"));
	auto clientdll  =    get_module_factory(GetModuleHandleW(L"client.dll"));
	auto vstdlibdll =    get_module_factory(GetModuleHandleW(L"vstdlib.dll"));
	auto vguidll    =    get_module_factory(GetModuleHandleW(L"vguimatsurface.dll"));
	auto vgui2dll   =    get_module_factory(GetModuleHandleW(L"vgui2.dll"));
	auto matsysdll  =    get_module_factory(GetModuleHandleW(L"materialsystem.dll"));

	g_engine        =    get_interface<IEngineClient>      (enginedll,  "VEngineClient013");
	g_entitylist    =    get_interface<IClientEntityList>  (clientdll,  "VClientEntityList003");
	g_baseclientdll =    get_interface<IBaseClientDll>     (clientdll,  "VClient016");
	g_surfaces      =    get_interface<ISurface>           (vguidll,    "VGUI_Surface031");
	g_enginevgui    =    get_interface<IEngineVGui>        (enginedll,  "VEngineVGui001");
	g_modelinfo     =    get_interface<CModelInfo>         (enginedll,  "VModelInfoClient004");
	g_trace         =    get_interface<IEngineTrace>       (enginedll,  "EngineTraceClient003");
	g_gamemovement  =    get_interface<IGameMovement>      (clientdll,  "GameMovement001");
	g_prediction    =    get_interface<IPrediction>        (clientdll,  "VClientPrediction001");
	g_cvar          =    get_interface<ICvar>              (vstdlibdll, "VEngineCvar007");
	g_matsys        =    get_interface<IMaterialSystem>    (matsysdll,  "VMaterialSystem080");
	g_renderview    =    get_interface<IVRenderView>       (enginedll,  "VEngineRenderView013");
	g_modelrender   =    get_interface<IVModelRender>      (enginedll,  "VEngineModel016");
	g_panel         =    get_interface<IPanel>             (vgui2dll,   "VGUI_Panel009");


	//offset getinterfaces
	g_movehelper    =    **reinterpret_cast<IMoveHelper***>(tools::findpattern("client.dll", "A1 ? ? ? ? 8B 10 8B 52 ? 81 C1") + 1);
	g_input         =    **reinterpret_cast<CInput***>(tools::findpattern("client.dll", "8B 55 10 8B 0D ? ? ? ? 8B 01 8B 40 0C") + 0x5);
	g_directdevice  =    **reinterpret_cast<IDirect3DDevice9***> (tools::findpattern("shaderapidx9.dll", "A1 ? ? ? ? 8B 08 6A 00 57 52") + 1);
	g_globalvars    =    **(CGlobalVarsBase***)((*(std::uintptr_t**)g_baseclientdll)[10] + 0x11);
	g_clientmode    =    (((IClientMode*(*)())(tools::follow_relative_jump(tools::findpattern("client.dll", "E8 ? ? ? ? 8B 10 8B C8 8B 52 34"))))());
	g_clientstate   =    **reinterpret_cast<clientstate***>(tools::findpattern("engine.dll", "A1 ? ? ? ? 83 C0 08") + 1);


	tools::log("find g_engine at : 0x%p\n", g_engine);
	tools::log("find g_entitylist at : 0x%p\n", g_entitylist);
	tools::log("find g_baseclientdll at : 0x%p\n", g_baseclientdll);
	tools::log("find g_surfaces at : 0x%p\n", g_surfaces);
	tools::log("find g_enginevgui at : 0x%p\n", g_enginevgui);
	tools::log("find g_modelinfo at : 0x%p\n", g_modelinfo);
	tools::log("find g_trace at : 0x%p\n", g_trace);
	tools::log("find g_gamemovement at : 0x%p\n", g_gamemovement);
	tools::log("find g_prediction at : 0x%p\n", g_prediction);
	tools::log("find g_cvar at : 0x%p\n", g_cvar);
	tools::log("find g_matsys at : 0x%p\n", g_matsys);
	tools::log("find g_renderview at : 0x%p\n", g_renderview);
	tools::log("find g_modelrender at : 0x%p\n", g_modelrender);
	tools::log("find g_panel at : 0x%p\n", g_panel);
	tools::log("find g_movehelper at : 0x%p\n", g_movehelper);
	tools::log("find g_input at : 0x%p\n", g_input);
	tools::log("find g_directdevice at : 0x%p\n", g_directdevice);
	tools::log("find g_globalvars at : 0x%p\n", g_globalvars);
	tools::log("find g_clientmode at : 0x%p\n", g_clientmode);
	tools::log("find clientstate at : 0x%p\n", g_clientstate);
}

