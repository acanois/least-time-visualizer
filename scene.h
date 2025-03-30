//
// Created by David Richter on 3/22/25.
//

#pragma once

#include "scenecamera.h"
#include "crystal.h"

#include "raylib.h"
#include "rlgl.h"

#include "oscpack/ip/UdpSocket.h"
#include "oscReceiver.h"

#include <iostream>
#include <format>
#include <memory>
#include <array>
#include <thread>

class Scene {
public:
    Scene();

public:
    void run();


private:
    void update();
    void draw();
    static Shader loadShader(std::string fileName);
    static Shader loadShader(std::string vertexName, std::string fragmentName);
    static Image loadImage(std::string fileName);

    static void oscHandler(UdpListeningReceiveSocket& oscServer);


private:
    MaxReceiver maxReceiver;
    UdpListeningReceiveSocket mOscServer;


private:
    static constexpr int mWindowWidth { 1280 };
    static constexpr int mWindowHeight { 720 };

    std::unique_ptr<SceneCamera> mCamera { nullptr };
    std::unique_ptr<Crystal> mCrystal { nullptr };
    std::vector<std::unique_ptr<Crystal>> mSubCrystals;

    static constexpr int NUM_CRYSTALS = 16;
    static constexpr float CIRCLE_RADIUS = 12.f;

    float mCameraTheta = 0.f;
};
