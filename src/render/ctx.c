#include "ctx.h"
#include "objects/models.h"
#include "objects/primitives.h"
#include "shaders.h"


// DevNote: The way renderList and models rely on eachother makes splitting them feel awkward
// Possibly keep list of models within model.c and only keep a model count in ctx

static RenderList_t RenderList = {0};
static unsigned int shaderPID = 0;
static unsigned int VAO = 0;

static float ViewMatrix[16] = {
    .3f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.3f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
};
void initRenderList(void);


void initCtx(void){
    shaderPID = initShaders();
    VAO = createPrimitive(PRIM_SQUARE);
    initRenderList();
}


// DevNote: At the moment sets specific object data. Will createa more dynamic way to create the objects
void initRenderList(void){
    newObject(&RenderList, (float[]){1.0f, 1.0f}, (float[]){1.0f, 1.0f});
    newObject(&RenderList, (float[]){1.2f, 2.0f}, (float[]){0.5f, 0.5f});
    newObject(&RenderList, (float[]){-1.2f, 2.0f}, (float[]){1.0f, 1.0f});
    // return &RenderList;
}


void setViewTransformation(void){
    unsigned int uniformLoc = glGetUniformLocation(shaderPID, "uView");
    glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, ViewMatrix);
}


void setModel(int index){
    float mat4[16] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
    };
    mat4[0] = RenderList.xSize[index];
    mat4[5] = RenderList.ySize[index];

    mat4[12] = RenderList.xPos[index];
    mat4[13] = RenderList.yPos[index];

    unsigned int uniformLoc = glGetUniformLocation(shaderPID, "uModel");
    glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, mat4);
}

void drawList(void){
    glUseProgram(shaderPID);
    setViewTransformation();
    for (int i = 0; i < RenderList.objectCount; i++){
        setModel(i);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

}





