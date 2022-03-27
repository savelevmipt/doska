//
// Created by Matvey on 26.03.2022.
//

#ifndef DOSKA_SELECTOR_H
#define DOSKA_SELECTOR_H
#include "../utils/Position.h"
class Position;
class Camera;

//Класс-обработчик движений мыши

class Selector {
public:
    Camera& cam;

    Selector(Camera& _cam);
    virtual void begin(const Position& start) = 0;
    virtual void update(const Position& curr) = 0;
    virtual void finish() = 0;
    virtual void render() = 0;
};


#endif //DOSKA_SELECTOR_H
