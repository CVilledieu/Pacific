#ifndef __RENDER_DRAW_H__
#define __RENDER_DRAW_H__

#include "camera.h"
#include "scene.h"

typedef struct {
    unsigned int PID;
    unsigned int VAO;
    Vec4 bgColor;
} RenderCtx_t;

extern RenderCtx_t rCtx;

void initCtx(void);
void draw(void);

#endif