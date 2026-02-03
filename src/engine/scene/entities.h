#ifndef __ENTITIES_H__
#define __ENTITIES_H__

#include "engine/types.h"

// Properties: Number of indices, Pos(x,y,z), Velocity(dX, dY, dZ), Size(width, height, length)

extern Entities_t* creatures;
extern Entities_t* constructs;

void initECS(ECS_t* ecs);

void newCreature(Vec2 pos, Vec2 size, Vec2 speed);
void newConstruct(Vec2 pos, Vec2 size);

void moveEntityUpDown(int id, float force);
void moveEntityLeftRight(int id, float force);

#endif