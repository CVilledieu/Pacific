#include "glad/glad.h"
#include <glfw/glfw3.h>

#include "ctx.h"
#include "perspective.h"
#include "models.h"

#include "primitives/shaders.h"
#include "primitives/vertex.h"
#include "window/wnd.h"

#include <stdio.h>

RenderCtx_t rCtx = {0};


void initCtx(void){
    rCtx.PID = initShaders();
    rCtx.VAO = createPrimitive(PRIM_SQUARE);
    initObjectList();
}





void drawLoop(void){
    while(!glfwWindowShouldClose(mainWindow->window)){
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(rCtx.PID);
        glBindVertexArray(rCtx.VAO);

        setViewTransformation(rCtx.PID);

        drawModels();

        glBindVertexArray(0);

        glfwSwapBuffers(mainWindow->window);
        glfwPollEvents();
    }    
}



