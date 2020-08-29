#include "../hooks.h"

void __fastcall hook::frame_stage_notify(IBaseClientDll* _ecx, LPVOID _edx, framestage_t stage)
{
	static auto original_frame_stage_notify = chlclienthook->getoriginal<fnframestagenotify>(index::frame_stage_noify);

	original_frame_stage_notify(_ecx, stage);
}

