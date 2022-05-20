//
// Created by Matvey on 29.03.2022.
//

#include "Copyer.h"
#include "../view/Camera.h"
Copyer::Copyer(Camera &_cam): Selector(_cam) {}
void Copyer::begin(const Position& start){
    first = start;
    last = start;
}
void Copyer::update(const Position& curr){
    last = curr;
}
bool Copyer::finish(){
    IntPosition chunk_to_save(0, 0);
    ChunkObject* obj = cam.doska2.assemble(first, last, chunk_to_save);
    for(int i = 0; i < 5; ++i) {
        cam.doska2.disassemble((ChunkObject*)obj->lightCopy(), chunk_to_save);
        obj->rotate(M_PI / 3);
    }
    cam.doska2.disassemble(obj, chunk_to_save);
    return true;
}
void Copyer::render(){
    cam.drawRect((first - cam.pos).toFlo(), (last - first).toFlo());
}

std::string Copyer::to_string() const {
    return first.to_string() + last.to_string();
}