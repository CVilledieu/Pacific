#include "draw.h"
#include "bedrock/foundation.h"

#include "engine/types.h"

static GLFWwindow* window = NULL;

static unsigned int uView = 0;
static Mesh_t mesh = {0};


GLFWwindow* initRenderData(void){
    window = createWindow();
    initShader();
    uView = getUniformAddress();

    createMesh(&mesh);
    return window;
}


static inline void buildModelMatrix(float* dest, float x, float y, float z, float sx, float sy, float sz, float rotX, float rotY, float rotZ){
    (void)rotX; (void)rotY; (void)rotZ;  // Suppress unused warnings
    
    // Column-major mat4: scale then translate
    // | sx  0   0   tx |
    // | 0   sy  0   ty |
    // | 0   0   sz  tz |
    // | 0   0   0   1  |
    dest[0]  = sx;   dest[1]  = 0.0f; dest[2]  = 0.0f; dest[3]  = 0.0f; 
    dest[4]  = 0.0f; dest[5]  = sy;   dest[6]  = 0.0f; dest[7]  = 0.0f; 
    dest[8]  = 0.0f; dest[9]  = 0.0f; dest[10] = sz;   dest[11] = 0.0f; 
    dest[12] = x;    dest[13] = y;    dest[14] = z;    dest[15] = 1.0f; 
}

// Pack all entity transforms into SSBO as mat4 model matrices
static void packEntityMatrices(float* buffer, Entities_t* entities, int startIndex){
    const int count = entities->count;
    for (int i = 0; i < count; i++){
        float* mat = buffer + (startIndex + i) * FLOATS_PER_INSTANCE;
        buildModelMatrix(mat, entities->x[i], entities->y[i], entities->z[i], entities->width[i], entities->height[i], entities->length[i], 0.0f, 0.0f, 0.0f);  
    }
}

static void drawECS(Entities_t* creatures, Entities_t* constructs){

    const int creatureCount = creatures->count;
    const int constructsCount = constructs->count;

    glBindVertexArray(mesh.VO);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, mesh.ssbo);
    
    float* buffer = glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, TRANSFORM_BUFFER_SIZE, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

    if (!buffer){
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
        return;
    }

    packEntityMatrices(buffer, creatures, 0);
    packEntityMatrices(buffer, constructs, creatureCount);

    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    glDrawElementsInstanced(GL_TRIANGLES, mesh.indices, GL_UNSIGNED_INT, 0, (creatureCount + constructsCount));
}



void draw(ECS_t* ecs, Mat4 camera){
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glUniformMatrix4fv(uView, 1, GL_FALSE, camera);
    drawECS(&ecs->creatures, &ecs->constructs);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

