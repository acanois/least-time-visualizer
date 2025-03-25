//
// Created by David Richter on 3/25/25.
//

#include "crystal.h"


Crystal::Crystal(Vector3 position, float height)
    : mPosition(position),
      mHeight(height)
{

}

void Crystal::update() {
    mTheta += 0.1f;
}

void Crystal::draw() const {
    auto yOffset = mHeight / 2.f;
    auto coneHeight = mHeight / 3.f;

    const auto alpha = 200;

    rlPushMatrix();
    rlTranslatef(mPosition.x, mPosition.y, mPosition.z);
    rlRotatef(mTheta, 0.f, 1.f, 0.f);
        DrawCylinder(
            Vector3 { 0.f, -yOffset, 0.f },
            1.0f, 1.0f, mHeight, mNumSegments,
            Color { 55, 114, 255, alpha }
        );

        DrawCylinder(
            Vector3 { 0.f, mHeight - yOffset, 0.f },
            0.f, 1.0f, mHeight / 3.f, mNumSegments,
            Color { 55, 114, 255, alpha }
        );

        DrawCylinder(
            Vector3 { 0.f, -coneHeight - yOffset, 0.f },
            1.f, 0.f, mHeight / 3.f, mNumSegments,
            Color { 55, 114, 255, alpha }
        );

        DrawCylinderWires(
            Vector3 { 0.f, -yOffset, 0.f },
            2.f, 2.f, mHeight, mNumSegments,
            Color { 22, 57, 127, 255 }
        );

//        DrawCylinderWires(
//            Vector3 { 0.f, mHeight - yOffset, 0.f },
//            0.f, 2.f, mHeight / 3.f, mNumSegments,
//            Color { 55, 114, 255, 255 }
//        );
//
//        DrawCylinderWires(
//            Vector3 { 0.f, -coneHeight - yOffset, 0.f },
//            2.f,
//            0.f,
//            mHeight / 3.f,
//            mNumSegments,
//            Color { 55, 114, 255, 255 }
//        );
    rlPopMatrix();
}
