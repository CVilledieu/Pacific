#include "movement.h"
#include "engine/types.h"
#include "engine/ecs/entities.h"
#include <stdio.h>

void moveEntities(void){
    for (int i = 0; i < creatures->count; i++){
        creatures->x[i] += creatures->dX[i];
    }

    for (int j = 0; j < creatures->count; j++){
        creatures->y[j] += creatures->dY[j];
    }
}


void setXVelocity(int id, float force){
    creatures->dX[id] = force;
}

void setYVelocity(int id, float force){
    creatures->dY[id] = force;
}

void stopMovement(int id){
    creatures->dX[id] = 0;
    creatures->dY[id] = 0;
}