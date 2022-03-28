//
// Created by Matvey on 28.03.2022.
//

#ifndef DOSKA_SQUARE_H
#define DOSKA_SQUARE_H

#include "Object.h"

class Square:public Object {
public:
    void render(Camera& cam, const Vector2& c_pos) override;
    ~Square();
};


#endif //DOSKA_SQUARE_H
