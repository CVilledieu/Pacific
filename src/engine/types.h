#ifndef __TYPES_H__
#define __TYPES_H__

#define WORLD_SCALE (1.0f / 100.0f)  // Compile-time constant
#define MAX_MODEL_COUNT 512


typedef float Vec2[2];
typedef float Mat4[16];


typedef enum Axis_t{
    X = 0,
    Y,
} Axis_t;


// Properties: Number of indices, Pos(x,y,z), Velocity(dX, dY, dZ), Size(width, height, length) 
typedef struct Entities_t{
    int count;

    float x[MAX_MODEL_COUNT];
    float y[MAX_MODEL_COUNT];
    
    float dX[MAX_MODEL_COUNT];
    float dY[MAX_MODEL_COUNT];
    
    float width[MAX_MODEL_COUNT];
    float height[MAX_MODEL_COUNT];
} Entities_t;

typedef struct ECS_t{
    // Can move and have collision
    Entities_t creatures; 
    // Cant move, but have collision
    Entities_t constructs; 
} ECS_t;

#endif