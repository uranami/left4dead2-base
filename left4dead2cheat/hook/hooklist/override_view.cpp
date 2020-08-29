#include "..\hooks.h"

void _fastcall hook::overrideview(IClientMode* _ecx, void* _edx, c_viewsetup* setup)
{

	static auto original_overrideview = clientmodehook->getoriginal< fnoverrideview >(index::overrideview);
	original_overrideview(_ecx, setup);

	if (g_engine->IsInGame())
	{
		setup->m_fov = 110.f;
	}
}