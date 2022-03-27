//
// Created by Matvey on 26.03.2022.
//

#include "CurveDrawer.h"
#include "../view/Camera.h"
CurveDrawer::CurveDrawer(Camera &_cam):Selector(_cam) {}

void CurveDrawer::begin(const Position& start){
    last = start;
}
void CurveDrawer::update(const Position& curr){
    cam.doska2.addLine(last, curr);
    last = curr;
}
void CurveDrawer::finish(){}

void CurveDrawer::render(){}