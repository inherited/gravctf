
#include <game/server/gamecontext.hpp>
#include <engine/e_config.h>

#include "physics.hpp"

int gravtiles;
vec2 gravtile[128];

vec2 gravity(vec2 pos, float g, float gfactor, float gpower)
{
	vec2 res;
	res.x = 0;
	res.y = 0;
	for(int i = 0; i < gravtiles; i++) {
		float ax = gravtile[i].x - pos.x;
		float ay = gravtile[i].y - pos.y;
		//normalize;
		float len = sqrtf(ax*ax + ay*ay);
		ax = ax / len;
		ay = ay / len;
		len /= gfactor*1.0;
		res.x += g * ax / (pow(len, gpower));
		res.y += g * ay / (pow(len, gpower));
	}
	return res;
}

float gravity_x(vec2 pos, float g, float gfactor, float gpower)
{
	return gravity(pos, g, gfactor, gpower).x;
}

float gravity_y(vec2 pos, float g, float gfactor, float gpower)
{
	return gravity(pos, g, gfactor, gpower).y;
}
