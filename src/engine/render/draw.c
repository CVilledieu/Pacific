#include "draw.h"
#include "bedrock/foundation.h"

#include "engine/types.h"

static GLFWwindow* window = NULL;

static unsigned int uView = 0;
static Mesh_t mesh = {0};

static float defaultCamera[16] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
};


GLFWwindow* initRenderData(void){
    window = createWindow();
    initShader();
    uView = getUniformAddress();

    createMesh(&mesh);
    return window;
}


static inline void setCameraData(void){
    glUniformMatrix4fv(uView, 1, GL_FALSE, defaultCamera);
}

static void loadBuffer(int offset, int size, float* dest, float* src){
    for(int i = 0; i < size; i++){
        dest[4*i + offset] = src[i];
    }
}

static void drawEntities(Entities_t* creatures, Entities_t* constructs){

    const int creatureCount = creatures->count;
    const int constructsCount = constructs->count;

    glBindVertexArray(mesh.VO);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, mesh.ssbo);
    
    float* buffer = glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, TRANSFORM_BUFFER_SIZE, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

    if (!buffer){
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
        return;
    }

    loadBuffer(0, creatureCount, buffer, creatures->x);
    loadBuffer(1, creatureCount, buffer, creatures->y);
    loadBuffer(2, creatureCount, buffer, creatures->width);
    loadBuffer(3, creatureCount, buffer, creatures->height);

    float* conBuffer = buffer + (creatureCount * 4);
    loadBuffer(0, constructsCount, conBuffer, constructs->x);
    loadBuffer(1, constructsCount, conBuffer, constructs->y);
    loadBuffer(2, constructsCount, conBuffer, constructs->width);
    loadBuffer(3, constructsCount, conBuffer, constructs->height);

    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    glDrawElementsInstanced(GL_TRIANGLES, mesh.indices, GL_UNSIGNED_INT, 0, (creatureCount + constructsCount));
}



void draw(ECS_t* ecs){
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    setCameraData();
    drawEntities(&ecs->creatures, &ecs->constructs);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

