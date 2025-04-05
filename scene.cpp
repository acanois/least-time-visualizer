//
// Created by David Richter on 3/22/25.
//

#include "scene.h"


Scene::Scene()
    : mCamera(std::make_unique<SceneCamera>(
        Vector3 { 0.f, 0.f, -25.f },
        Vector3 { 0.f, 0.f, 0.f },
        Vector3 { 0.f, 1.f, 0.f },
        45.f,
        CAMERA_PERSPECTIVE
    )),
    mCrystal(std::make_unique<Crystal>(
        Vector3 { 0.f, 0.f, 0.f },
        4.f, Color { 243, 243, 244, 255 }
    ))
{

}

Shader Scene::loadShader(std::string fileName) {
    auto rootDir = GetPrevDirectoryPath(GetWorkingDirectory());
    auto shaderPath = std::format("{}/resources/shaders/{}", rootDir, fileName);

    Shader shader = LoadShader(nullptr, shaderPath.c_str());

    return shader;
}

Shader Scene::loadShader(std::string vertexName, std::string fragmentName) {
    auto rootDir = GetPrevDirectoryPath(GetWorkingDirectory());
    auto vertexPath = std::format("{}/resources/shaders/{}", rootDir, vertexName);
    auto fragmentPath = std::format("{}/resources/shaders/{}", rootDir, fragmentName);

    Shader shader = LoadShader(vertexPath.c_str(), fragmentPath.c_str());

    return shader;
}

Image Scene::loadImage(std::string fileName) {
    auto rootDir = GetPrevDirectoryPath(GetWorkingDirectory());
    auto filePath = std::format("{}/resources/images/{}", rootDir, fileName);

    Image image = LoadImage(filePath.c_str());

    return image;
}

void Scene::run() {
    InitWindow(mWindowWidth, mWindowHeight, "Least Time");
    SetTargetFPS(60);

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    SetConfigFlags(FLAG_VSYNC_HINT);

    rlSetBlendMode(RL_BLEND_DST_ALPHA);

    bool showGrid = false;

    auto crystalHeight = mCrystal->getHeight();
    auto groundHeight = -crystalHeight - (crystalHeight / 2.f);

    auto angle = 0.f;
    auto angleIncrement = 360.f / static_cast<float>(NUM_CRYSTALS);
    auto subCrystalHeight = crystalHeight / 3.f;
    auto subCrystalYPos = groundHeight + subCrystalHeight * 1.5f;

    for (auto i = 0; i < NUM_CRYSTALS; i++) {
        auto theta = angle * static_cast<float>(M_PI) / 180.f;
        mSubCrystals.push_back(std::make_unique<Crystal>(
            Vector3{
                sin(theta) * CIRCLE_RADIUS,
                subCrystalYPos,
                cos(theta) * CIRCLE_RADIUS
            },
            1.f,
            ColorFromHSV(angle, 0.75f, 1.f)
        ));
        angle += angleIncrement;
    }

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ONE)) mCamera->resetPosition();
        if (IsKeyPressed(KEY_TWO)) mCamera->setPositionToOverhead();

        BeginDrawing();
        ClearBackground(Color { 24, 29, 39, 255 });

        mCamera->beginMode3d();

        mCrystal->draw();

        for (auto&& crystal : mSubCrystals) {
            crystal->draw();
            crystal->update();
        }

        DrawCircle3D(
            Vector3 { 0.f, groundHeight + 0.1f, 0.f },
            CIRCLE_RADIUS,
            Vector3 { 1.f, 0.f, 0.f },
            90.f,
            Color { 243, 243, 244, 255 }
        );

        rlPushMatrix();
        rlTranslatef(0.f, groundHeight, 0.f);
        DrawPlane(
            Vector3 { 0.f, 0.f, 0.f },
            Vector2 { 60.f, 60.f },
            Color { 125, 130, 184, 255 }
        );
        rlPopMatrix();

        if (IsKeyPressed(KEY_G)) showGrid = !showGrid;
        if (showGrid) DrawGrid(10, 1.0f);

        mCamera->endMode3d();
        EndDrawing();
        update();
    }

    CloseWindow();
}

void Scene::update() {
    mCameraTheta += 0.011;
    mCamera->updateOrbitalCamera(mCameraTheta, 25.f);
    mCrystal->update();
}

void Scene::draw() {

}