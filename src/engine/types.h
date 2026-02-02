#ifndef __TYPES_H__
#define __TYPES_H__

#define WORLD_SCALE (1.0f / 100.0f)  // Compile-time constant
#define MAX_MODEL_COUNT 512


typedef float Vec2[2];
typedef float Vec3[3];
typedef float Vec4[4];
typedef float Mat4[16];


typedef enum Axis_t{
    X = 0,
    Y,
    Z,
} Axis_t;


// Properties: Number of indices, Pos(x,y,z), Velocity(dX, dY, dZ), Size(width, height, length) 
typedef struct Entities_t{
    int count;

    float x[MAX_MODEL_COUNT];
    float y[MAX_MODEL_COUNT];
    float z[MAX_MODEL_COUNT];
    
    float dX[MAX_MODEL_COUNT];
    float dY[MAX_MODEL_COUNT];
    float dZ[MAX_MODEL_COUNT];
    
    float width[MAX_MODEL_COUNT];
    float height[MAX_MODEL_COUNT];
    float length[MAX_MODEL_COUNT];
} Entities_t;

typedef struct ECS_t{
    // Can move and have collision
    Entities_t creatures; 
    // Cant move, but have collision
    Entities_t constructs;
} ECS_t;


static inline void calibrateVec2(Vec2 dest, int x, int y){
    dest[X] = (float)x * WORLD_SCALE;
    dest[Y] = (float)y * WORLD_SCALE;
}

static inline void calibrateVec3(Vec3 dest, int x, int y, int z){
    dest[X] = (float)x * WORLD_SCALE;
    dest[Y] = (float)y * WORLD_SCALE;
    dest[Z] = (float)z * WORLD_SCALE;
}

#endif