#ifndef __RENDER_SCENE_H__
#define __RENDER_SCENE_H__

#include "common/types.h"

#define MAX_OBJECTS 100

// SoA approach to organizing object data
typedef struct Objects_t {
    float xPos[MAX_OBJECTS];
    float yPos[MAX_OBJECTS];

    float xVel[MAX_OBJECTS];
    float yVel[MAX_OBJECTS];

    float xSize[MAX_OBJECTS];
    float ySize[MAX_OBJECTS];
} Objects_t;

typedef Vec2 ObjectData[3];


// typedef struct Scene_t{
//     int oCount;
// } Scene_t;


void initScene(Vec2 cameraScale);

void renderObjects(void);

#endif