//
// Created by Matvey on 26.03.2022.
//

#include "RectDrawer.h"
#include "../view/Camera.h"

RectDrawer::RectDrawer(Camera &_cam) : Selector(_cam), square(nullptr) {}

void RectDrawer::begin(const Position &start) {
    first = start;
    last = start;
    square = new Square;
    square->center = first.flop;
    square->ang = Vector2(M_PI / 3);
}

void RectDrawer::update(const Position &curr) {
    last = curr;
    square->size = (last - first).toFlo();
    square->size.rotateBack(square->ang);
}

bool RectDrawer::finish() {
    square->normSize();
    cam.doska2.addObject(square, first.intp);
    return true;
}

void RectDrawer::render() {
    square->render(cam, -(cam.pos - first.intp).toFlo());
}