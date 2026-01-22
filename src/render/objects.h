#ifndef __RENDER_OBJECTS_H__
#define __RENDER_OBJECTS_H__

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include 

typedef struct RenderObject {
    unsigned int VAO;
    GLenum mode;
    unsigned int count;
} RenderObject;

#endif