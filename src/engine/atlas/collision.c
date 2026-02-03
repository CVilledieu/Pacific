#include "collision.h"

#include "engine/types.h"
#include <stdio.h>

/*
    Implementation ideas:
    create list of entities that want to move.
        - Create a seperate struct that contains movement?
    EntityList_t movers[]
    canMove(EntityList_t movers)
    if (!Collisions) 
        applyMovement()
    else 
        nothing || rejectedMovement()
    


*/


// void AABBCollision(EntityList_t* list){
//     int *secondary = malloc(sizeof(int) * list->count);
//     int sentToSecondary = 0;

//     float leftA, 

//     float topA = list->y[idA] + list->height[idA];
//     float bottomA  = list->y[idA] - list->height[idA];
//     float topB = list->y[idB] + list->height[idB];
//     if (bottomA > topB){
//         printf("Hit\n");
//         printf("ObjectId: %i, axis value: %f\n", idA, bottomA);
//         printf("ObjectId: %i, axis value: %f\n", idB, topB);
//     }


// }

