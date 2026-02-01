#include "foundation.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static void squareMesh(Mesh_t* mesh){
    unsigned int VBO, EBO;
    glGenVertexArrays(1, &mesh->VO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(mesh->VO);
    
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

    mesh->indices = (sizeof(drawOrder) / sizeof(unsigned int));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(drawOrder), drawOrder, GL_STATIC_DRAW);
    
    int stride = 6 * sizeof(float);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

static void circleMesh(Mesh_t* mesh){
    unsigned int VBO, EBO;
    glGenVertexArrays(1, &mesh->VO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(mesh->VO);
    

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
    mesh->indices = (sizeof(drawOrder) / sizeof(unsigned int));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(drawOrder), drawOrder, GL_STATIC_DRAW);
    
    int stride = 6 * sizeof(float);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void createMeshes(Mesh_t* meshes){
    squareMesh(&meshes[SQUARE]);
    circleMesh(&meshes[CIRCLE]);
    
}

void cleanUpMeshes(Mesh_t* meshes){
    for (int i = 0; i < TOTAL_MESH_BASES; i++){
        glDeleteVertexArrays(1, &meshes[i].VO);
    }
}


unsigned int createTransformSSBO(void){
    unsigned int ssbo;
    glGenBuffers(1, &ssbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    glBufferData(GL_SHADER_STORAGE_BUFFER, 
                 MAX_MODEL_COUNT * 4 * sizeof(float), 
                 NULL, 
                 GL_DYNAMIC_DRAW);
    // Bind to binding point 0 (matches shader layout)
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    return ssbo;
}

