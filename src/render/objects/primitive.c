#include "primitive.h"
#include <stdlib.h>


typedef struct {
    unsigned int vertexCount;
    unsigned int indexCount;

    unsigned int drawCount;
    unsigned int* drawOrder;

    float* vertices;
} VertexData;

static VertexData* getShapeData(ShapeType type){
    switch(type){
        case SHAPE_TRIANGLE:
            return (VertexData*)&Triangle_VD;
        case SHAPE_SQUARE:
            return (VertexData*)&Square_VD;
        default:
            return NULL;
    }
}


Primitive* newPrimitive(ShapeType shape){
    Primitive* prim = malloc(sizeof(Primitive));

    glGenVertexArrays(1, &prim->VAO);
    glGenBuffers(1, &prim->VBO);
    glGenBuffers(1, &prim->EBO);

    glBindVertexArray(prim->VAO);

    VertexData* data = getShapeData(shape);
    
    int bufferSize = data->vertexCount * data->indexCount * sizeof(float);
    glBindBuffer(GL_ARRAY_BUFFER, prim->VBO);
    glBufferData(GL_ARRAY_BUFFER, bufferSize, data->vertices, GL_STATIC_DRAW);

    int drawOrderSize = data->drawCount * sizeof(unsigned int);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, prim->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, drawOrderSize, data->drawOrder, GL_STATIC_DRAW);

    // DevNote: currently hard coding the number of indexes related to the different aspects of the array. 
    // Should update so number of indexes is uniform. Meaning all portions 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, data->indexCount * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, data->indexCount * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}



static const VertexData Square_VD = {
    .vertexCount = 4,
    .indexCount = 7,
    .drawCount = 6,
    .drawOrder = (unsigned int[]){0, 1, 2, 2, 3, 0},
    
    .vertices = (float[]){
        // positions            // colors
         0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f, 1.0f, 
         0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f, 1.0f, 
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f, 1.0f, 
        -0.5f,  0.5f, 0.0f,     1.0f, 1.0f, 0.0f, 1.0f   
    },
};

static const VertexData Triangle_VD = {
    .vertexCount = 3,
    .indexCount = 7,
    .drawCount = 3,
    .drawOrder = (unsigned int[]){0, 1, 2},
    .vertices = (float[]){
        // positions             // colors
         0.0f,  0.5f, 0.0f,      1.0f, 0.0f, 0.0f, 1.0f, 
        -0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f, 1.0f, 
         0.5f, -0.5f, 0.0f,      0.0f, 0.0f, 1.0f, 1.0f  
    }
};