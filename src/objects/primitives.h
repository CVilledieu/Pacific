#ifndef __PRIMITIVE_H__
#define __PRIMITIVE_H__

#include "glad/glad.h"
#include <glfw/glfw3.h>


typedef enum {
    PRIM_SQUARE,
    PRIM_TRIANGLE,
} primType;

unsigned int createPrimitive(primType type);
void deleteBufferObjects(void);


#endif