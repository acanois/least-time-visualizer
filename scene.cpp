//
// Created by David Richter on 3/22/25.
//

#include "scene.h"


Scene::Scene()
    : mCamera(std::make_unique<SceneCamera>(
        Vector3 { 0.f, 0.f, -10.f },
        Vector3 { 0.f, 0.f, 0.f },
        Vector3 { 0.f, 1.f, 0.f },
        45.f,
        CAMERA_PERSPECTIVE
    ))
{
    InitWindow(mWindowWidth, mWindowHeight, "Least Time");
    SetTargetFPS(60);
}

void Scene::run() {
    while (!WindowShouldClose()) {
        draw();
    }
}

void Scene::draw() {
    BeginDrawing();
    ClearBackground(Color { 37, 36, 34, 255 });
    mCamera->beginMode3d();

    auto height = 6.f;
    auto yPosition = height - (height / 2.f);
    DrawCylinder(
        Vector3 { 0.f, -yPosition, 0.f },
        1.0f, 1.0f, height, 16.f,
        Color { 55, 114, 255, 255 }
    );
//    DrawCubeWires(
//        Vector3 { 0.f, 0.f, 0.f },
//        2.0f, 2.0f, 2.0f,
//        Color { 243, 41, 53, 255 }
//    );

    DrawGrid(10, 1.0f);

    mCamera->endMode3d();
    EndDrawing();
}