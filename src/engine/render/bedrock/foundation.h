#ifndef __FOUNDATION_H__
#define __FOUNDATION_H__

#include "GLAD/glad.h"
#include <GLFW/glfw3.h>

#include "engine/types.h"


// Each instance stores a full mat4 model matrix (16 floats, computed on CPU)
#define FLOATS_PER_INSTANCE 16
#define TRANSFORM_BUFFER_SIZE (MAX_MODEL_COUNT * FLOATS_PER_INSTANCE * sizeof(float))

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