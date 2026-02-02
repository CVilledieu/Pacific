#include "camera.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <string.h>
#include <math.h>

// X axis rotation
// | 1    0       0    0 |
// | 0   cos   -sin    0 |
// | 0   sin    cos    0 |
// | 0    0       0    1 |

// Y axis rotation
// | cos   0   sin   0 | 
// |  0    1    0    0 |  
// |-sin   0   cos   0 |   
// |  0    0    0    1 |   

// Z axis rotation
// | cos  -sin  0    0 |
// | sin   cos  0    0 |
// | 0     0    1    0 |
// | 0     0    0    1 |

// [0]	= sx * (cy*cz)
// [1]	= sx * (cy*sz)
// [2]	= sx * (-sy)
// [4]	= sy * (sx*cz*sy - cx*sz)
// [5]	= sy * (sx*sz*sy + cx*cz)
// [6]	= sy * (sx*cy)
// [8]	= sz * (cx*cz*sy + sx*sz)
// [9]	= sz * (cx*sz*sy - sx*cz)
// [10]	= hsz * (cx*cy)


// Default camera position for 3D view
#define DEFAULT_EYE_X    0.0f
#define DEFAULT_EYE_Y    2.0f
#define DEFAULT_EYE_Z    5.0f
#define DEFAULT_TARGET_X 0.0f
#define DEFAULT_TARGET_Y 0.0f
#define DEFAULT_TARGET_Z 0.0f

// Default perspective params
#define DEFAULT_FOV      60.0f   // degrees
#define DEFAULT_ASPECT   (800.0f / 600.0f)
#define DEFAULT_NEAR     0.1f
#define DEFAULT_FAR      100.0f

static void initIdentity(Mat4 m){
    memset(m, 0, sizeof(Mat4));
    m[0]  = 1.0f;
    m[5]  = 1.0f;
    m[10] = 1.0f;
    m[15] = 1.0f;
}

// CPU-side matrix multiply: result = a * b (column-major)
static void multiplyMat4(Mat4 result, const Mat4 a, const Mat4 b){
    for (int col = 0; col < 4; col++){
        for (int row = 0; row < 4; row++){
            result[col * 4 + row] = 
                a[0 * 4 + row] * b[col * 4 + 0] +
                a[1 * 4 + row] * b[col * 4 + 1] +
                a[2 * 4 + row] * b[col * 4 + 2] +
                a[3 * 4 + row] * b[col * 4 + 3];
        }
    }
}

// Build perspective projection matrix (CPU-side)
static void perspectiveMatrix(Mat4 m, float fovDegrees, float aspect, float nearZ, float farZ){
    memset(m, 0, sizeof(Mat4));
    
    float fovRad = fovDegrees * (3.14159265f / 180.0f);
    float tanHalfFov = tanf(fovRad / 2.0f);
    
    m[0]  = 1.0f / (aspect * tanHalfFov);
    m[5]  = 1.0f / tanHalfFov;
    m[10] = -(farZ + nearZ) / (farZ - nearZ);
    m[11] = -1.0f;
    m[14] = -(2.0f * farZ * nearZ) / (farZ - nearZ);
    // m[15] = 0.0f (already zeroed)
}

// Build lookAt view matrix (CPU-side)
static void lookAtMatrix(Mat4 m, Vec3 eye, Vec3 target, Vec3 up){
    // Forward vector (from target to eye, because we look along -Z)
    float fx = eye[X] - target[X];
    float fy = eye[Y] - target[Y];
    float fz = eye[Z] - target[Z];
    float fLen = sqrtf(fx*fx + fy*fy + fz*fz);
    fx /= fLen; fy /= fLen; fz /= fLen;
    
    // Right vector = up cross forward
    float rx = up[Y] * fz - up[Z] * fy;
    float ry = up[Z] * fx - up[X] * fz;
    float rz = up[X] * fy - up[Y] * fx;
    float rLen = sqrtf(rx*rx + ry*ry + rz*rz);
    rx /= rLen; ry /= rLen; rz /= rLen;
    
    // Recalculate up = forward cross right
    float ux = fy * rz - fz * ry;
    float uy = fz * rx - fx * rz;
    float uz = fx * ry - fy * rx;
    
    // Build view matrix (column-major)
    m[0]  = rx;  m[1]  = ux;  m[2]  = fx;  m[3]  = 0.0f;
    m[4]  = ry;  m[5]  = uy;  m[6]  = fy;  m[7]  = 0.0f;
    m[8]  = rz;  m[9]  = uz;  m[10] = fz;  m[11] = 0.0f;
    m[12] = -(rx*eye[X] + ry*eye[Y] + rz*eye[Z]);
    m[13] = -(ux*eye[X] + uy*eye[Y] + uz*eye[Z]);
    m[14] = -(fx*eye[X] + fy*eye[Y] + fz*eye[Z]);
    m[15] = 1.0f;
}

