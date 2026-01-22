#ifndef __OBJECTS_PRIMITIVE_H
#define __OBJECTS_PRIMITIVE_H

#include <glad/glad.h>

typedef enum {
    SHAPE_SQUARE,
    SHAPE_TRIANGLE,
} ShapeType;

typedef struct {
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    unsigned int vertexCount;
    unsigned int indicesCount;
    GLenum mode;
    ShapeType type;
} Primitive;


#endif
