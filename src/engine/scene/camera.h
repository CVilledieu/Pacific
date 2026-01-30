#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "engine/common/types.h"

void newDefaultCamera(Camera_t camera);
void newCustomCamera(Camera_t camera, Vec3 scale, Vec3 move);

#endif