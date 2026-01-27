#include "camera.h"

#include "glad/glad.h"
#include <glfw/glfw3.h>


static enum {
    SCALE_W = 0,
    SCALE_H = 5,
    MOVE_X = 12,
    MOVE_Y = 13,
} ViewIndex_e;

Camera_t camera = {
    .bgColor = (Vec4){0.2f, 0.2f, 0.2f, 1.0f},
};

static void updateFOV(int index, float newValue);

Camera_t* initCamera(Vec2 initFOV){
    camera.fov[X] = initFOV[X],
    camera.fov[Y] = initFOV[Y],
    updateFOV(SCALE_H, camera.fov[Y]);
    updateFOV(SCALE_W, camera.fov[X]);
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
