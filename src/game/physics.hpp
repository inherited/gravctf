#ifndef PHYSICS_H
#define PHYSICS_H

#include <base/vmath.hpp>
#include <game/server/gamecontext.hpp>
#include <engine/e_config.h>

int gravtiles;
vec2 gravtile[128];

vec2 gravity(vec2 pos)
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
		len /= tuning.gravity_factor*1.0;
		res.x += tuning.gravity * ax / (pow(len, tuning.gravity_power));
		res.y += tuning.gravity * ay / (pow(len, tuning.gravity_power));
	}
	return res;
}

float gravity_x(vec2 pos)
{
	return gravity(pos).x;
}

float gravity_y(vec2 pos)
{
	return gravity(pos).y;
}


#endif
