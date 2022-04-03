//
// Created by Matvey on 29.03.2022.
//

#include "Resizer.h"
#include "../view/Camera.h"
Resizer::Resizer(Camera& _cam):
        Selector(_cam),
        resizing(nullptr),
        isChunk(false),
        active_mod(RESIZER_SELECTING),
        chunk_pos(0, 0){}
Resizer::~Resizer() {
    delete resizing;
}
void Resizer::begin(const Position& start){
    p_main = start;
    last = start;
    if(resizing != nullptr){
        Square sq;
        Vector2 click = (start - chunk_pos).toFlo();

        sq.center = resizing->center +
                 Vector2(resizing->size.x + 25 / cam.scale, 0)
                .rotateRet(resizing->ang);
        sq.size = Vector2(1, 1) * (5 / cam.scale);
        sq.ang = resizing->ang;
        if(sq.containsDot(click)){
            active_mod = RESIZER_ROTATING;
            return;
        }

        sq.center = resizing->center;
        sq.size = resizing->size;
        sq.ang = resizing->ang;
        if(sq.containsDot(click)){
            active_mod = RESIZER_MOVING;
            return;
        }

        active_mod = RESIZER_SELECTING;
        releaseObj();
    }else{
        active_mod = RESIZER_SELECTING;
    }
}
void Resizer::update(const Position& curr){

    if(resizing != nullptr){
        if(active_mod == RESIZER_ROTATING) {
            last = curr;
            Vector2 ang = (last - chunk_pos).toFlo() - resizing->center;
            Vector2 prev_ang = resizing->ang;
            prev_ang.y = -prev_ang.y;
            ang.rotate(prev_ang);
            ang.norm();
            resizing->rotate(ang);
        }else if(active_mod == RESIZER_MOVING){
            Vector2 delta = (curr - last).toFlo();
            last = curr;
            resizing->center += delta;
            Position pos(chunk_pos, resizing->center);
            pos.floor();
            chunk_pos = pos.intp;
            resizing->center = pos.flop;
        }
    }else{
        last = curr;
    }
}
bool Resizer::finish(){
    if(active_mod != RESIZER_SELECTING)
        return false;
    ChunkObject* obj = cam.doska2.assemble(p_main, last, chunk_pos);
    if(obj->chunk.lines.empty() && obj->chunk.objects.empty()) {
        delete obj;
        return true;
    }else if(obj->chunk.lines.empty() && obj->chunk.objects.size() == 1){
        isChunk = false;
        resizing = obj->chunk.objects[0];
        resizing->center += obj->center - obj->size;
        delete obj;
    }else {
        isChunk = true;
        resizing = obj;
    }
    return false;
}
void Resizer::render(){
    if(resizing == nullptr){
        if(active_mod == RESIZER_SELECTING)
            cam.drawRect((p_main - cam.pos).toFlo(), (last - p_main).toFlo());
    }else{
        Vector2 c_pos = -(cam.pos - chunk_pos).toFlo();
        Vector2 size = resizing->size;
        Vector2 ang = resizing->ang;
        Vector2 side(1, 1);
        side *= 5 / cam.scale;
        resizing->render(cam, c_pos);
        c_pos += resizing->center;
        cam.drawRect(c_pos, size, ang);
        cam.drawRect(c_pos + Vector2(size.x, size.y).rotateRet(ang), side, ang);
        cam.drawRect(c_pos + Vector2(size.x, -size.y).rotateRet(ang), side, ang);
        cam.drawRect(c_pos + Vector2(-size.x, -size.y).rotateRet(ang), side, ang);
        cam.drawRect(c_pos + Vector2(-size.x, size.y).rotateRet(ang), side, ang);
        cam.drawRect(c_pos + Vector2(size.x, 0).rotateRet(ang), side, ang);
        cam.drawRect(c_pos + Vector2(-size.x, 0).rotateRet(ang), side, ang);
        cam.drawRect(c_pos + Vector2(0, size.y).rotateRet(ang), side, ang);
        cam.drawRect(c_pos + Vector2(0, -size.y).rotateRet(ang), side, ang);
        cam.drawRect(c_pos + Vector2(size.x + 25 / cam.scale, 0).rotateRet(ang), side, ang);
    }
}
void Resizer::releaseObj(){
    if(isChunk)
        cam.doska2.disassemble((ChunkObject*)resizing, chunk_pos);
    else
        cam.doska2.addObject(resizing, chunk_pos);
    resizing = nullptr;
}
