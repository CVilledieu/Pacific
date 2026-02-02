#ifndef __ECS_H__
#define __ECS_H__

#include "engine/types.h"

void initECS(ECS_t* ecs);

void newCreature(Vec3 pos, Vec3 size, Vec3 speed);
void newConstruct(Vec3 pos, Vec3 size);

#endif