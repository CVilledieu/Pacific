#include "director.h"
#include "atlas/entities.h"

#include "glad/glad.h"
#include <glfw/glfw3.h>

Atlas_t atlas = {0};


void initDirector(GLFWwindow* window){
    initEntities(&atlas);

}


void update(void){
    glfwPollEvents();
    moveEntities();


}

Atlas_t* getAtlas(void){
    return &atlas;
}
