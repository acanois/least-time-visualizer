//
// Created by David Richter on 3/22/25.
//

#include "scene.h"


Scene::Scene()
    : mCamera(std::make_unique<SceneCamera>(
        Vector3 { 0.f, 0.f, -20.f },
        Vector3 { 0.f, 0.f, 0.f },
        Vector3 { 0.f, 1.f, 0.f },
        45.f,
        CAMERA_PERSPECTIVE
    ))
{

}

void Scene::run() {
    InitWindow(mWindowWidth, mWindowHeight, "Least Time");
    SetTargetFPS(60);
    SetConfigFlags(FLAG_MSAA_4X_HINT);

    RenderTexture2D target = LoadRenderTexture(1280, 720);
    Shader shader = LoadShader(nullptr, "/Users/davidrichter/CLionProjects/LeastTimeVizualizer/resources/shaders/bloom.fs");
    while (!WindowShouldClose()) {
        BeginTextureMode(target);
        ClearBackground(Color { 37, 36, 34, 255 });
        mCamera->beginMode3d();

        auto height = 6.f;
        auto yPosition = height - (height / 2.f);

        const auto alpha = 200;
        const auto segments = 12;

        DrawCylinder(
            Vector3 { 0.f, -yPosition, 0.f },
            1.0f, 1.0f, height, segments,
            Color { 55, 114, 255, alpha }
        );

        DrawCylinder(
            Vector3 { 0.f, yPosition, 0.f },
            0.f, 1.0f, height / 3.f, segments,
            Color { 55, 114, 255, alpha }
        );

        DrawCylinder(
            Vector3 { 0.f, (-yPosition - 2.f), 0.f },
            1.f, 0.f, height / 3.f, segments,
            Color { 55, 114, 255, alpha }
        );

        DrawCylinderWires(
            Vector3 { 0.f, -yPosition, 0.f },
            2.f, 2.f, height, segments,
            Color { 22, 57, 127, 255 }
        );

        DrawCylinderWires(
            Vector3 { 0.f, yPosition, 0.f },
            0.f, 2.f, height / 3.f, segments,
            Color { 55, 114, 255, 255 }
        );

        DrawCylinderWires(
            Vector3 { 0.f, (-yPosition - 2.f), 0.f },
            2.f,
            0.f,
            height / 3.f,
            segments,
            Color { 55, 114, 255, 255 }
        );

        if (IsKeyPressed(KEY_G)) mShowGrid = !mShowGrid;
        if (mShowGrid) DrawGrid(10, 1.0f);

        mCamera->endMode3d();
        EndTextureMode();

        BeginDrawing();
        ClearBackground(Color { 37, 36, 34, 255 });

        BeginShaderMode(shader);
        DrawTextureRec(
            target.texture,
            (Rectangle){ 0, 0, (float)target.texture.width, (float)-target.texture.height },
            (Vector2){ 0, 0 },
            WHITE
        );
        EndShaderMode();
        EndDrawing();
        update();
    }

    UnloadShader(shader);
    UnloadRenderTexture(target);
}

void Scene::update() {
    mCameraTheta += 0.1;
    mCamera->updateOrbitalCamera(mCameraTheta, 20.f);
}

void Scene::draw() {

}