//
// Created by David Richter on 3/22/25.
//

#include "scenecamera.h"

SceneCamera::SceneCamera(
    Vector3 position,
    Vector3 target,
    Vector3 up,
    float fovy,
    int projection
)
    : mCamera({ position, target, up, fovy, projection })
{

}

void SceneCamera::updateCamera() {
    if (IsKeyDown(KEY_UP)) mCamera.position.y += 1;
    if (IsKeyDown(KEY_DOWN)) mCamera.position.y -= 1;
    if (IsKeyDown(KEY_LEFT)) mCamera.position.x -= 1;
    if (IsKeyDown(KEY_RIGHT)) mCamera.position.x += 1;
    if (IsKeyDown(KEY_S)) mCamera.position.z += 1;
    if (IsKeyDown(KEY_W)) mCamera.position.z -= 1;
}

void SceneCamera::updateOrbitalCamera(float angle, float radius) {
    mCamera.position = Vector3 {
        cos(angleToRads(angle)) * radius,
        0.f,
        sin(angleToRads(angle)) * radius
    };
}

float SceneCamera::angleToRads(float angle) {
    return angle * static_cast<float>(M_PI) / 180.f;
}

void SceneCamera::beginMode3d() {
    BeginMode3D(mCamera);
}

void SceneCamera::endMode3d() {
    EndMode3D();
}
