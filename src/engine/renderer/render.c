#include "render.h"
#include "root.h"
#include "shaders.h"
#include "shapes.h"

static void setSafeties(void);

typedef struct {
    unsigned int VAO;
    GLenum mode;
    unsigned int count;
    // DevNote: programID could be added later so that the objects track which shader program to use when rendering.
    // Could also have shaderPrograms keep track of their associated render objects.
} RenderObject;

// DevNote: Render objects are set to an array. Makes it easier to draw multiple objects in the render loop.
// Later on, an actual Render system can be implemented to manage these objects better.
#define MAX_RENDER_OBJECTS 10
static RenderObject* renderObjects[MAX_RENDER_OBJECTS];
static unsigned int renderObjectCount = 0;

// Resets bound buffers and vertex arrays to defaults to prevent accidental modification.
static void setSafeties(void){
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


void newRenderObject(const Shape* shape){
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

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

    RenderObject* obj = malloc(sizeof(RenderObject));
    obj->mode = GL_TRIANGLES;
    obj->count = shape->indicesCount;
    obj->VAO = VAO;
    renderObjects[renderObjectCount++] = obj;
    setSafeties();
}


static void setVertexArray(const Shape* shape){
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

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

    // DevNote: most of setShapeData is flexible enough to be used for different shapes and if there are textures,
    // BUT currently setting arrays and enabling attributes are hardcoded for position and color only.
    // Template for when I add more attributes like texture coordinates. Possibly use an enum or flags in Shape struct to indicate presence of certain attributes.
    // 
    // if(shape->HasTexture){
    //     // Set texture coordinates attribute pointer and enable it
    //     glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, shape->vertexSize * sizeof(float), (void*)(7 * sizeof(float)));
    //     glEnableVertexAttribArray(2);
    // }
    //
    // switch(shape->Enum/Flag){
    //     case ATTRIBUTE_TYPE_1:
    //         CallAttributeSetupFunction1();
    //         break;
    // }

    setSafeties();
}

// Should initialize any rendering data related to the plotting of elements to the screen. Not related to window creation or shader compilation.
int RendInit(void){
    
    setProgram();

    //setShapeData(&triangle);
    newRenderObject(GetShapeData(SHAPE_TRIANGLE));

    return 0;
}

// Handles initial steps of a render cycle.
void CleanCanvas(void){
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // Dark gray background as a placeholder
    glClear(GL_COLOR_BUFFER_BIT);
}

// Handles final steps of a render cycle.
void Serve(void){
    glfwSwapBuffers(mainWindow->window);
    glfwPollEvents();
}

// Main render function called each frame. Handles drawing all necessary elements to the screen.
void Render(void){
    for(unsigned int i = 0; i < renderObjectCount; i++){
        RenderObject* obj = renderObjects[i];
        setProgram();
        glBindVertexArray(obj->VAO);
        glDrawElements(obj->mode, obj->count, GL_UNSIGNED_INT, 0);
    }
}