//
// Created by David Richter on 3/25/25.
//

#include "crystal.h"


Crystal::Crystal(float height)
    : mHeight(height)
{

}

void Crystal::draw() {
    auto yPosition = mHeight - (mHeight / 2.f);

    const auto alpha = 200;

    DrawCylinder(
        Vector3 { 0.f, -yPosition, 0.f },
        1.0f, 1.0f, mHeight, mNumSegments,
        Color { 55, 114, 255, alpha }
    );

    DrawCylinder(
        Vector3 { 0.f, yPosition, 0.f },
        0.f, 1.0f, mHeight / 3.f, mNumSegments,
        Color { 55, 114, 255, alpha }
    );

    DrawCylinder(
        Vector3 { 0.f, (-yPosition - 2.f), 0.f },
        1.f, 0.f, mHeight / 3.f, mNumSegments,
        Color { 55, 114, 255, alpha }
    );

    DrawCylinderWires(
        Vector3 { 0.f, -yPosition, 0.f },
        2.f, 2.f, mHeight, mNumSegments,
        Color { 22, 57, 127, 255 }
    );

    DrawCylinderWires(
        Vector3 { 0.f, yPosition, 0.f },
        0.f, 2.f, mHeight / 3.f, mNumSegments,
        Color { 55, 114, 255, 255 }
    );

    DrawCylinderWires(
        Vector3 { 0.f, (-yPosition - 2.f), 0.f },
        2.f,
        0.f,
        mHeight / 3.f,
        mNumSegments,
        Color { 55, 114, 255, 255 }
    );
}
