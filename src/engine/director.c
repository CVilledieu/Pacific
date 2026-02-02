/*
    Director:
        contains the central logic for game engine.


*/
#include "director.h"
#include "render/draw.h"
#include "ecs/entities.h"
#include "types.h"
#include <stdlib.h>
#include <stdio.h>

static GLFWwindow* window = NULL;
static Vec2 camera;
static ECS_t ecs;


void teardown(void){
    if (window) {
        glfwDestroyWindow(window);
    }
    

    #ifdef DEBUG_MODE
        printErrLog();
    #endif
    glfwTerminate();
}

void run(void){
    while(!glfwWindowShouldClose(window)){
        draw(&ecs);
        
    }  
    
    teardown();
}

void setup(void){
    window = initRenderData();

    if (!window) {
        printf("ERROR: Failed to create window\n");
        return;
    }
    // setControls(window);
    initECS(&ecs);


    run();
}




