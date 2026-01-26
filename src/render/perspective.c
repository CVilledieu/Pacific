#include "perspective.h"


#include "glad/glad.h"
#include <glfw/glfw3.h>

static float ViewMatrix[16] = {
    0.2f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.2f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
};


void setViewTransformation(unsigned int shaderPID){
    unsigned int uniformLoc = glGetUniformLocation(shaderPID, "uView");
    glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, ViewMatrix);
}
