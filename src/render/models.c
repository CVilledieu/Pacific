#include "models.h"

#include "glad/glad.h"
#include <glfw/glfw3.h>

#include <stdio.h>

// Should probably change to something like eX = 0, and eY.
// At the moment no issues, but could easily cause a problem
static enum {
    X = 0,
    Y,
} COORD;

int nObjects = 0;
Vec2 bounds = {0, 0}; 
Objects_t objList = {0};


int newObject(Vec2 pos, Vec2 size, Vec2 velocity);

void updateBoundary(float x, float y);

void setPos(int id, Vec2 value);
void setSize(int id, Vec2 value);
void setVelocity(int id, Vec2 value);

// DevNote: Currently has staticly created objects for debugging / dev purposes
void initObjects(float x, float y){

    updateBoundary(x, y);

    newObject((Vec2){-4.2f, 1.0f}, (Vec2){1.0f, 1.0f}, (Vec2){0.07f, 0.06f} );
    newObject((Vec2){4.2f, -1.0f}, (Vec2){1.0f, 1.0f}, (Vec2){0.1f, 0.09f} );
}


int newObject(Vec2 pos, Vec2 size, Vec2 velocity){
    if (nObjects > MAX_OBJECTS) return 1;

    setPos(nObjects, pos);
    setSize(nObjects, size);
    setVelocity(nObjects, velocity);

    nObjects++;
}

void moveVelocity(int id){
    objList.xPos[id] += objList.xVel[id];
    if (objList.xPos[id] >= bounds[X] || objList.xPos[id] <= -bounds[X]){
        if(objList.xVel[id] > 0){
            objList.xPos[id] = bounds[X];
        } else {
            objList.xPos[id] = bounds[X];
            objList.xPos[id] *= -1;
        }
        
        objList.xVel[id] *= -1.0f;
    }


    objList.yPos[id] += objList.yVel[id];
    if (objList.yPos[id] >= bounds[Y] || objList.yPos[id] <= -bounds[Y]){
        if(objList.yVel[id] > 0){
            objList.yPos[id] = bounds[Y];
        } else {
            objList.yPos[id] = (bounds[Y] * -1);
        }
        objList.yVel[id] *= -1.0f;
    }
}

void setPos(int id, Vec2 value){
    objList.xPos[id] = value[X];
    objList.yPos[id] = value[Y];
}

void setVelocity(int id, Vec2 value){
    objList.xVel[id] = value[X];
    objList.yVel[id] = value[Y];
}

void setSize(int id, Vec2 value){
    objList.xSize[id] = value[X];
    objList.ySize[id] = value[Y];
}



// Model's matrix is handled differently than the Perspective matrix
// An identity matrix is initialized each time function is called, so no artifacts are left from other models.
// This way the amount of memory used is not linear with the number of objects
void setModel(int index){
    float mat4[16] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
    };
    mat4[0] = objList.xSize[index];
    mat4[5] = objList.ySize[index];

    mat4[12] = objList.xPos[index];
    mat4[13] = objList.yPos[index];
    unsigned int uniformLoc = glGetUniformLocation(rCtx.PID, "uModel");
    glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, mat4);

}


void drawModels(void){
    for (int i = 0; i < nObjects; i++){
        setModel(i);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        moveVelocity(i);
    }

}

// Render piple always results in a number between -1 and 1, so
// Dividing 1 by the perspective scaler gets the window boundaries into model coordinates 
void updateBoundary(float x, float y){
    bounds[X] = (1 / x) - 0.5f;
    bounds[Y] = 1 / y - 0.5f;
}