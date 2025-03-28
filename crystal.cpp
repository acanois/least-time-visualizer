//
// Created by David Richter on 3/25/25.
//

#include "crystal.h"


Crystal::Crystal(Vector3 position, float height, Color color)
    : mPosition(position),
      mHeight(height),
      mColor(color)
{

}

void Crystal::update() {
    mTheta += 0.1f;
}

void Crystal::draw() const {
    auto yOffset = mHeight / 2.f;
    auto coneHeight = mHeight / 3.f;
    auto diameter = mHeight / 6.f;

    rlPushMatrix();
    rlTranslatef(mPosition.x, mPosition.y, mPosition.z);
    rlRotatef(mTheta, 0.f, 1.f, 0.f);
        DrawCylinder(
            Vector3 { 0.f, -yOffset, 0.f },
            diameter, diameter, mHeight, mNumSegments,
            mColor
        );

        DrawCylinder(
            Vector3 { 0.f, mHeight - yOffset, 0.f },
            0.f, diameter, mHeight / 3.f, mNumSegments,
            mColor
        );

        DrawCylinder(
            Vector3 { 0.f, -coneHeight - yOffset, 0.f },
            diameter, 0.f, mHeight / 3.f, mNumSegments,
            mColor
        );

        DrawCylinderWires(
            Vector3 { 0.f, -yOffset, 0.f },
            diameter * 2.f, diameter * 2.f, mHeight, mNumSegments,
            mColor
        );

    rlPopMatrix();
}
