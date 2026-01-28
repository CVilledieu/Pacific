#include "render/draw.h"
#include "common/error.h"
#include "window/wnd.h"

RenderCtx_t rCtx = {
    .bgColor = (Vec4){0.2f, 0.2f, 0.2f, 1.0f},
};

void initCtx(void){
    if (createWindow()){
        exit(-1);
    }
    initShaders();
    rCtx.VAO = createPrimitive(PRIM_SQUARE);

    Vec2 initFOV = {0.09f, 0.09f}; 
    initCamera(initFOV);
    initScene(initFOV);
}

int main(void){
    initCtx();
    
    glUseProgram(rCtx.PID);
    
    while(!glfwWindowShouldClose(mainWindow->window)){
        glClearColor(
            rCtx.bgColor[0], 
            rCtx.bgColor[1], 
            rCtx.bgColor[2], 
            rCtx.bgColor[3]
        );
        glClear(GL_COLOR_BUFFER_BIT);
        
        glBindVertexArray(rCtx.VAO);

        setPerspective();
        
        drawScene();
        
        glBindVertexArray(0);

        glfwSwapBuffers(mainWindow->window);
        glfwPollEvents();
    }    

    closeWindow();
}