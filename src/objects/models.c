#include "models.h"



int newObject(RenderList_t* list, float pos[2], float size[2]){
    int index = list->objectCount;
    if (index >= MAX_OBJECTS) {
        return -1;
    }

    list->xPos[index] = pos[0];
    list->yPos[index] = pos[1];

    list->xSize[index] = size[0];
    list->ySize[index] = size[1];
    list->objectCount++;
    return 0;
}

// int newObject(float xPos,float yPos, float xScale, float yScale){
//     int index = RenderList.objectCount;
//     if (index >= MAX_OBJECTS) {
//         return -1;
//     }

//     RenderList.xPos[index] = xPos;
//     RenderList.yPos[index] = yPos;
//     RenderList.xScale[index] = xScale;
//     RenderList.yScale[index] = yScale;

//     RenderList.objectCount++;

//     return 0;
// }