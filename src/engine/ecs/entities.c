#include "entities.h"

#include <stdlib.h>

//static ECS_t ecs;
static Entities_t* creatures;
static Entities_t* constructs;



void newCreature(Vec3 pos, Vec3 size, Vec3 speed){
    if (creatures->count >= MAX_MODEL_COUNT) return;

    int id = creatures->count;
    creatures->x[id] = pos[X];
    creatures->y[id] = pos[Y];
    creatures->z[id] = pos[Z];

    creatures->width[id] = size[X];
    creatures->height[id] = size[Y];
    creatures->length[id] = size[Z];

    creatures->dX[id] = speed[X];
    creatures->dY[id] = speed[Y];
    creatures->dZ[id] = speed[Z];

    creatures->count++;
}

void newConstruct(Vec3 pos, Vec3 size){
    if (constructs->count >= MAX_MODEL_COUNT) return;

    int id = constructs->count;
    constructs->x[id] = pos[X];
    constructs->y[id] = pos[Y];
    constructs->z[id] = pos[Z];

    constructs->width[id] = size[X];
    constructs->height[id] = size[Y];
    constructs->length[id] = size[Z];
    constructs->count++;
}


void initECS(ECS_t* ecs){
    creatures = &ecs->creatures;
    constructs = &ecs->constructs;

    // Explicitly zero the counts (static storage should be zero, but be safe)
    creatures->count = 0;
    constructs->count = 0;

    newCreature((Vec3){-0.5f, 0.2f, 0.0f}, (Vec3){1.0f, 0.9f, 1.0f}, (Vec3){0.0f, 0.0f, 0.0f});
    newConstruct((Vec3){0.3f, -0.9f, 0.0f}, (Vec3){0.8f, 0.8f, 1.0f});
}

void newEntity(Entities_t* list, Vec3 pos, Vec3 size, Vec3 speed){
    if (list->count >= MAX_MODEL_COUNT) return;

    int id = list->count;
    list->x[id] = pos[X];
    list->y[id] = pos[Y];
    list->z[id] = pos[Z];

    list->dX[id] = speed[X];
    list->dY[id] = speed[Y];
    list->dZ[id] = speed[Z];

    list->width[id] = size[X];
    list->height[id] = size[Y];
    list->length[id] = size[Z];
    list->count++;
}
