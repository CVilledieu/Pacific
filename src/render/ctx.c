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
ViewCtx_t view = {0};

void initCtx(void){
    rCtx.PID = initShaders();
    rCtx.VAO = createPrimitive(PRIM_SQUARE);

    view.height = 0.2f;
    view.width = 0.2f;

    initObjects(view.width, view.height);

    initPerspective(&view);
}

void drawLoop(void){
    while(!glfwWindowShouldClose(mainWindow->window)){
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(rCtx.PID);
        glBindVertexArray(rCtx.VAO);

        setPerspective(rCtx.PID);

        drawModels();

        glBindVertexArray(0);

        glfwSwapBuffers(mainWindow->window);
        glfwPollEvents();
    }    
}

