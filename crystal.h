//
// Created by David Richter on 3/25/25.
//

#pragma once

#include "raylib.h"
#include "rlgl.h"


class Crystal {
public:
    explicit Crystal(Vector3 position, float height);

    void update();
    void draw() const;

private:
    static constexpr int mNumSegments { 12 };

    Vector3 mPosition { 0 };

    float mHeight { 6.f };
    float mTheta { 0.f };
};
