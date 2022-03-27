//
// Created by Matvey on 26.03.2022.
//

#include "RectDrawer.h"
#include "../view/Camera.h"

RectDrawer::RectDrawer(Camera &_cam) : Selector(_cam) {}

void RectDrawer::begin(const Position &start) {
    first = start;
    last = start;
}

void RectDrawer::update(const Position &curr) {
    last = curr;
}

void RectDrawer::finish() {
    first.buildRectWith(last);
    cam.doska2.addLine(first, first + Position(
            0, last.intp.y - first.intp.y,
            0, last.flop.y - first.flop.y).toFlo());
    cam.doska2.addLine(first + Position(
                               0, last.intp.y - first.intp.y,
                               0, last.flop.y - first.flop.y).toFlo(),
                       last);
    cam.doska2.addLine(last,
                       first + Position(
                               last.intp.x - first.intp.x, 0,
                               last.flop.x - first.flop.x, 0).toFlo());
    cam.doska2.addLine(first + Position(
            last.intp.x - first.intp.x, 0,
            last.flop.x - first.flop.x, 0).toFlo(),
                       first);
}

void RectDrawer::render() {
    cam.drawRect((first - cam.pos).toFlo(), (last - first).toFlo());
}