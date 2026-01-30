#ifndef __DRAW_H__
#define __DRAW_H__

#include "bedrock/foundation.h"

typedef struct Render_t {
    unsigned int shaderID;
    GLFWwindow* window;
    unsigned int viewUniformLocation;
    unsigned int ssboTransforms;
    Mesh_t meshes[TOTAL_MESH_BASES];
} Render_t;

GLFWwindow* initRenderData(void);

void draw(Scene_t* scene);

void cleanup(void);

#endif