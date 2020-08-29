#pragma once

class CModelInfo
{
public:
	inline void* get_model(int nIndex)
	{
		return callvtable<void* (__thiscall*)(void*, int)>(this, 1)(this, nIndex);
	}

	studiohdr_t* get_studio_model(const model_t* model)
	{
		return callvtable<studiohdr_t* (__stdcall*)(const model_t*)>(this, 30)(model);
	}

	const char* get_model_name(const model_t* model)
	{
		return callvtable<const char* (__thiscall*)(void*, const model_t*)>(this, 3)(this, model);
	}
};