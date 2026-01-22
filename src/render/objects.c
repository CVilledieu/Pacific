#include "objects.h"

void new_RenderObject(const Shape* shape){
    RenderObject* obj = malloc(sizeof(RenderObject));
    obj->mode = GL_TRIANGLES;

    unsigned int VBO, EBO;
    glGenVertexArrays(1, &obj->VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(obj->VAO);

    int bufferSize = shape->vertexCount * shape->vertexSize * sizeof(float);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, bufferSize, shape->vertices, GL_STATIC_DRAW); 

    int indicesSize = shape->indicesCount * sizeof(unsigned int);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, shape->indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, shape->vertexSize * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, shape->vertexSize * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    obj->count = shape->indicesCount;
    obj->VAO = VAO;
    renderObjects[renderObjectCount++] = obj;
}