//
// Created by Matvey on 29.03.2022.
//

#include "ChunkObject.h"
#include "../../view/Camera.h"
void ChunkObject::render(Camera& cam, const Vector2& c_pos){
//    rotate(M_PI / 60);

    chunk.render(cam, c_pos + center - Vector2(size).rotateRet(ang));
}
void ChunkObject::rotate(const Vector2& _ang){
    Square::rotate(_ang);

    for(auto& line: chunk.lines){
        line.start.rotate(_ang);
        line.end.rotate(_ang);
    }
    for(auto obj: chunk.objects){
        obj->center.rotate(_ang);
        obj->rotate(_ang);
    }
}
Object* ChunkObject::lightCopy() {
    auto* obj = new ChunkObject;
    obj->center = this->center;
    obj->size = this->size;
    obj->ang = this->ang;
    for(Line& l: chunk.lines)
        obj->chunk.lines.push_back(l);
    for(auto o: chunk.objects)
        obj->chunk.objects.push_back(o->lightCopy());
    return obj;
}
void ChunkObject::resize(const Vector2 &d_size) {
    Square::resize(d_size);
    for(Line& l: chunk.lines){
        Vector2 st = l.start;
        st.rotateBack(ang);
//        st.set(st.x *)
    }
}
