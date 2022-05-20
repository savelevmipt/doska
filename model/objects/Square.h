//
// Created by Matvey on 28.03.2022.
//

#ifndef DOSKA_SQUARE_H
#define DOSKA_SQUARE_H

#include "Object.h"

class Square:public Object {
public:
    void render(Camera& cam, const Vector2& c_pos) override;
    ~Square() override;
    void rotate(const Vector2& _ang) override;
    Object* lightCopy() override;
    void resize(const Vector2& d_size) override;

    bool containsDot(const Vector2& point) override;

};

#endif //DOSKA_SQUARE_H
