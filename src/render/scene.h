#ifndef __RENDER_SCENE_H__
#define __RENDER_SCENE_H__

#include "draw.h"

#define MAX_OBJECTS 100

// SoA approach to organizing object data
typedef struct Scene_t{
    float xPos[MAX_OBJECTS];
    float yPos[MAX_OBJECTS];

    float xVel[MAX_OBJECTS];
    float yVel[MAX_OBJECTS];

    float xSize[MAX_OBJECTS];
    float ySize[MAX_OBJECTS];
    int objCount;
} Scene_t;

void initScene(Vec2 initBounds);

void drawScene(void);

#endif