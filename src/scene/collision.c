
// Collision detection system
// 
#include "render/scene.h"
typedef struct Collision_t{

} Collision_t;

void checkCollision(int id){
    if (scene.xPos[id] >= bounds[xCoord]){
        scene.xPos[id] = bounds[xCoord];
        scene.xVel[id] *= -1.0f;
        
    }else if (scene.xPos[id] <= -bounds[xCoord]){
        scene.xPos[id] = (bounds[xCoord] * -1);
        scene.xVel[id] *= -1.0f;
    }

    if (scene.yPos[id] >= bounds[yCoord]){
        scene.yPos[id] = bounds[yCoord];
        scene.yVel[id] *= -1.0f;
    }else if (scene.yPos[id] <= -bounds[yCoord]){
        scene.yPos[id] = (bounds[yCoord] * -1);
        scene.yVel[id] *= -1.0f;
    }
}