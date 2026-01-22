#include "new.h"
#include <stdlib.h>

Wnd* mainWindow;

void setCallbacks(void);

int WndInit(void){
    if (!glfwInit()){
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    mainWindow = malloc(sizeof(Wnd));
    mainWindow->window = glfwCreateWindow(800, 600, "IslandTap Engine", NULL, NULL);
    if (!mainWindow->window) {
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(mainWindow->window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        glfwDestroyWindow(mainWindow->window);
        glfwTerminate();
        return 1;
    }

    setCallbacks(); // Sets input and window_Resize callbacks
    return 0;
}

// Currently listening for:
// - ESC key to close the window
void callback_key(GLFWwindow* window, int key, int scancode, int action, int mods){
    (void)scancode;
    (void)mods;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void callback_wndSize_Update(GLFWwindow* window, int width, int height){
    (void)window;
    mainWindow->width = width;
    mainWindow->height = height;
    glViewport(0, 0, width, height);
}

void setCallbacks(void){
    glfwSetKeyCallback(mainWindow->window, callback_key);
    glfwSetFramebufferSizeCallback(mainWindow->window, callback_wndSize_Update);
}

void CloseWindow(void){
    if (mainWindow->window) {
        glfwDestroyWindow(mainWindow->window);
    }
    glfwTerminate();
}

