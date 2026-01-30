#ifndef __TYPES_H__
#define __TYPES_H__

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
    float height[MAX_MODEL_COUNT];
    float width[MAX_MODEL_COUNT];
    float xV[MAX_MODEL_COUNT];
    float yV[MAX_MODEL_COUNT];
} EntityList_t;

typedef float Camera_t[16];

typedef struct Scene_t {
    Camera_t camera;
    EntityList_t* allLists[TOTAL_MESH_BASES];
    int listCount;
} Scene_t;



#endif