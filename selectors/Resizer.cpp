//
// Created by Matvey on 29.03.2022.
//

#include "Resizer.h"
#include "../view/Camera.h"
Resizer::Resizer(Camera& _cam):
Selector(_cam),
resizing(nullptr),
isChunk(false),
chunk_pos(0, 0){}
Resizer::~Resizer() {
    delete resizing;
}
void Resizer::begin(const Position& start){
    if(resizing == nullptr){
        p_main = start;
        last = start;
    }else{

    }
}
void Resizer::update(const Position& curr){
    if(resizing == nullptr){
        last = curr;
    }else{

    }
}
bool Resizer::finish(){
    if(resizing == nullptr){
        ChunkObject* obj = cam.doska2.assemble(p_main, last, chunk_pos);
        if(obj->chunk.lines.empty() && obj->chunk.objects.empty()) {
            delete obj;
        }else if(obj->chunk.lines.empty() && obj->chunk.objects.size() == 1){
            isChunk = false;
            resizing = obj->chunk.objects[0];
            delete obj;
        }else {
            isChunk = true;
            resizing = obj;
        }
        return false;
    }else{
        delete resizing;
        return true;
    }
}
void Resizer::render(){
    if(resizing == nullptr){
        cam.drawRect((p_main - cam.pos).toFlo(), (last - p_main).toFlo());
    }else{

    }

}