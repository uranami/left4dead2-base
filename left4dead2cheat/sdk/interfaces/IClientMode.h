#pragma once

class c_viewsetup
{
public:
	uint32_t x; //0x0000
	uint32_t unscale_x; //0x0004
	uint32_t y; //0x0008
	uint32_t unscale_y; //0x000C
	uint32_t w; //0x0010
	uint32_t unscale_w; //0x0014
	uint32_t h; //0x0018
	uint32_t unscale_h; //0x001C
	bool m_bortho; //0x0020
	char pad_0021[3]; //0x0021
	float m_orholeft; //0x0024
	float m_orhotop; //0x0028
	float m_orhoright; //0x002C
	float m_orhobottom; //0x0030
	float m_fov; //0x0034
	float m_viewmodelfov; //0x0038
	QAngle origin; //0x003C
	QAngle angles; //0x0048
	float z_near; //0x0054
	float z_far; //0x0058
	float viewmodel_znear; //0x005C
	float viewmodel_zfar; //0x0060
	bool m_rendertosublargerscreen; //0x0064
	char pad_0065[3]; //0x0065
	float m_aspectratio; //0x0068
	char pad_006C[4068]; //0x006C
}; //Size: 0x1050
   //now we have fov hack!!!
class IClientMode;