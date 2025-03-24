//
// Created by David Richter on 3/22/25.
//

#pragma once

#include "scenecamera.h"

#include <iostream>
#include <format>
#include <memory>

class Scene {
public:
    Scene();

public:
    void run();


private:
    void update();
    void draw();
    static Shader loadShader(std::string fileName);


private:
    static constexpr int mWindowWidth { 1280 };
    static constexpr int mWindowHeight { 720 };

    float mCameraTheta = 0.f;

    bool mShowGrid { false };

    std::unique_ptr<SceneCamera> mCamera = nullptr;
};
