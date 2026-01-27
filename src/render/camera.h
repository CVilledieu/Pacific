#ifndef __RENDER_CAMERA_H__
#define __RENDER_CAMERA_H__

#include "common/types.h"

typedef struct Camera_t{
    Vec2 fov;
    Vec4 bgColor;
} Camera_t;


Camera_t* initCamera(Vec2 initFOV);

void setPerspective(unsigned int shaderPID);

#endif