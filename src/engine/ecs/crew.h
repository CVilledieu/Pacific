#ifndef __ECS_CREW_H__
#define __ECS_CREW_H__

#define MAX_MODEL_COUNT 512

typedef enum {
    SQUARE,
    CIRCLE, 
    TOTAL_MESH_TYPES,
} MeshType_t;

// Properties: Number of indices, Pos(x,y,z), Velocity(dX, dY, dZ), Size(width, height, length) 
typedef struct Entities_t{
    int count;
    MeshType_t meshType;

    float x[MAX_MODEL_COUNT];
    float y[MAX_MODEL_COUNT];
    float z[MAX_MODEL_COUNT];
    
    float dX[MAX_MODEL_COUNT];
    float dY[MAX_MODEL_COUNT];
    float dZ[MAX_MODEL_COUNT];
    
    float width[MAX_MODEL_COUNT];
    float height[MAX_MODEL_COUNT];
    float lengh[MAX_MODEL_COUNT];
} Entities_t;

typedef struct World_t{
    // Can move and have collision
    Entities_t actors[TOTAL_MESH_TYPES]; 
    // Cant move, but have collision
    Entities_t construct[TOTAL_MESH_TYPES];
    // Dont have collision and probably dont have movement(?/tbd)
    Entities_t items[TOTAL_MESH_TYPES];
    // 4th group? That have collision, but doesnt stop movement?
    // Example Projectiles, Check Points, 
} World_t;

#endif