//
// Created by Matvey on 28.03.2022.
//

#ifndef DOSKA_OBJECT_H
#define DOSKA_OBJECT_H

#include "../../utils/Position.h"

class Camera;
//Объект на доске
class Object {
public:
    Vector2 center;//Кажется, можно менять извне, придется менять извне для перемещения объекта между чанками

    Vector2 size;//Для изменения size извне придумать метод (нужно растягивать содержимое объекта)
    Vector2 ang;//Для изменения ang извне вызывать метод rotate()

    Object();
    virtual ~Object() = 0;

    void normSize();

    virtual void render(Camera& cam, const Vector2& c_pos) = 0;

    virtual void rotate(const Vector2& _ang) = 0;//повернуть относительно центра
    virtual Object* lightCopy() = 0; //быстрое копирование (в смысле если у нас запущена игра в окне, не нужно все данные о ней копировать)
    /*
     * Изменить размер size, d_size в абсолютной системе
     * center изменяется вызвавшим метод
     */
    virtual void resize(const Vector2& d_size) = 0;

    virtual bool containsDot(const Vector2& dot) = 0;//содержит ли объект точку, для неквадратных объектов и объектов с пустотами

};


#endif //DOSKA_OBJECT_H
