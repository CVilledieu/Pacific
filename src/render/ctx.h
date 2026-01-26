#ifndef __RENDER_CTX_H__
#define __RENDER_CTX_H__

typedef float Vec2[2];
typedef struct {
    unsigned int PID;
    unsigned int VAO;
} RenderCtx_t;

extern RenderCtx_t rCtx;


void initCtx(void);
void drawLoop(void);


#endif