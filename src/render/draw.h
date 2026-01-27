#ifndef __RENDER_DRAW_H__
#define __RENDER_DRAW_H__

// Should probably change to something like eX = 0, and eY.
// At the moment no issues, but could easily cause a problem
typedef enum {
    xCoord = 0,
    yCoord,
} Coord;

typedef float Vec2[2];

typedef struct Camera_t Camera_t;

typedef struct {
    unsigned int PID;
    unsigned int VAO;
    Camera_t* camera;
} RenderCtx_t;

extern RenderCtx_t rCtx;


void initCtx(void);
void draw(void);


#endif