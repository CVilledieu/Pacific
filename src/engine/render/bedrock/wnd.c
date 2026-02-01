#include "foundation.h"
#include <stdlib.h>
#include "common/error.h"


// typedef struct ControlScheme_t {
//     int key;
//     void* funcPtr;
// } ControlScheme_t;

void callback_wndSize_Update(GLFWwindow* window, int width, int height){
    (void)window;
    glViewport(0, 0, width, height);
}

GLFWwindow* createWindow(void){
    if (!glfwInit()){
        return NULL;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif


    GLFWwindow* window = glfwCreateWindow(800, 600, "Pacific Engine", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        glfwDestroyWindow(window);
        glfwTerminate();
        return NULL;
    }

    glfwSetFramebufferSizeCallback(window, callback_wndSize_Update);
    return window;
}





