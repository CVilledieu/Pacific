#ifndef __TYPES_H__
#define __TYPES_H__

#define WORLD_SCALE (1.0f / 100.0f)  // Compile-time constant
#define MAX_MODEL_COUNT 512


typedef float Vec2[2];
typedef float Vec3[3];
typedef float Vec4[4];
typedef float Mat4[16];
typedef float Camera_t[16];

typedef enum Axis_t{
    X = 0,
    Y,
    Z,
} Axis_t;

typedef enum {
    SQUARE,
    CIRCLE,
    TOTAL_MESH_BASES,
} MeshBase_t;



typedef struct EntityList_t{
    MeshBase_t baseType;
    int count;
    float x[MAX_MODEL_COUNT];
    float y[MAX_MODEL_COUNT];
    float z[MAX_MODEL_COUNT];
    float height[MAX_MODEL_COUNT];
    float width[MAX_MODEL_COUNT];
    float length[MAX_MODEL_COUNT];
    float dX[MAX_MODEL_COUNT];
    float dY[MAX_MODEL_COUNT];
    float dZ[MAX_MODEL_COUNT];
} EntityList_t;



typedef struct Scene_t {
    Camera_t camera;
    EntityList_t* allLists[TOTAL_MESH_BASES];
    int listCount;
} Scene_t;


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