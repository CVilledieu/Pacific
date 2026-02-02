#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "engine/types.h"

// Initialize camera with default 3D position and build viewProj matrix
void newDefaultCamera(Mat4 viewProj);

// Initialize camera with custom eye position and target, build viewProj matrix  
void newCustomCamera(Mat4 viewProj, Vec3 eye, Vec3 target);

// Move camera by delta (moves both eye and target)
void moveCamera(Mat4 viewProj, Vec3 delta);

// Set camera eye position directly
void setCameraPosition(Mat4 viewProj, Vec3 eye);

// Set camera look-at target
void setCameraTarget(Mat4 viewProj, Vec3 target);

// Set field of view in degrees
void setCameraFov(Mat4 viewProj, float fovDegrees);

// Update aspect ratio (call on window resize)
void updateCameraAspect(Mat4 viewProj, float aspect);

// Rebuild viewProj matrix (call if you modify camera state externally)
void buildViewProjMatrix(Mat4 viewProj);

#endif