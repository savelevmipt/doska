//
// Created by Matvey on 26.03.2022.
//

#include <queue>
#include <string>

#include "CurveDrawer.h"
#include "../view/Camera.h"

extern std::queue <std::string> msg_to_send;

CurveDrawer::CurveDrawer(Camera &_cam):Selector(_cam) {}

void CurveDrawer::begin(const Position& start){
    last = start;
}
void CurveDrawer::update(const Position& curr){
    cam.doska2.addLine(last, curr);
    std::string line_message = "C" + last.to_string() + curr.to_string(); //Curve
    msg_to_send.push(line_message);
    last = curr;
}
bool CurveDrawer::finish(){
    return true;
}

void CurveDrawer::render(){}