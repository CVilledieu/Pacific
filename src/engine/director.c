/*
    Director:
        contains the central logic for game engine.


*/
#include "director.h"
#include "render/draw.h"
#include "scene/camera.h"
#include "scene/entities.h"

#include <stdlib.h>

#define W(x) ((float)(x) * 0.01f)  // World coordinate


Director_t director = {0};


Scene_t* createFirstScene(void){
    Scene_t* first = malloc(sizeof(Scene_t));
    first->listCount = 0;
    
    newDefaultCamera(first->camera);
    newEntityList(&first->allLists[SQUARE], SQUARE);
    first->listCount++;
    
    addEntity(first->allLists[SQUARE], 
        (Vec2){-0.5f, -0.2f}, (Vec2){1.0f, 0.9f}, (Vec2){0.00f, 0.00f}
    );
    addEntity(first->allLists[SQUARE], 
        (Vec2){0.3f, 0.5f}, (Vec2){0.8f, 0.8f}, (Vec2){0.00f, 0.00f}
    );
    return first;
}

Scene_t* createScene(void){
    Scene_t* newScene = malloc(sizeof(Scene_t));
    newScene->listCount = 0;
    newDefaultCamera(newScene->camera);

    return newScene;
}


void setup(void){
    director.window = initRenderData();
    director.currentScene = createFirstScene();
}

void teardown(void){

    cleanup();
    #ifdef DEBUG_MODE
        printErrLog();
    #endif
}

void run(void){
    setup();

    while(!glfwWindowShouldClose(director.window)){
        draw(director.currentScene);  
    }  

    teardown();
}