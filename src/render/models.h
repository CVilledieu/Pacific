#ifndef __OBJECTS_MODELS_H__
#define __OBJECTS_MODELS_H__

#include "render/ctx.h"

#define MAX_OBJECTS 100

typedef struct ObjectList_t{
    float xPos[MAX_OBJECTS];
    float yPos[MAX_OBJECTS];
    float xSize[MAX_OBJECTS];
    float ySize[MAX_OBJECTS];
    int objCount;
} ObjectList_t;

void initObjectList(void);

void drawModels(void);

#endif