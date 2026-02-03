#include "entities.h"
 
#include <stdlib.h>

Entities_t* creatures = NULL;
Entities_t* constructs = NULL;

void initEntities(Atlas_t* atlas){
    creatures = &atlas->creatures;
    constructs = &atlas->constructs;
}

// Index zero of creatures is reserved / occupide by the player controlled unit aka the Hero unit
void setHero(void){
    creatures->x[0] = DEFAULT_HERO_X;
    creatures->y[0] = DEFAULT_HERO_Y;
    creatures->width[0] = DEFAULT_HERO_W;
    creatures->height[0] = DEFAULT_HERO_H;
    creatures->count = 1;
}


void newEntity(Entity_t obj){
    Entities_t* list = NULL;
    if (obj.ObjType == 0) {
        list = creatures;
    } else {
        list = constructs;
    }
    
    if (list->count >= MAX_MODEL_COUNT) return;

    int id = list->count;
    list->x[id] = obj.x;
    list->y[id] = obj.y;

    list->width[id] = obj.width;
    list->height[id] = obj.height;

    list->dX[id] = obj.dX;
    list->dY[id] = obj.dY;

    list->count++;
}


inline void moveVertical(int id, float force){
    creatures.y[id] += force;
}

inline void moveHorizontal(int id, float force){
    constructs->x[id] += force;
}

// void initECS(ECS_t* ecs){

//     newCreature((Vec2){-0.5f, 0.2f}, (Vec2){1.0f, 0.9f}, (Vec2){0.0f, 0.0f});
//     newConstruct((Vec2){0.3f, -0.9f}, (Vec2){0.8f, 0.8f});
// }
