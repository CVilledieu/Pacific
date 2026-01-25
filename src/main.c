#include "window/wnd.h"
#include "render/ctx.h"
#include <stdlib.h>


int main(void){

    if (createWindow()){
        return -1;
    }


    GLFWwindow* window = mainWindow->window;

    initCtx();
    
    while(!glfwWindowShouldClose(window)){
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        drawList();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }    

    closeWindow();

    // printErrLog();
}