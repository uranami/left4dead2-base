#include "..\hooks.h"

void __fastcall hook::draw_model_execute(void* _ecx, int edx, const DrawModelState_t& state, const ModelRenderInfo_t& info, matrix3x4_t* custom_bone)
{
	static auto originaldme = modelrenderhook->getoriginal< fndrawmodelexecute >(index::draw_model_execute);

	originaldme(_ecx, state, info, custom_bone);
}

