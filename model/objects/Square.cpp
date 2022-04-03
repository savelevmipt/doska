//
// Created by Matvey on 28.03.2022.
//

#include "Square.h"
#include "../../view/Camera.h"
void Square::render(Camera &cam, const Vector2& c_pos) {
    cam.drawRect(c_pos + center, size, ang);
    // ang.rotate(Vector2(M_PI / 60));
}
Square::~Square()= default;
void Square::rotate(const Vector2 &_ang) {
    ang.rotate(_ang);
}
Object* Square::lightCopy(){
    auto *sq = new Square;
    sq->center = this->center;
    sq->ang = this->ang;
    sq->size = this->size;
    return sq;
}
bool Square::containsDot(const Vector2 &point) {
    Vector2 cd = center - point;
    cd.rotateBack(ang);
    return fabs(cd.x) < size.x && fabs(cd.y) < size.y;
}