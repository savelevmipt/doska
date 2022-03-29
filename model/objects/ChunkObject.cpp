//
// Created by Matvey on 29.03.2022.
//

#include "ChunkObject.h"
#include "../../view/Camera.h"
void ChunkObject::render(Camera& cam, const Vector2& c_pos){
    rotate(M_PI / 60);


    cam.drawRect(c_pos + center, size, ang);

    Vector2 chunk_pos = c_pos + center - Vector2(size).rotateRet(ang);
    chunk.render(cam, chunk_pos);
}
void ChunkObject::rotate(const Vector2& _ang){
    ang.rotate(_ang);
    for(auto& line: chunk.lines){
        line.start.rotate(_ang);
        line.end.rotate(_ang);
    }
    for(auto* obj: chunk.objects){
        obj->center.rotate(_ang);
        obj->rotate(_ang);
    }
}
ChunkObject::~ChunkObject() noexcept = default;
Object* ChunkObject::lightCopy() {
    ChunkObject* obj = new ChunkObject;
    obj->center = this->center;
    obj->size = this->size;
    obj->ang = this->ang;
    for(Line& l: chunk.lines)
        obj->chunk.lines.push_back(l);
    for(Object* o: chunk.objects)
        obj->chunk.objects.push_back(o->lightCopy());
    return obj;
}
