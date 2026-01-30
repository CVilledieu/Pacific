#ifndef __ENTITIES_H__
#define __ENTITIES_H__

#include "engine/common/types.h"

int addEntity(EntityList_t* cast, Vec2 pos, Vec2 size, Vec2 speed);

void newEntityList(EntityList_t** new, MeshBase_t meshBase);

void deleteList(EntityList_t** cast, int size);

#endif