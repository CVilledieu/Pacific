#include "control.h"


void controlCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (action != GLFW_PRESS) 
        return;
    switch (key){
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            break;
        case GLFW_KEY_W:
        case GLFW_KEY_A:
        case GLFW_KEY_D:
        case GLFW_KEY_S:
        case GLFW_KEY_F:
        case GLFW_KEY_SPACE:
            break;
    }
}


void setControls(GLFWwindow* window){
    glfwSetKeyCallback(window, controlCallback);
}