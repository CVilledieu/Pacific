#ifndef __OBJECTS_MODELS_H__
#define __OBJECTS_MODELS_H__

#include "render/ctx.h"

#define MAX_OBJECTS 100

// SoA approach to organizing object data
typedef struct Objects_t{
    float xPos[MAX_OBJECTS];
    float yPos[MAX_OBJECTS];

    float xVel[MAX_OBJECTS];
    float yVel[MAX_OBJECTS];

    float xSize[MAX_OBJECTS];
    float ySize[MAX_OBJECTS];
} Objects_t;

void initObjects(float x, float y);

void drawModels(void);

#endif