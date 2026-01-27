#include "scene.h"
#include "draw.h"
#include "common/error.h"

#include "glad/glad.h"
#include <glfw/glfw3.h>

#include <stdio.h>


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
void moveSceneObjects(void){
    for (int id = 0; id < oCount; id++){
        float newPos = list.xPos[id] + list.xVel[id];
        if (newPos >= stage[X]){
            list.xPos[id] = stage[X];
            list.xVel[id] *= -1;
        } else if (newPos <= -stage[X]){
            list.xPos[id] = -stage[X];
            list.xVel[id] *= -1;
        } else {
            list.xPos[id] = newPos;
        }
    }

    for (int id = 0; id < oCount; id++){
        float newPos = list.yPos[id] + list.yVel[id];
        if (newPos >= stage[Y]){
            list.yPos[id] = stage[Y];
            list.yVel[id] *= -1;
        } else if (newPos <= -stage[Y]){
            list.yPos[id] = -stage[Y];
            list.yVel[id] *= -1;
        } else {
           list. yPos[id] = newPos;
        }
    }

}


Err newObject(Vec2 pos, Vec2 size, Vec2 velocity){
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
void loadObjects(void){
    Vec2 obj1[3] = {{-4.2f, -1.0f}, {1.0f, 1.0f}, {0.07f, 0.06f}};
    Vec2 obj2[3] = {{-0.5f, 1.0f}, {1.0f, 1.0f}, {0.07f, 0.06f}};
    Vec2 obj3[3] = {{4.0f, 1.0f}, {1.0f, 1.0f}, {0.07f, 0.06f}};
    Vec2 obj4[3] = {{3.0f, -1.0f}, {1.0f, 1.0f}, {0.07f, 0.06f}};
    int res = 0;
    res = newObject(obj1[0], obj1[1], obj1[2]);
    if (res != 0){
        logErr(res, "Failed to create obj");
    }

    newObject(obj2[0], obj2[1], obj2[2]);
    newObject(obj3[0], obj3[1], obj3[2]);
    newObject(obj4[0], obj4[1], obj4[2]);
}


int flushScene(void){

}


// Model's matrix is handled differently than the Perspective matrix
// An identity matrix is initialized each time function is called, so no artifacts are left from other models.
// This way the amount of memory used is not linear with the number of objects
void setModelMatrix(int index){
    float mat4[16] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
    };

    mat4[0] = list.xSize[index];
    mat4[5] = list.ySize[index];

    mat4[12] = list.xPos[index];
    mat4[13] = list.yPos[index];

    unsigned int uniformLoc = glGetUniformLocation(rCtx.PID, "uModel");
    glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, mat4);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


// DevNote: broke off from drawScene, for more customize ablity with both
void renderObjects(void){
    moveSceneObjects();
    for (int i = 0; i < oCount; i++){
        setModelMatrix(i);   
    }
}


// DevNote: Currently has staticly created objects for debugging / dev purposes
void initScene(Vec2 cameraScale){
    setStageSize(cameraScale);
    loadObjects();

}
