#ifndef __TYPES_H__
#define __TYPES_H__


#define WORLD_SCALE (1.0f / 100.0f)  // Compile-time constant


typedef float Vec2[2];
typedef float Mat4[16];


typedef struct Object_t{
    int ObjType; //0 = creature 1 = construct
    float x;
    float y;
    float dX;
    float dY;
    float width;
    float height;
} Entity_t;




#endif