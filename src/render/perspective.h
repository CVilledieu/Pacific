#ifndef __RENDER_PERSPECTIVE_H__
#define __RENDER_PERSPECTIVE_H__

typedef struct {
    float height;
    float width;
} ViewCtx_t;


void initPerspective(ViewCtx_t* view);

void setPerspective(unsigned int shaderPID);

#endif