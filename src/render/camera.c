#include "camera.h"

#include "glad/glad.h"
#include <glfw/glfw3.h>




static enum {
    SCALE_W = 0,
    SCALE_H = 5,
    MOVE_X = 12,
    MOVE_Y = 13,
} ViewIndex_e;

Camera_t camera = {0};

static void updateFOV(int index, float newValue);

Camera_t* initCamera(Vec2 initFOV){
    camera.fov[xCoord] = initFOV[xCoord],
    camera.fov[yCoord] = initFOV[yCoord],
    updateFOV(SCALE_H, camera.fov[yCoord]);
    updateFOV(SCALE_W, camera.fov[xCoord]);

    return &camera;
}


static float ViewMatrix[16] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
};

void setPerspective(unsigned int shaderPID){
    unsigned int uniformLoc = glGetUniformLocation(shaderPID, "uView");
    glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, ViewMatrix);
}


static void updateFOV(int index, float newValue){
    ViewMatrix[index] = newValue;
}



