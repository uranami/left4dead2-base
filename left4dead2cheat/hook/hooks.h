#pragma once
#include "index.h"
#include "..\render\render.h"
#include "..\sdk\interfaces.h"
#include "..\tools\vmthook.h"
#include "..\tools\math.h"

extern std::unique_ptr<vmthook> clientmodehook;
extern std::unique_ptr<vmthook> chlclienthook;
extern std::unique_ptr<vmthook> enginevguihook;
extern std::unique_ptr<vmthook> matsystemhok;
extern std::unique_ptr<vmthook> directhook;
extern std::unique_ptr<vmthook> modelrenderhook;
extern std::unique_ptr<vmthook> surfacehook;

namespace hook
{

	using fnenginepaint = void(__thiscall*) (IEngineVGui*, paintmode_t);
	using fncreatemove = void(__thiscall*)(IBaseClientDll*, int, float, bool);
	using fnoverrideview = void(__thiscall*)(IClientMode*, c_viewsetup*);
	using fnframestagenotify = void(__thiscall*)(IBaseClientDll*, framestage_t);
	using fndrawmodelexecute = void(__thiscall*)(void*, const DrawModelState_t&, const ModelRenderInfo_t&, matrix3x4_t*);
	using fnscreensize = void(__thiscall*)(void*, int, int);

	extern void setup_hook();

	extern void __fastcall enginepaint(IEngineVGui* _ecx, void* _edx, paintmode_t mode);

	extern void __fastcall frame_stage_notify(IBaseClientDll* _ecx, LPVOID _edx, framestage_t stage);

	extern void _fastcall overrideview(IClientMode* _ecx, void* _edx, c_viewsetup* setup);

	extern void __fastcall createmove(IBaseClientDll* _ecx, void* _edx, int sequence_number, float input_sample_frametime, bool active);

	extern void __fastcall draw_model_execute(void* _ecx, int edx, const DrawModelState_t& state, const ModelRenderInfo_t& info, matrix3x4_t* custom_bone);

	extern void __fastcall on_screen_size_changed(void* _ecx, int _edx, int old_w, int old_h);
}