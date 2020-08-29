#include "..\hooks.h"

void __fastcall hook::enginepaint(IEngineVGui* _ecx, void* _edx, paintmode_t mode)
{

	static auto original_enginepaint = enginevguihook->getoriginal<fnenginepaint>(index::paint);
	original_enginepaint(_ecx, mode);

	static auto g_startdraw = reinterpret_cast<void(__thiscall*)(void*)>(tools::findpattern("vguimatsurface.dll", "33 C5 50 8D 45 F4 64 A3 ? ? ? ? 8B F9 80 3D") - 0x1B);
	static auto g_enddraw = reinterpret_cast<void(__thiscall*)(void*)>(tools::findpattern("vguimatsurface.dll", "51 56 A1 ? ? ? ? 33 C5 50 8D 45 F4 64 A3 ? ? ? ? 6A") - 0x11);

	if (mode & paintmode_t::PAINT_UIPANELS)
	{
		//start draw
		g_startdraw(g_surfaces);



		g_enddraw(g_surfaces);
	}

}