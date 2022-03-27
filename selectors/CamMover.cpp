//
// Created by Matvey on 26.03.2022.
//

#include "CamMover.h"
#include "../view/Camera.h"
CamMover::CamMover(Camera &_cam):Selector(_cam) {}
void CamMover::begin(const Position& start){
    last = start;
}
void CamMover::update(const Position& curr){
    Position delta = curr - last;
    cam.pos -= delta;
    cam.pos.floor();
}
void CamMover::finish(){}
void CamMover::render(){}