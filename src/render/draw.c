// Main Ctx for the engine
// will likely switch names of: `render/ -> context/` 


#include "glad/glad.h"
#include <glfw/glfw3.h>

#include "draw.h"
#include "camera.h"
#include "scene.h"

#include "primitives/shaders.h"
#include "primitives/vertex.h"
#include "window/wnd.h"

#include <stdio.h>

RenderCtx_t rCtx = {0};


void initCtx(void){
    rCtx.PID = initShaders();
    rCtx.VAO = createPrimitive(PRIM_SQUARE);

    // DevNote: Passing initial fov to camera for 2 reasons. 
    // Later, I can have the initial FOV as a parameter for initCtx. Allowing more customizablity
    // Also feels smoother pass the same Vec to both camera and scene rather than passing scene a property of camera
    Vec2 initFOV = {0.09f, 0.09f}; 
    rCtx.camera = initCamera(initFOV);

    initScene(initFOV);
}

void drawStep(void){
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glUseProgram(rCtx.PID);
    glBindVertexArray(rCtx.VAO);

    setPerspective(rCtx.PID);

    drawScene();

    glBindVertexArray(0);

    glfwSwapBuffers(mainWindow->window);
    glfwPollEvents();
}

void draw(void){
    while(!glfwWindowShouldClose(mainWindow->window)){
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(rCtx.PID);
        glBindVertexArray(rCtx.VAO);

        setPerspective(rCtx.PID);
        
        drawScene();
        
        glBindVertexArray(0);

        glfwSwapBuffers(mainWindow->window);
        glfwPollEvents();
    }    
}



