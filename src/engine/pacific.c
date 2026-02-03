#include "pacific.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "renderer.h"
#include "director.h"

static GLFWwindow* window = NULL;

void teardown(void);

void init(void){
    window = initRenderData();
}

void mainLoop(void){
    while(!glfwWindowShouldClose(window)){
        update();
        draw();
    }

    teardown();
}

void teardown(void){
    if (window) {
        glfwDestroyWindow(window);
    }
    

    #ifdef DEBUG_MODE
        printErrLog();
    #endif
    glfwTerminate();
}