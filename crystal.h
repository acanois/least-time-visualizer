//
// Created by David Richter on 3/25/25.
//

#pragma once

#include "raylib.h"


class Crystal {
public:
    explicit Crystal(float height);

    void draw();

private:
    static constexpr int mNumSegments { 12 };

    float mHeight;
};
