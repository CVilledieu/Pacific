#ifndef __DIRECTOR_H__
#define __DIRECTOR_H__

#include "common/types.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>

typedef struct Director_t{
    GLFWwindow* window;
    Scene_t* currentScene;
} Director_t;



void setup(void);
void teardown(void);


void run(void);

#endif