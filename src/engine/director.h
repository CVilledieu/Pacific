#ifndef __DIRECTOR_H__
#define __DIRECTOR_H__

#include "types.h"

#define MAX_MODEL_COUNT 512

#define DEFAULT_HERO_X 0.0f
#define DEFAULT_HERO_Y 0.0f

#define DEFAULT_HERO_W 0.5f
#define DEFAULT_HERO_H 0.5f


void initDirector(GLFWwindow* window);
void update(void);


typedef struct Entities_t{
    int count;
    
    float x[MAX_MODEL_COUNT];
    float y[MAX_MODEL_COUNT];
    
    float dX[MAX_MODEL_COUNT];
    float dY[MAX_MODEL_COUNT];
    
    float width[MAX_MODEL_COUNT];
    float height[MAX_MODEL_COUNT];
} Entities_t;

typedef struct Atlas_t{
    Entities_t creatures;
    Entities_t constructs;
} Atlas_t;


Atlas_t* getAtlas(void);

#endif