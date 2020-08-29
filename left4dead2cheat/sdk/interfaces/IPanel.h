#pragma once

class IPanel
{
public:
	const char* get_panel_name(int panel)
	{
		return callvtable<const char* (__thiscall*)(IPanel*, int)>(this, 36)(this, panel);
	}
};