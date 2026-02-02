#ifndef __FOUNDATION_H__
#define __FOUNDATION_H__

#include "GLAD/glad.h"
#include <GLFW/glfw3.h>

#include "engine/types.h"


#define TRANSFORM_BUFFER_SIZE (MAX_MODEL_COUNT * 4 * sizeof(float))

// Window
// =========
GLFWwindow* createWindow(void);


// Vertex Object
// =============

typedef struct Mesh_t{
    unsigned int VO;
    unsigned int indices;
    unsigned int ssbo;
} Mesh_t;

void createMesh(Mesh_t* mesh);


// Shaders function
// ===============

void initShader(void);
unsigned int getUniformAddress(void);

#endif