// Camera state
static Vec3 cameraEye    = {DEFAULT_EYE_X, DEFAULT_EYE_Y, DEFAULT_EYE_Z};
static Vec3 cameraTarget = {DEFAULT_TARGET_X, DEFAULT_TARGET_Y, DEFAULT_TARGET_Z};
static Vec3 cameraUp     = {0.0f, 1.0f, 0.0f};
static float cameraFov   = DEFAULT_FOV;
static float cameraAspect = DEFAULT_ASPECT;

// Build combined view-projection matrix (call this before draw)
void buildViewProjMatrix(Mat4 viewProj){
    Mat4 view, proj;
    lookAtMatrix(view, cameraEye, cameraTarget, cameraUp);
    perspectiveMatrix(proj, cameraFov, cameraAspect, DEFAULT_NEAR, DEFAULT_FAR);
    multiplyMat4(viewProj, proj, view);  // proj * view
}

void newDefaultCamera(Mat4 viewProj){
    cameraEye[X] = DEFAULT_EYE_X;
    cameraEye[Y] = DEFAULT_EYE_Y;
    cameraEye[Z] = DEFAULT_EYE_Z;
    cameraTarget[X] = DEFAULT_TARGET_X;
    cameraTarget[Y] = DEFAULT_TARGET_Y;
    cameraTarget[Z] = DEFAULT_TARGET_Z;
    cameraFov = DEFAULT_FOV;
    buildViewProjMatrix(viewProj);
}

void newCustomCamera(Mat4 viewProj, Vec3 eye, Vec3 target){
    cameraEye[X] = eye[X];
    cameraEye[Y] = eye[Y];
    cameraEye[Z] = eye[Z];
    cameraTarget[X] = target[X];
    cameraTarget[Y] = target[Y];
    cameraTarget[Z] = target[Z];
    buildViewProjMatrix(viewProj);
}

void moveCamera(Mat4 viewProj, Vec3 delta){
    cameraEye[X] += delta[X];
    cameraEye[Y] += delta[Y];
    cameraEye[Z] += delta[Z];
    cameraTarget[X] += delta[X];
    cameraTarget[Y] += delta[Y];
    cameraTarget[Z] += delta[Z];
    buildViewProjMatrix(viewProj);
}

void setCameraPosition(Mat4 viewProj, Vec3 eye){
    cameraEye[X] = eye[X];
    cameraEye[Y] = eye[Y];
    cameraEye[Z] = eye[Z];
    buildViewProjMatrix(viewProj);
}

void setCameraTarget(Mat4 viewProj, Vec3 target){
    cameraTarget[X] = target[X];
    cameraTarget[Y] = target[Y];
    cameraTarget[Z] = target[Z];
    buildViewProjMatrix(viewProj);
}

void setCameraFov(Mat4 viewProj, float fovDegrees){
    cameraFov = fovDegrees;
    buildViewProjMatrix(viewProj);
}

// Update aspect ratio (call on window resize)
void updateCameraAspect(Mat4 viewProj, float aspect){
    cameraAspect = aspect;
    buildViewProjMatrix(viewProj);
}

void updatedWindowSize(GLFWwindow* window, int width, int height){
    (void)window;
    glViewport(0, 0, width, height);
    // Note: To update aspect ratio, caller should also call updateCameraAspect
}

void initCamera(GLFWwindow* window){
    glfwSetFramebufferSizeCallback(window, updatedWindowSize);
}