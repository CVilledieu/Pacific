#ifndef __ENGINE_SHAPES_H__
#define __ENGINE_SHAPES_H__

// DevNote: setting up basic rendering functionality. Will likely refactor and expand upon this later as needed.
// Hardcoding data for some simple shapes for now.
// May not need to implement more complex systems, because engine is intended to be simple and 2D.
// Basic shapes may be sufficient for most purposes with detail added via textures later.
typedef struct {
    unsigned int vertexCount;
    unsigned int vertexSize; // indices per vertex
    unsigned int indicesCount;
    
    unsigned int* indices;
    float* vertices;
} Shape;

typedef enum ShapeType {
    SHAPE_TRIANGLE,
    SHAPE_SQUARE,
    // DevNote: Add more shapes as needed
} ShapeType;

Shape* GetShapeData(ShapeType type);

#endif