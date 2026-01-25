#ifndef __RENDER_CTX_H__
#define __RENDER_CTX_H__

#define MAX_OBJECTS 100

typedef struct {
    float xPos[MAX_OBJECTS];
    float yPos[MAX_OBJECTS];
    float xSize[MAX_OBJECTS];
    float ySize[MAX_OBJECTS];
    int objectCount;
} RenderList_t;



void initCtx(void);
void drawList(void);


#endif