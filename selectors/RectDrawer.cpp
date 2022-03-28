//
// Created by Matvey on 26.03.2022.
//

#include "RectDrawer.h"
#include "../view/Camera.h"

RectDrawer::RectDrawer(Camera &_cam) : Selector(_cam) {}

void RectDrawer::begin(const Position &start) {
    first = start;
    last = start;
    square = new Square;
    square->center = first.flop;
}

void RectDrawer::update(const Position &curr) {
    last = curr;
    square->size = (last - first).toFlo();
}

bool RectDrawer::finish() {
    cam.doska2.addObject(square, first.intp);
    return true;
}

void RectDrawer::render() {
    square->render(cam, -(cam.pos - first.intp).toFlo());
}