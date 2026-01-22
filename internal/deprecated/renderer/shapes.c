#include "shapes.h"
#include <stdlib.h>

static const Shape triangle = {
    .vertexCount = 3,
    .vertexSize = 7,
    .indicesCount = 3,
    .indices = (unsigned int[]){0, 1, 2},
    .vertices = (float[]){
        // positions             // colors
         0.0f,  0.5f, 0.0f,      1.0f, 0.0f, 0.0f, 1.0f, 
        -0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f, 1.0f, 
         0.5f, -0.5f, 0.0f,      0.0f, 0.0f, 1.0f, 1.0f  
    }
};

static const Shape square = {
    .vertexCount = 4,
    .vertexSize = 7,
    .indicesCount = 6,
    .indices = (unsigned int[]){0, 1, 2, 2, 3, 0},
    .vertices = (float[]){
        // positions            // colors
         0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f, 1.0f, 
         0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f, 1.0f, 
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f, 1.0f, 
        -0.5f,  0.5f, 0.0f,     1.0f, 1.0f, 0.0f, 1.0f   
    }
};

Shape* GetShapeData(ShapeType type){
    switch(type){
        case SHAPE_TRIANGLE:
            return (Shape*)&triangle;
        case SHAPE_SQUARE:
            return (Shape*)&square;
        default:
            return NULL;
    }
}