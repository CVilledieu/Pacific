#include "entities.h"

#include <stdlib.h>

//static ECS_t ecs;
static Entities_t* creatures = NULL;
static Entities_t* constructs = NULL;



void newCreature(Vec2 pos, Vec2 size, Vec2 speed){
    if (creatures->count >= MAX_MODEL_COUNT) return;

    int id = creatures->count;
    creatures->x[id] = pos[X];
    creatures->y[id] = pos[Y];

    creatures->width[id] = size[X];
    creatures->height[id] = size[Y];

    creatures->dX[id] = speed[X];
    creatures->dY[id] = speed[Y];

    creatures->count++;
}

void newConstruct(Vec2 pos, Vec2 size){
    if (constructs->count >= MAX_MODEL_COUNT) return;

    int id = constructs->count;
    constructs->x[id] = pos[X];
    constructs->y[id] = pos[Y];

    constructs->width[id] = size[X];
    constructs->height[id] = size[Y];

    constructs->dX[id] = 0;
    constructs->dY[id] = 0;

    constructs->count++;
}


void initECS(ECS_t* ecs){
    creatures = &ecs->creatures;
    constructs = &ecs->constructs;
    creatures->count = 0;
    constructs->count = 0;

    newCreature((Vec2){-0.5f, 0.2f}, (Vec2){1.0f, 0.9f}, (Vec2){0.0f, 0.0f});
    newConstruct((Vec2){0.3f, -0.9f}, (Vec2){0.8f, 0.8f});
}
