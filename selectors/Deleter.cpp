//
// Created by Matvey on 26.03.2022.
//
#include <queue>

#include "Deleter.h"
#include "../view/Camera.h"

extern std::queue <std::string> msg_to_send;

Deleter::Deleter(Camera &_cam): Selector(_cam) {}
void Deleter::begin(const Position& start){
    first = start;
    last = start;
}
void Deleter::update(const Position& curr){
    last = curr;
}
bool Deleter::finish(){
    IntPosition chunk_to_save(0, 0);
    ChunkObject* obj = cam.doska2.assemble(first, last, chunk_to_save);
    msg_to_send.push("D" + to_string());
    delete obj;
    return true;
}
void Deleter::render(){
    cam.drawRect((first - cam.pos).toFlo(), (last - first).toFlo());
}

std::string Deleter::to_string() const {
    return first.to_string() + last.to_string();
}

