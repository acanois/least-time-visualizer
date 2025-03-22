//
// Created by David Richter on 3/22/25.
//

#pragma once

#include "scenecamera.h"

#include <memory>

class Scene {
public:
    Scene() = default;
    Scene(Scene&&) = default;

    Scene& operator=(const Scene&) = default;
    Scene& operator=(const Scene&&) = delete;

    ~Scene() = default;

private:
    void draw();

    std::unique_ptr<SceneCamera> mCamera = nullptr;

};
