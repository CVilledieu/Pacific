#include "scene.h"
#include "draw.h"
#include "common/error.h"

#include "glad/glad.h"
#include <glfw/glfw3.h>

#include <stdio.h>

ObjectData tempObjs[4] = {
    {{-4.2f, -1.0f}, {4.2f, 1.0f}, {0.02f, 0.01f}},
    {{-0.5f, 1.0f}, {1.0f, 1.0f}, {0.02f, 0.01f}},
    {{4.0f, 1.0f}, {1.0f, 3.0f}, {0.02f, 0.01f}},
    {{3.0f, -1.0f}, {1.0f, 1.0f}, {0.02f, 0.01f}},
};


Vec2 stage = {0, 0};
Objects_t list = {0}; 
static int oCount = 0;


// Render piple always results in a number between -1 and 1, so
// Dividing 1 by the perspective scaler gets the window boundaries into model coordinates 
void setStageSize(Vec2 worldScale){
    stage[X] = (1 / worldScale[X]);
    stage[Y] = (1 / worldScale[Y]);
}

// Updates xPos and yPos seperately to take advantage of SoA approach
void updateScenePos(void){
    for (int id = 0; id < oCount; id++){
        float newPos = list.xPos[id] + list.xVel[id];
        float outOfBounds = stage[X] - (list.xSize[id]/2);
        if (newPos >= outOfBounds){
            list.xPos[id] = outOfBounds;
            list.xVel[id] *= -1;
        } else if (newPos <= -outOfBounds){
            list.xPos[id] = -outOfBounds;
            list.xVel[id] *= -1;
        } else {
            list.xPos[id] = newPos;
        }
    }

    for (int id = 0; id < oCount; id++){
        float newPos = list.yPos[id] + list.yVel[id];
        float outOfBounds = stage[Y] - (list.ySize[id]/2);
        if (newPos >= outOfBounds){
            list.yPos[id] = outOfBounds;
            list.yVel[id] *= -1;
        } else if (newPos <= -outOfBounds){
            list.yPos[id] = -outOfBounds;
            list.yVel[id] *= -1;
        } else {
           list. yPos[id] = newPos;
        }
    }

}


Err setObject(Vec2 pos, Vec2 size, Vec2 velocity){
    int newID = oCount;
    if (newID > MAX_OBJECTS) return E_OUT_OF_MEMORY;

    list.xPos[newID] = pos[X];
    list.yPos[newID] = pos[Y];

    list.xSize[newID] = size[X];
    list.ySize[newID] = size[Y];
        
    list.xVel[newID] = velocity[X];
    list.yVel[newID] = velocity[Y];

    oCount++;

    return E_SUCCESS;
}

//Only checking 1 result right now. Since object creation is static and uniform, if one fail all would fail
void loadObjects(ObjectData* data, int num){
    for (int i = 0; i < num; i++){
        int res = setObject(data[i][0], data[i][1], data[i][2]);
        if (res != 0){
            logErr(res, "Failed to load object from data");
        }
    }
}


int flushScene(void){

}


// Model's matrix is handled differently than the Perspective matrix
// An identity matrix is initialized each time function is called, so no artifacts are left from other models.
// This way the amount of memory used is not linear with the number of objects
// TEMP: moved into drawScene for simplicty and to be able to pass Program ID easier
// void setModelMatrix(int index){
//     float mat4[16] = {
//         1.0f, 0.0f, 0.0f, 0.0f,
//         0.0f, 1.0f, 0.0f, 0.0f,
//         0.0f, 0.0f, 1.0f, 0.0f,
//         0.0f, 0.0f, 0.0f, 1.0f,
//     };

//     mat4[0] = list.xSize[index];
//     mat4[5] = list.ySize[index];

//     mat4[12] = list.xPos[index];
//     mat4[13] = list.yPos[index];

//     unsigned int uniformLoc = glGetUniformLocation(rCtx.PID, "uModel");
//     glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, mat4);
//     glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
// }


void drawScene(unsigned int uniformLoc){
    updateScenePos();

    for (int i = 0; i < oCount; i++){
        float mat4[16] = {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f,
        };

        mat4[0] = list.xSize[i];
        mat4[5] = list.ySize[i];

        mat4[12] = list.xPos[i];
        mat4[13] = list.yPos[i];

        glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, mat4);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);   
    }
}


// DevNote: Currently has staticly created objects for debugging / dev purposes
void initScene(Vec2 cameraScale){
    setStageSize(cameraScale);
    loadObjects(tempObjs, 4);

}
