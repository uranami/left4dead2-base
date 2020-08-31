#include "render.h"

unsigned long g_draw::font::watermark = NULL;

void g_draw::setup_font()
{
	g_surfaces->set_font_glyph(g_draw::font::watermark = g_surfaces->create_font(), "Tahoma", 12, 700, 0, 0, FONTFLAG_DROPSHADOW);
}

void g_draw::draw_text(int x, int y, std::string_view str, Color col, HFont font)
{
	const auto wchar = std::wstring(str.begin(), str.end());

	int w, h;
	g_surfaces->get_text_size(font, wchar.data(), w, h);
	g_surfaces->set_text_font(font);
	g_surfaces->set_text_pos(x, y);
	g_surfaces->set_text_color(col.red, col.green, col.blue, col.alpha);
	g_surfaces->draw_text(wchar.data(), wcslen(wchar.data()));
}