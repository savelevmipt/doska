//
// Created by Matvey on 28.03.2022.
//

#ifndef DOSKA_OBJECT_H
#define DOSKA_OBJECT_H

#include "../utils/Position.h"

class Camera;

class Object {
public:
    Vector2 center;
    Vector2 size;
    Vector2 ang;

    Object();
    virtual ~Object() = 0;

    void normSize();

    virtual void render(Camera& cam, const Vector2& c_pos) = 0;
};


#endif //DOSKA_OBJECT_H
