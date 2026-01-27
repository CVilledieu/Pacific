#include "vertex.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static unsigned int VBO, EBO;

unsigned int createSquare_VAO(void){
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    
    float vertices[] = {
        -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, // Top Left
        -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom Left
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, // Top Right
         0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom Right
    };

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int drawOrder[] = {
        0, 1, 2, 
        3, 2, 1,
    };
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(drawOrder), drawOrder, GL_STATIC_DRAW);
    
    int stride = 6 * sizeof(float);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    return VAO;
}

unsigned int createCircle_VAO(void){
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    

    float vertices[] = {
         0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Center

        -0.8f, 0.3f, 0.0f, 1.0f, 1.0f, 1.0f, 
        -0.3f, 0.8f, 0.0f, 1.0f, 1.0f, 1.0f, 

         0.3f, 0.8f, 0.0f, 1.0f, 1.0f, 1.0f,
         0.8f, 0.3f, 0.0f, 1.0f, 1.0f, 1.0f,
        
         0.8f, -0.3f, 0.0f, 1.0f, 1.0f, 1.0f,
         0.3f, -0.8f, 0.0f, 1.0f, 1.0f, 1.0f,
         
        -0.3f, -0.8f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.8f, -0.3f, 0.0f, 1.0f, 1.0f, 1.0f,

    };

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int drawOrder[] = {
        0, 1, 2, 
        0, 2, 3,
        0, 3, 4,
        0, 4, 5,
        0, 5, 6,
        0, 6, 7,
        0, 7, 8,
        0, 8, 1,
    };
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(drawOrder), drawOrder, GL_STATIC_DRAW);
    
    int stride = 6 * sizeof(float);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    return VAO;
}

unsigned int createPrimitive(primType type){
    switch(type){
        case PRIM_SQUARE:
            return createSquare_VAO();
        case PRIM_CIRCLE:
            return createCircle_VAO();
        default:
            return 0;
    }
    
}

void deleteBufferObjects(void){
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

