#ifndef __ENTITIES_H__
#define __ENTITIES_H__

#include "engine/types.h"

// Properties: Number of indices, Pos(x,y,z), Velocity(dX, dY, dZ), Size(width, height, length)

void initECS(ECS_t* ecs);

void newCreature(Vec2 pos, Vec2 size, Vec2 speed);
void newConstruct(Vec2 pos, Vec2 size);

#endif