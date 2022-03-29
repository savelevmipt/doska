//
// Created by Matvey on 28.03.2022.
//

#include "Object.h"
Object::Object():ang(1, 0){}
Object::~Object()= default;

void Object::normSize() {
    size.set(fabs(size.x), fabs(size.y));
}