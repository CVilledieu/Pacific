#ifndef __PRIMITIVES_SHADERS_H__
#define __PRIMITIVES_SHADERS_H__

#include "glad/glad.h"
#include <GLFW/glfw3.h>

// typedef struct {
//     unsigned int id;
//     int uCount;
//     // char** fNames;
//     char** uNames;
//     unsigned int uLocs[];
// } Shader_t;

void initShaders(void);
void setProgramID(void);
unsigned int getUniformLoc(char* name);

#endif