#include "draw.h"
#include "bedrock/foundation.h"

#include "engine/common/types.h"

typedef enum {
    dW = 0,
    dH = 5,
    dL = 10,
    dX = 12,
    dY = 13,
} MatMap;

static Render_t driver = {0};

GLFWwindow* initRenderData(void){
    driver.window = createWindow();
    driver.shaderID = createShaders();
    createMeshes(driver.meshes);
    driver.ssboTransforms = createTransformSSBO();
    driver.viewUniformLocation = glGetUniformLocation(driver.shaderID, "uView");

    // Nothing should remove Program, so at the moment its safe to call before rendering process.
    // Also saves processing to call once before rendering instead of each render call
    glUseProgram(driver.shaderID); 

    return driver.window;
}



static inline void updateMapBuffer(int offset, int count, float* dest, float* source){
    for (int i = 0; i < count; i++){
        dest[i * 4 + offset] = source[i];
    }
}

static void drawEntityList(EntityList_t* cast){
    if (cast->count == 0) return;
    Mesh_t mesh = driver.meshes[cast->baseType];
    glBindVertexArray(mesh.VO);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, driver.ssboTransforms);
    
    float* mapBuffer = (float*)glMapBufferRange(
        GL_SHADER_STORAGE_BUFFER,
        0,
        cast->count * 4 * sizeof(float),
        GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT
    );
    
    if (!mapBuffer) {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
        return;
    }
    
    const int count = cast->count;

    updateMapBuffer(0, count, mapBuffer, cast->x);
    updateMapBuffer(1, count, mapBuffer, cast->y);
    updateMapBuffer(2, count, mapBuffer, cast->width);
    updateMapBuffer(3, count, mapBuffer, cast->height);
    
    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    glDrawElementsInstanced(GL_TRIANGLES, mesh.indices, GL_UNSIGNED_INT, 0, cast->count);
}

// Place holder until multiple meshes are going to be drawn at the sametime. 
// At that time this will be expanded on.
void drawEntities(EntityList_t** allLists, int size){
    for (int i = 0; i < size; i++){
        drawEntityList(allLists[i]);
    }
}

void draw(Scene_t* scene){
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // Only one Vertex array at the moment, so no need to unbind and rebind. Current binding will be set right before draw
    // glBindVertexArray(driver.mesh); 
    glUniformMatrix4fv(driver.viewUniformLocation, 1, GL_FALSE, scene->camera);
    drawEntities(scene->allLists, scene->listCount);

    // glBindVertexArray(0);
    glfwSwapBuffers(driver.window);
    glfwPollEvents();
}

void cleanup(void){
    if (driver.window) {
        glfwDestroyWindow(driver.window);
    }
    
    glfwTerminate();
}