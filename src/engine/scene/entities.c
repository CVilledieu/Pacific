#include "entities.h"

#include <stdlib.h>


int addEntity(EntityList_t* cast, Vec2 pos, Vec2 size, Vec2 speed){
    int entityId = cast->count;
    if(entityId >= MAX_MODEL_COUNT) {
        return -1;
    }

    cast->x[entityId] = pos[X];
    cast->y[entityId] = pos[Y];

    cast->width[entityId] = size[X];
    cast->height[entityId] = size[Y];

    cast->dX[entityId] = speed[X];
    cast->dY[entityId] = speed[Y];
    cast->count++;
    return entityId;
}

void newEntityList(EntityList_t** new, MeshBase_t meshBase){
    *new = malloc(sizeof(EntityList_t));
    (*new)->baseType = meshBase;
    (*new)->count = 0;
}

void deleteList(EntityList_t** cast, int size){
    if (size < 1) return;
    for (int i = 0; i < size; i++){
        free(cast[i]);
    }
}

void nextFrame(EntityList_t* cast){
    for (int id = 0; id < cast->count; id++){
        
    }
}