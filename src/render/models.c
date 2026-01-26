#include "models.h"

#include "glad/glad.h"
#include <glfw/glfw3.h>

#include <stdio.h>

ObjectList_t objList = {0};

int newObject(float xPos, float yPos, float xSize, float ySize);

// DevNote: At the moment sets specific object data. Will createa more dynamic way to create the objects
void initObjectList(void){
    newObject(-1.0f, -1.0f, 1.0f, 1.0f);
    newObject(1.0f, -1.0f, 1.0f, 1.0f);
    newObject(-1.0f, 1.0f, 1.0f, 1.0f);
    newObject(1.0f, 1.0f, 1.0f, 1.0f);
}

int newObject(float xPos, float yPos, float xSize, float ySize){
    if(objList.objCount > MAX_OBJECTS) return 1;
    
    int i = objList.objCount;
    objList.xPos[i] = xPos;
    objList.yPos[i] = yPos;
    objList.xSize[i] = xSize;
    objList.ySize[i] = ySize;

    objList.objCount++;
}

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
    for (int i = 0; i < objList.objCount; i++){
        setModel(i);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

}