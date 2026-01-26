#include "perspective.h"

#include "glad/glad.h"
#include <glfw/glfw3.h>

#define WIDTH_INDEX 0
#define HEIGHT_INDEX 5

static void updateScaling(int index, float newValue);

static float ViewMatrix[16] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
};


void initPerspective(ViewCtx_t* view){
    updateScaling(HEIGHT_INDEX, view->height);
    updateScaling(WIDTH_INDEX, view->width);
}


void setPerspective(unsigned int shaderPID){
    unsigned int uniformLoc = glGetUniformLocation(shaderPID, "uView");
    glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, ViewMatrix);
}


void updateScaling(int index, float newValue){
    ViewMatrix[index] = newValue;
}
