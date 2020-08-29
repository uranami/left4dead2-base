#pragma once

class CGlobalVarsBase
{
public:
	float			realtime;
	int				framecount;
	float			absoluteframetime;
	float			curtime;
	float			frametime;
	int				max_clients;
	int				tickcount;
	float			interval_per_tick;
	float			interpolation_amount;
	int				sim_ticks_this_frame;
	int				network_protocol;
};