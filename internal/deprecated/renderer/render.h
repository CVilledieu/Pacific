#ifndef __ENGINE_RENDERER_H__
#define __ENGINE_RENDERER_H__

#include "GLAD/glad.h"
#include <GLFW/glfw3.h>


int RendInit(void);
void Render(void);

void CleanCanvas(void);
void Serve(void);

#endif