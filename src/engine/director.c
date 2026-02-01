/*
    Director:
        contains the central logic for game engine.


*/
#include "director.h"
#include "render/draw.h"
#include "scene/camera.h"
#include "scene/entities.h"
#include "subsystems/collision.h"
#include <stdlib.h>
#include <stdio.h>

Director_t director = {0};

void setControls(GLFWwindow* window);
Scene_t* createFirstScene(void);
Scene_t* createScene(void);



void setup(void){
    director.window = initRenderData();
    director.currentScene = createFirstScene();
    setControls(director.window);
}

void teardown(void){
    
    cleanup();
    #ifdef DEBUG_MODE
    printErrLog();
    #endif
}

void run(void){
    setup();
    AABBCollision(director.currentScene->allLists[0], 1, 0);
    while(!glfwWindowShouldClose(director.window)){
        draw(director.currentScene);  
        
    }  
    
    teardown();
}


Scene_t* createScene(void){
    Scene_t* newScene = malloc(sizeof(Scene_t));
    newScene->listCount = 0;
    newDefaultCamera(newScene->camera);
    
    return newScene;
}


Scene_t* createFirstScene(void){
    Scene_t* first = malloc(sizeof(Scene_t));
    first->listCount = 0;
    
    newDefaultCamera(first->camera);
    newEntityList(&first->allLists[SQUARE], SQUARE);
    first->listCount++;
    
    addEntity(first->allLists[SQUARE], 
        (Vec2){-0.5f, 0.2f}, (Vec2){1.0f, 0.9f}, (Vec2){0.00f, 0.00f}
    );
    addEntity(first->allLists[SQUARE], 
        (Vec2){0.3f, -0.9f}, (Vec2){0.8f, 0.8f}, (Vec2){0.00f, 0.00f}
    );
    return first;
}



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