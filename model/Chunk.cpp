//
// Created by Matvey on 12.03.2022.
//

#include "Chunk.h"
#include "../view/Camera.h"
Chunk* Chunk_constructor(){
    return new Chunk();
}
void Chunk_destructor(Chunk* chunk){
    for(auto& obj: chunk->objects)
        delete obj;
    delete chunk;
}
void Chunk::render(Camera &cam, const Vector2 &c_pos) {
    //отрисуем линии
    for(auto &l: lines)
        cam.drawLine(c_pos + l.start, l.end - l.start);
    //Рисуем объекты
    for(auto* obj: objects)
        obj->render(cam, c_pos);
}