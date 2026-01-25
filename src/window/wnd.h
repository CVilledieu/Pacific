#ifndef __WINDOW_H__
#define __WINDOW_H__


#include "GLAD/glad.h"
#include <GLFW/glfw3.h>

typedef struct Wnd {
    int width;
    int height;
    GLFWwindow* window;
} Wnd;

extern Wnd* mainWindow;

int createWindow(void);
void closeWindow(void);

#endif