#ifndef __FOUNDATION_H__
#define __FOUNDATION_H__

#include "GLAD/glad.h"
#include <GLFW/glfw3.h>

#include "engine/types.h"
// Window
// =========
GLFWwindow* createWindow(void);


// Vertex Object
// =============

typedef struct Mesh_t{
    unsigned int VO;
    unsigned int indices;
} Mesh_t;

void createMeshes(Mesh_t* meshes);
unsigned int createTransformSSBO(void);

// Shaders function
// ===============

unsigned int createShaders(void);

//Possible shader type
typedef enum {
    uVIEW,
    TOTAL_UNIFORMS,
} Uniforms;

typedef struct Shader_t{
    unsigned int pid;
    unsigned int uLocs[TOTAL_UNIFORMS];
    char* uNames[TOTAL_UNIFORMS];
} Shader_t;


#endif