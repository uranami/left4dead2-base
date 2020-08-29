#include "..\hooks.h"

void __fastcall hook::on_screen_size_changed(void* _ecx, int _edx, int old_w, int old_h)
{
	static auto original_scrsize = surfacehook->getoriginal<fnscreensize>(index::on_screen_size_changed);
	original_scrsize(_ecx, old_w, old_h);

}