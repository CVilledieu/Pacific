// ATTN: Comments prefixed with 'DevNotes' are notes for future development and improvements and are intended to be temporary. They are intended for the developer's reference and may be removed in future versions.
// All other comments will be aimed as documentation for anyone else. 

// Root should only act as a coordinator or manager of the engine's subsystems. 
// Root should not contain any logic for how the engine actually works, but should instead call the appropriate functions in the appropriate order to initialize, run, and terminate the engine.

// Std C headers
#include <stdlib.h>

// Dependency headers
#include "GLAD/glad.h"
#include <GLFW/glfw3.h>

// Project headers
#include "root.h"
#include "win/window.h"
#include "renderer/render.h"
#include "renderer/shaders.h"

// Calls subsystem initialization functions in correct order. Since the engine is intended to be simply a state machine, there is nothing for the engine itself to initialize.
void InitEngine(void){
    // DevNote: More robust error handling should be implemented. Consider logging system and exiting with error codes instead of just returning from the function. At the moment, if a subsystem fails I am just returning to end up exiting the program anyway.
    if (WndInit()) {
        return;
    }

    ShaderInit();
    if (RendInit()) {
        return;
    }
    
}

void RunEngine(void){
    while(!glfwWindowShouldClose(mainWindow->window)){
        CleanCanvas();
        Render();
        Serve();
    }
}


// Currently only calls window termination, but will eventually be updated
// Calls all subsystems' termination/cleanup functions
void TerminateEngine(void){
    CloseWindow();
    TerminateShaders();
    
}