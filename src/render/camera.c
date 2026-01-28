#include "camera.h"
#include "primitives/shaders.h"
#include "glad/glad.h"
#include <glfw/glfw3.h>


static enum {
    SCALE_W = 0,
    SCALE_H = 5,
    MOVE_X = 12,
    MOVE_Y = 13,
} ViewIndex;

#define uniformName "uView"

static Vec2 fov;
static unsigned int uniformLoc = 0;

static void updateFOV(int index, float newValue);

void initCamera(Vec2 initFOV){
    fov[X] = initFOV[X],
    fov[Y] = initFOV[Y],
    uniformLoc = getUniformLoc(uniformName);
    updateFOV(SCALE_H, fov[Y]);
    updateFOV(SCALE_W, fov[X]);
}

static float ViewMatrix[16] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
};

void setPerspective(void){
    glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, ViewMatrix);
}


static void updateFOV(int index, float newValue){
    ViewMatrix[index] = newValue;
}
