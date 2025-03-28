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
    )),
    mCrystal(std::make_unique<Crystal>(Vector3 { 0.f, 0.f, 0.f }, 6.f))
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

    // Render Texture
    RenderTexture2D target = LoadRenderTexture(1280, 720);

    // Skybox
    Mesh cube = GenMeshCube(100.f, 100.f, 100.f);
    Model skybox = LoadModelFromMesh(cube);

    auto useHDR = false;
    skybox.materials[0].shader = loadShader("skybox.vs", "skybox.fs");
    SetShaderValue(
        skybox.materials[0].shader,
        GetShaderLocation(skybox.materials[0].shader, "environmentMap"),
        (int[1]){ MATERIAL_MAP_CUBEMAP },
        SHADER_UNIFORM_INT
    );
    SetShaderValue(
        skybox.materials[0].shader,
        GetShaderLocation(skybox.materials[0].shader, "doGamma"),
        (int[1]) { useHDR ? 1 : 0 },
        SHADER_UNIFORM_INT);
    SetShaderValue(
        skybox.materials[0].shader,
        GetShaderLocation(skybox.materials[0].shader, "vflipped"),
        (int[1]){ useHDR ? 1 : 0 },
        SHADER_UNIFORM_INT
    );

    // Cubemap for skybox
    Shader shdrCubemap = loadShader("cubemap.vs", "cubemap.fs");
    SetShaderValue(
        shdrCubemap,
        GetShaderLocation(shdrCubemap, "equirectangularMap"),
        (float[1]) { 0 },
        SHADER_UNIFORM_FLOAT
    );

    Image skyboxTexture = loadImage("skybox-blue-night.png");
    skybox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = LoadTextureCubemap(
        skyboxTexture,
        CUBEMAP_LAYOUT_AUTO_DETECT
    );
    UnloadImage(skyboxTexture);

    // Postprocessing Bloom Shader
    auto shdrBloom = loadShader("bloom.fs");

    while (!WindowShouldClose()) {
        BeginTextureMode(target);
        ClearBackground(Color { 7, 6, 4, 255 });

        mCamera->beginMode3d();

        // Draw the skybox
        rlDisableBackfaceCulling();  // To see skybox texture
        rlDisableDepthMask();
            DrawModel(skybox, Vector3 { 0.f, 0.f, 0.f }, 1.f, WHITE);
        rlEnableBackfaceCulling();
        rlEnableDepthMask();

        mCrystal->draw();

        if (IsKeyPressed(KEY_G)) mShowGrid = !mShowGrid;
        if (mShowGrid) DrawGrid(10, 1.0f);

        mCamera->endMode3d();
        EndTextureMode();

        BeginDrawing();
        ClearBackground(Color { 7, 6, 4, 255 });

        DrawTextureRec(
            target.texture,
            Rectangle {
                0, 0,
                static_cast<float>(target.texture.width),
                static_cast<float>(-target.texture.height) // Inverted because OpenGL coordinates
            },
            Vector2 { 0, 0 },
            WHITE
        );
        EndDrawing();
        update();
    }

    UnloadShader(shdrCubemap);
    UnloadShader(skybox.materials[0].shader);
    UnloadShader(shdrBloom);
    UnloadRenderTexture(target);
    UnloadModel(skybox);

    CloseWindow();
}

void Scene::update() {
    mCameraTheta += 0.1;
    mCamera->updateOrbitalCamera(mCameraTheta, 20.f);
    mCrystal->update();
}

void Scene::draw() {

}