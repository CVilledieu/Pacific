#include "control.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

const float unit = 0.06f;



// void checkInput(GLFWwindow* window){
//     glfwGetKey()
// }



static void released(int key){
        switch (key){
        case GLFW_KEY_W:
            setYVelocity(0, 0);
            break;
        case GLFW_KEY_A:
            setXVelocity(0, 0);
            break;
        case GLFW_KEY_D:
            setXVelocity(0, 0);
            break;
        case GLFW_KEY_S:
            setYVelocity(0, 0);
            break;
        case GLFW_KEY_F:
        case GLFW_KEY_SPACE:
            break;
    }
}

static void pressed(GLFWwindow* window, int key){
    switch (key){
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            break;
        case GLFW_KEY_W:
            setYVelocity(0, unit);
            break;
        case GLFW_KEY_A:
            setXVelocity(0, -unit);
            break;
        case GLFW_KEY_D:
            setXVelocity(0, unit);
            break;
        case GLFW_KEY_S:
            setYVelocity(0, -unit);
            break;
        case GLFW_KEY_F:
        case GLFW_KEY_SPACE:
            break;
    }
}

void controlCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (action == GLFW_PRESS || action == GLFW_REPEAT){
        pressed(window, key);
    } else if (action == GLFW_RELEASE) {
        released(key);
    }
}

