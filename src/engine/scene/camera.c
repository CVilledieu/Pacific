#include "camera.h"

#include <string.h>

// Column-major 4x4 matrix indices:
// [0]  [4]  [8]  [12]    Sx   0    0   Tx
// [1]  [5]  [9]  [13]     0  Sy    0   Ty
// [2]  [6] [10]  [14]     0   0   Sz   Tz
// [3]  [7] [11]  [15]     0   0    0    1

#define DEFAULT_WIDTH 0.5f
#define DEFAULT_HEIGHT 0.5f
#define DEFAULT_LENGTH 1.0f

static void initIdentity(Camera_t camera){
    memset(camera, 0, sizeof(Camera_t));
    camera[0]  = 1.0f;  // Sx
    camera[5]  = 1.0f;  // Sy
    camera[10] = 1.0f;  // Sz
    camera[15] = 1.0f;  // W (homogeneous)
}

void newDefaultCamera(Camera_t camera){
    initIdentity(camera);
    camera[0]  = DEFAULT_WIDTH;   // Scale X
    camera[5]  = DEFAULT_HEIGHT;  // Scale Y
    camera[10] = DEFAULT_LENGTH;  // Scale Z
}

void newCustomCamera(Camera_t camera, Vec3 scale, Vec3 move){
    initIdentity(camera);
    // Scale
    camera[0]  = scale[X];  // Scale X
    camera[5]  = scale[Y];  // Scale Y
    camera[10] = scale[Z];  // Scale Z

    // Translation
    camera[12] = move[X];   // Translate X
    camera[13] = move[Y];   // Translate Y
    camera[14] = move[Z];   // Translate Z
}

void scaleCamera(Camera_t camera, Vec3 scale){
    camera[0]  = scale[X];  // Scale X
    camera[5]  = scale[Y];  // Scale Y
    camera[10] = scale[Z];  // Scale Z
}

void moveCamera(Camera_t camera, Vec3 move){
    camera[12] = move[X];   // Translate X
    camera[13] = move[Y];   // Translate Y
    camera[14] = move[Z];   // Translate Z
}