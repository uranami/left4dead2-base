#pragma once

typedef unsigned long HFont;


enum FontFlags_t
{
	FONTFLAG_NONE,
	FONTFLAG_ITALIC = 0x001,
	FONTFLAG_UNDERLINE = 0x002,
	FONTFLAG_STRIKEOUT = 0x004,
	FONTFLAG_SYMBOL = 0x008,
	FONTFLAG_ANTIALIAS = 0x010,
	FONTFLAG_GAUSSIANBLUR = 0x020,
	FONTFLAG_ROTARY = 0x040,
	FONTFLAG_DROPSHADOW = 0x080,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400,
	FONTFLAG_BITMAP = 0x800,
};

class ISurface
{
public:

	void set_color(const int r, const int g, const int b, const int a)
	{
		callvtable<void(__thiscall*)(void*, int, int, int, int)>(this, 11)(this, r, g, b, a);
	}

	void draw_line(int x0, int y0, int x1, int y1)
	{
		callvtable<void(__thiscall*)(void*, int, int, int, int)>(this, 15)(this, x0, y0, x1, y1);
	}

	void draw_outlined_rect(int x0, int y0, int x1, int y1)
	{
		callvtable<void(__thiscall*)(void*, int, int, int, int)>(this, 14)(this, x0, y0, x1, y1);
	}

	void draw_filled_rect(int x0, int y0, int x1, int y1)
	{
		callvtable<void(__thiscall*)(void*, int, int, int, int)>(this, 12)(this, x0, y0, x1, y1);
	}

	void set_text_color(const int r, const int g, const int b, const int a)
	{
		callvtable<void(__thiscall*)(void*, int, int, int, int)>(this, 19)(this, r, g, b, a);
	}

	void set_text_pos(const int x, const int y)
	{
		callvtable<void(__thiscall*)(void*, int, int)>(this, 20)(this, x, y);
	}

	void set_text_font(HFont font)
	{
		callvtable<void(__thiscall*)(void*, unsigned long)>(this, 17)(this, font);
	}

	void draw_text(const wchar_t* text, const int len)
	{
		callvtable<void(__thiscall*)(void*, wchar_t const*, int, int)>(this, 22)(this, text, len, 0);
	}

	void set_mouse_visible(bool visible)
	{
		callvtable<void(__thiscall*)(void*, bool)>(this, 49)(this, visible);
	}

	HFont create_font()
	{
		return callvtable<HFont(__thiscall*)(void*)>(this, 63)(this);
	}

	bool set_font_glyph(HFont font, const char* windowsfontname, std::int32_t tall, std::int32_t weight, std::int32_t blur, std::int32_t scanlines, std::int32_t flags, std::int32_t nRangeMin = 0, std::int32_t nRangeMax = 0)
	{
		return callvtable<bool(__thiscall*)(void*, HFont, const char*, int, int, int, int, int, int, int)>(this, 64)(this, font, windowsfontname, tall, weight, blur, scanlines, flags, nRangeMin, nRangeMax);
	}

	void get_text_size(HFont font, const wchar_t* text, int& wide, int& tall)
	{
		callvtable<void(__thiscall*)(void*, HFont, const wchar_t*, int&, int&)>(this, 72)(this, font,  text, wide, tall);
	}
};