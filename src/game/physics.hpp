#ifndef PHYSICS_H
#define PHYSICS_H

#include <base/vmath.hpp>

extern int gravtiles;
extern vec2 gravtile[128];

extern vec2 gravity(vec2 pos, float g, float gfactor, float gpower);
extern float gravity_x(vec2 pos, float g, float gfactor, float gpower);
extern float gravity_y(vec2 pos, float g, float gfactor, float gpower);


#endif
