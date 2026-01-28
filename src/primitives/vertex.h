#ifndef __PRIMITIVES_VERTEX_H__
#define __PRIMITIVES_VERTEX_H__

#include "glad/glad.h"
#include <glfw/glfw3.h>


typedef enum {
    PRIM_SQUARE,
    PRIM_CIRCLE,
} PrimType;

unsigned int createPrimitive(PrimType type);
void deleteBufferObjects(void);


#endif