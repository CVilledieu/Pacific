#include "foundation.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static void createVO(Mesh_t* mesh){
    unsigned int VBO, EBO;
    glGenVertexArrays(1, &mesh->VO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(mesh->VO);
    
    float vertices[] = {
        // Front face (Z+) - white
        -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
        // Back face (Z-) - light gray
        -0.5f, -0.5f, -0.5f,  0.8f, 0.8f, 0.8f,
        -0.5f,  0.5f, -0.5f,  0.8f, 0.8f, 0.8f,
         0.5f,  0.5f, -0.5f,  0.8f, 0.8f, 0.8f,
         0.5f, -0.5f, -0.5f,  0.8f, 0.8f, 0.8f,
        // Top face (Y+) - light blue
        -0.5f,  0.5f, -0.5f,  0.7f, 0.7f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.7f, 0.7f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.7f, 0.7f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.7f, 0.7f, 1.0f,
        // Bottom face (Y-) - dark gray
        -0.5f, -0.5f, -0.5f,  0.5f, 0.5f, 0.5f,
         0.5f, -0.5f, -0.5f,  0.5f, 0.5f, 0.5f,
         0.5f, -0.5f,  0.5f,  0.5f, 0.5f, 0.5f,
        -0.5f, -0.5f,  0.5f,  0.5f, 0.5f, 0.5f,
        // Right face (X+) - light green
         0.5f, -0.5f, -0.5f,  0.7f, 1.0f, 0.7f,
         0.5f,  0.5f, -0.5f,  0.7f, 1.0f, 0.7f,
         0.5f,  0.5f,  0.5f,  0.7f, 1.0f, 0.7f,
         0.5f, -0.5f,  0.5f,  0.7f, 1.0f, 0.7f,
        // Left face (X-) - light red
        -0.5f, -0.5f, -0.5f,  1.0f, 0.7f, 0.7f,
        -0.5f, -0.5f,  0.5f,  1.0f, 0.7f, 0.7f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.7f, 0.7f,
        -0.5f,  0.5f, -0.5f,  1.0f, 0.7f, 0.7f,
    };

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int drawOrder[] = {
        0,  1,  2,   2,  3,  0,   // Front
        4,  5,  6,   6,  7,  4,   // Back
        8,  9,  10,  10, 11, 8,   // Top
        12, 13, 14,  14, 15, 12,  // Bottom
        16, 17, 18,  18, 19, 16,  // Right
        20, 21, 22,  22, 23, 20,  // Left
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

void createSSBO(Mesh_t* mesh){
    glGenBuffers(1, &mesh->ssbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, mesh->ssbo);
    glBufferData(GL_SHADER_STORAGE_BUFFER, 
                 TRANSFORM_BUFFER_SIZE, 
                 NULL, 
                 GL_DYNAMIC_DRAW);
    // Bind to binding point 0 (matches shader layout)
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, mesh->ssbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void createMesh(Mesh_t* mesh){
    createVO(mesh);
    createSSBO(mesh);
}