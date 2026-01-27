#include "scene.h"

#include "glad/glad.h"
#include <glfw/glfw3.h>

#include <stdio.h>


int nObjects = 0;
Vec2 sceneEdge = {0, 0}; 
Scene_t scene = {0};


int newObject(Vec2 pos, Vec2 size, Vec2 velocity);

void setPos(int id, Vec2 value);
void setSize(int id, Vec2 value);
void setVelocity(int id, Vec2 value);
void getSceneEdge(Vec2 worldScale);

// DevNote: Currently has staticly created objects for debugging / dev purposes
void initScene(Vec2 worldScale){

    getSceneEdge(worldScale);

    newObject((Vec2){-4.2f, 1.0f}, (Vec2){1.0f, 1.0f}, (Vec2){0.07f, 0.06f} );
    newObject((Vec2){4.5f, -1.0f}, (Vec2){1.0f, 1.0f}, (Vec2){0.1f, 0.09f} );
    newObject((Vec2){4.0f, -2.0f}, (Vec2){1.0f, 1.0f}, (Vec2){0.1f, 0.099f} );
    newObject((Vec2){3.0f, -1.5f}, (Vec2){1.0f, 1.0f}, (Vec2){0.1f, 0.09f} );
}


int newObject(Vec2 pos, Vec2 size, Vec2 velocity){
    int newID = scene.objCount;

    if (newID > MAX_OBJECTS) return 1;
    
    setPos(newID, pos);
    setSize(newID, size);
    setVelocity(newID, velocity);

    scene.objCount++;
}

void updateScene(void){
    for (int id = 0; id < scene.objCount; id++){
        scene.xPos[id] += scene.xVel[id];
        scene.yPos[id] += scene.yVel[id];
    }
}

void checkEdgeCollision(int id){
    // Check if boundary was hit
    // If boundary is hit. Sets pos to boundary value and reverse direction
    if (scene.xPos[id] >= sceneEdge[xCoord]){
        scene.xPos[id] = sceneEdge[xCoord];
        scene.xVel[id] *= -1.0f;
        
    }else if (scene.xPos[id] <= -sceneEdge[xCoord]){
        scene.xPos[id] = (sceneEdge[xCoord] * -1);
        scene.xVel[id] *= -1.0f;
    }

    if (scene.yPos[id] >= sceneEdge[yCoord]){
        scene.yPos[id] = sceneEdge[yCoord];
        scene.yVel[id] *= -1.0f;
    }else if (scene.yPos[id] <= -sceneEdge[yCoord]){
        scene.yPos[id] = (sceneEdge[yCoord] * -1);
        scene.yVel[id] *= -1.0f;
    }
}

void setPos(int id, Vec2 value){
    scene.xPos[id] = value[xCoord];
    scene.yPos[id] = value[yCoord];
}

void setVelocity(int id, Vec2 value){
    scene.xVel[id] = value[xCoord];
    scene.yVel[id] = value[yCoord];
}

void setSize(int id, Vec2 value){
    scene.xSize[id] = value[xCoord];
    scene.ySize[id] = value[yCoord];
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
    mat4[0] = scene.xSize[index];
    mat4[5] = scene.ySize[index];

    mat4[12] = scene.xPos[index];
    mat4[13] = scene.yPos[index];
    unsigned int uniformLoc = glGetUniformLocation(rCtx.PID, "uModel");
    glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, mat4);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


void drawScene(void){
    for (int i = 0; i < scene.objCount; i++){
        setModelMatrix(i);
        

        moveObject(i);
    }

}

// Render piple always results in a number between -1 and 1, so
// Dividing 1 by the perspective scaler gets the window boundaries into model coordinates 
void getSceneEdge(Vec2 worldScale){
    sceneEdge[xCoord] = (1 / worldScale[xCoord]);
    sceneEdge[yCoord] = (1 / worldScale[yCoord]);
}