//
// Created by Matvey on 26.03.2022.
//

#include "Deleter.h"
#include "../view/Camera.h"
Deleter::Deleter(Camera &_cam): Selector(_cam) {}
void Deleter::begin(const Position& start){
    first = start;
    last = start;
}
void Deleter::update(const Position& curr){
    last = curr;
}
bool Deleter::finish(){
    cam.doska2.deleteVolume(first, last);
    return true;
}
void Deleter::render(){
    cam.drawRect((first - cam.pos).toFlo(), (last - first).toFlo());
}