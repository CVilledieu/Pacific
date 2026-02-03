#include "director.h"
#include "scene/entities.h"

#include "glad/glad.h"
#include <glfw/glfw3.h>



Catalog_t creatures = {0};
Catalog_t constructs = {0};

void setHero(void);

void initDirector(GLFWwindow* window){
    glfwSetKeyCallback(window, controlCallback);
    setHero();

}

void update(void){
    glfwPollEvents();
    moveEntities();


}


// Index zero of creatures is reserved / occupide by the player controlled unit aka the Hero unit
void setHero(void){
    creatures.x[0] = DEFAULT_HERO_X;
    creatures.y[0] = DEFAULT_HERO_Y;
    creatures.width[0] = DEFAULT_HERO_W;
    creatures.height[0] = DEFAULT_HERO_H;
    creatures.count = 1;
}

void newCreature(Object_t obj){
    if (creatures.count >= MAX_MODEL_COUNT) return;

    int id = creatures->count;
    creatures->x[id] = pos[X];
    creatures->y[id] = pos[Y];

    creatures->width[id] = size[X];
    creatures->height[id] = size[Y];

    creatures->dX[id] = speed[X];
    creatures->dY[id] = speed[Y];

    creatures->count++;
}