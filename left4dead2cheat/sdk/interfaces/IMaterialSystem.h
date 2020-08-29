#pragma once

class KeyValues
{
public:
	int m_iKeyName;
	char* m_sValue;
	wchar_t* m_wsValue;

	union {
		int m_iValue;
		float m_flValue;
		void* m_pValue;
		unsigned char m_Color[4];
	};

	char m_iDataType;
	char m_bHasEscapeSequences;
	char m_bEvaluateConditionals;
	char unused[1];

	KeyValues* m_pPeer;
	KeyValues* m_pSub;
	KeyValues* m_pChain;
};
class IFileSystem;

typedef unsigned short mat_handle_t;

class IMaterial
{
public:
	const char* get_name()
	{
		return callvtable<const char*(__thiscall*)(IMaterial*)>(this, 0)(this);
	}

	inline void set_material_flag(MaterialVarFlags_t flag, bool on)
	{
		return callvtable<void(__thiscall*)(IMaterial*, MaterialVarFlags_t, bool)>(this, 29)(this, flag, on);
	}

	inline void override_color(float r, float g, float b)
	{
		return callvtable<void(__thiscall*)(IMaterial*, float, float, float)>(this, 28)(this, r, g, b);
	}

	inline void IncrementReferenceCount()
	{
		return callvtable<void(__thiscall*)(void*)>(this, 14)(this);
	}

	inline void	override_alpha(float alpha)
	{
		return callvtable<void(__thiscall*)(void*, float)>(this, 27)(this, alpha);
	}
};

class IMaterialSystem
{
public:
	IMaterial* find_material(char const* pMaterialName, const char* pTextureGroupName, bool complain = true, const char* pComplainPrefix = 0)
	{
		return callvtable<IMaterial* (__thiscall*)(IMaterialSystem*, const char*, const char*, bool, const char*)>(this, 71)(this, pMaterialName, pTextureGroupName, complain, pComplainPrefix);
	}

	IMaterial* create_material (char const* materialname, KeyValues* kv)
	{
		return callvtable<IMaterial*(__thiscall*)(void*, char const*, KeyValues*)>(this, 70)(this, materialname, kv);
	}

	mat_handle_t first_material()
	{
		return callvtable<mat_handle_t(__thiscall*)(void*)>(this, 72)(this);
	}

	mat_handle_t invalid_material()
	{
		return callvtable<mat_handle_t(__thiscall*)(void*)>(this, 74)(this);
	}

	mat_handle_t next_material(mat_handle_t h)
	{
		return callvtable<mat_handle_t(__thiscall*)(void*, mat_handle_t)>(this, 73)(this,h);
	}

	IMaterial* get_material(mat_handle_t h)
	{
		return callvtable<IMaterial*(__thiscall*)(void*, mat_handle_t)>(this, 75)(this, h);
	}

};

#define TEXTURE_GROUP_LIGHTMAP "Lightmaps"
#define TEXTURE_GROUP_WORLD "World textures"
#define TEXTURE_GROUP_MODEL "Model textures"
#define TEXTURE_GROUP_VGUI "VGUI textures"
#define TEXTURE_GROUP_PARTICLE "Particle textures"
#define TEXTURE_GROUP_DECAL "Decal textures"
#define TEXTURE_GROUP_SKYBOX "SkyBox textures"
#define TEXTURE_GROUP_CLIENT_EFFECTS "ClientEffect textures"
#define TEXTURE_GROUP_OTHER "Other textures"
#define TEXTURE_GROUP_PRECACHED \ "Precached"  // TODO: assign texture groups to the precached materials
#define TEXTURE_GROUP_CUBE_MAP "CubeMap textures"
#define TEXTURE_GROUP_RENDER_TARGET "RenderTargets"
#define TEXTURE_GROUP_UNACCOUNTED \ "Unaccounted textures"  // Textures that weren't assigned a texture group.
//#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER		"Static Vertex"
#define TEXTURE_GROUP_STATIC_INDEX_BUFFER "Static Indices"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_DISP "Displacement Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_COLOR "Lighting Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_WORLD "World Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_MODELS "Model Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_OTHER "Other Verts"
#define TEXTURE_GROUP_DYNAMIC_INDEX_BUFFER "Dynamic Indices"
#define TEXTURE_GROUP_DYNAMIC_VERTEX_BUFFER "Dynamic Verts"
#define TEXTURE_GROUP_DEPTH_BUFFER "DepthBuffer"
#define TEXTURE_GROUP_VIEW_MODEL "ViewModel"
#define TEXTURE_GROUP_PIXEL_SHADERS "Pixel Shaders"
#define TEXTURE_GROUP_VERTEX_SHADERS "Vertex Shaders"
#define TEXTURE_GROUP_RENDER_TARGET_SURFACE "RenderTarget Surfaces"
#define TEXTURE_GROUP_MORPH_TARGETS "Morph Targets"