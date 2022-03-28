//
// Created by Matvey on 28.03.2022.
//

#include "Square.h"
#include "../view/Camera.h"
void Square::render(Camera &cam, const Vector2& c_pos) {
    cam.drawRect(c_pos + center, size, ang);
//    cam.drawRect(c_pos + center - size, size * 2);
}
Square::~Square(){}