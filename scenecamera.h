//
// Created by David Richter on 3/22/25.
//

#include "raylib.h"

#include <cmath>

class SceneCamera {
public:
    SceneCamera() = default;

    SceneCamera(Vector3 position, Vector3 target, Vector3 up, float fovy, int projection);

    void updateCamera();
    void updateOrbitalCamera(float angle, float radius);
    void setPositionToOverhead();
    void resetPosition();

    void beginMode3d();
    static void endMode3d();



private:
    static float angleToRads(float angle);

    Camera3D mCamera { { 0 } };
};
