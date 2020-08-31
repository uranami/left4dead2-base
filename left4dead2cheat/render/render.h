#pragma once
#include "..\sdk\interfaces.h"

namespace g_draw
{
	void setup_font();

	void draw_text(int x, int y, std::string_view str, Color col, HFont font);

	namespace font
	{
		extern HFont watermark;
	}

}

