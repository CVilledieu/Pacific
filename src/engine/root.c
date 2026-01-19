
#include "GLAD/glad.h"
#include <GLFW/glfw3.h>

typedef struct Wnd {
    int width;
    int height;
    const char* title;
    GLFWwindow* window;
} Wnd;

typedef struct Engine {
    
} Engine;

static Wnd mainWindow;
static Engine engine;

void setCallbacks(void);

void InitEngine(){
    if (!glfwInit() || !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    mainWindow.window = glfwCreateWindow(800, 600, "IslandTap Engine", NULL, NULL);
    if (!mainWindow.window) {
        
        glfwTerminate();
        return;
    }

    setCallbacks(); // Sets input and window_Resize callbacks
    glfwMakeContextCurrent(mainWindow.window);
}


void RenderLoop(){
    while (!glfwWindowShouldClose(mainWindow.window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        

        glfwSwapBuffers(mainWindow.window);
        glfwPollEvents();
    }
}


void TerminateEngine(){
    if (mainWindow.window) {
        glfwDestroyWindow(mainWindow.window);
    }
    glfwTerminate();
}

// Currently listening for:
// - ESC key to close the window
void callback_key(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void callback_wndSize_Update(GLFWwindow* window, int width, int height){
    mainWindow.width = width;
    mainWindow.height = height;
    glViewport(0, 0, width, height);
}

void setCallbacks(void){
    glfwSetKeyCallback(mainWindow.window, callback_key);
    glfwSetFramebufferSizeCallback(mainWindow.window, callback_wndSize_Update);
}