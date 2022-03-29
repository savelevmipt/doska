//
// Created by Matvey on 25.03.2022.
//

#include "Doska2.h"

Doska2::~Doska2(){
    net.free(Chunk_destructor);
}
ChunkIterator Doska2::select(Position rtp, Position lbp) {
    lbp.floor();
    rtp.ceil();
    IntPosition delta = rtp.intp - lbp.intp;
    ChunkIterator iter(net);
    iter.setBounds(lbp.intp.x, lbp.intp.y, delta.x, delta.y);
    return iter;
}
void Doska2::addLine(const Position& begin, const Position& end){
    Line l;
    l.start = begin.flop;
    l.end = (end - begin.intp).toFlo();

    Chunk* c = net.getNewChunk(begin.intp.x, begin.intp.y, Chunk_constructor);
    c->lines.push_back(l);
}
void Doska2::addObject(Object* object, const IntPosition& c_pos){
    Chunk* c = net.getNewChunk(c_pos.x, c_pos.y, Chunk_constructor);
    c->objects.push_back(object);
}
bool checkIntersect(Vector2 p, Vector2 d, Vector2 size){
    // пересекает отрезок (p, d) с прямоугольником, находящимся в начале координат
    // Если отрезок находится внутри прямоугольника, это считается пересечением
    if(d.x == 0 && fabs(p.x) > size.x || d.y == 0 && fabs(p.y) > size.y)
        return false;
    double s1, s2, e1, e2;
    double t1 = (p.x + size.x) / d.x;
    double t2 = (p.x - size.x) / d.x;
    s1 = fmin(t1, t2);
    e1 = fmax(t1, t2);
    t1 = (p.y + size.y) / d.y;
    t2 = (p.y - size.y) / d.y;
    s2 = fmin(t1, t2);
    e2 = fmax(t1, t2);

    s1 = fmax(s1, s2);
    e1 = fmin(e1, e2);
    return s1 < e1 && !(s1 < 0 && e1 < 0 || s1 > 1 && e1 > 1);
}
ChunkObject* Doska2::assemble(const Position& begin, const Position& end, IntPosition& chunk_to_save){
    Position rtp = begin, lbp = end;
    lbp.buildRectWith(rtp);
    Position center = lbp + rtp;
    center.div2();
    chunk_to_save = center.intp;
    Vector2 size = (rtp - lbp).toFlo() * 0.5;
    ChunkIterator iter = select(rtp + IntPosition(1, 1), lbp - IntPosition(1, 1));
    std::vector<IntPosition> chunk_to_delete;
    auto* obj = new ChunkObject;
    obj->center = center.flop;
    obj->size = size;
    while(iter.next()){
        Chunk* c = iter.getChunk();
        Position chunk({iter.getX(), iter.getY()}, {0, 0});
        if(chunk.liesInside(rtp, lbp) && (chunk + IntPosition(1, 1)).liesInside(rtp, lbp)){
            chunk_to_delete.push_back(chunk.intp);
            continue;
        }
        Vector2 chunk_pos = (center - chunk).toFlo();
        for(int i = (int)c->lines.size() - 1; i >= 0; --i){
            Line &l = c->lines[i];  //Технология трассировки лучей - пересекаем луч (линию) c квадратом
            Vector2 d = l.end - l.start;
            Vector2 p = chunk_pos - l.start;
            if(checkIntersect(p, d, size)) {
                l.start -= chunk_pos - obj->size;
                l.end -= chunk_pos - obj->size;
                obj->chunk.lines.push_back(l);
                c->lines.erase(c->lines.begin() + i);
            }
        }
        for(int i = (int)c->objects.size() - 1; i >= 0; --i){
            Object* o = c->objects[i];
            Vector2 ct = chunk_pos - o->center;

            Vector2 cd = ct;
            cd.rotateBack(o->ang);
            //Проверить пересечения квадратов
            if(fabs(cd.x) < o->size.x && fabs(cd.y) < o->size.y ||
                    checkIntersect(ct - Vector2(o->size.x,  o->size.y).rotateRet(o->ang), Vector2(0,-2 * o->size.y).rotateRet(o->ang), size) ||
                    checkIntersect(ct - Vector2(o->size.x, -o->size.y).rotateRet(o->ang), Vector2(-2 * o->size.x,0).rotateRet(o->ang), size) ||
                    checkIntersect(ct - Vector2(-o->size.x,-o->size.y).rotateRet(o->ang), Vector2(0, 2 * o->size.y).rotateRet(o->ang), size) ||
                    checkIntersect(ct - Vector2(-o->size.x, o->size.y).rotateRet(o->ang), Vector2(2 * o->size.x, 0).rotateRet(o->ang), size)){
                o->center -= chunk_pos - obj->size;
                obj->chunk.objects.push_back(o);
                c->objects.erase(c->objects.begin() + i);
            }
        }
        if(c->lines.empty() && c->objects.empty())
            chunk_to_delete.push_back(chunk.intp);
    }
    for(auto p : chunk_to_delete){
        Chunk* c = net.rmChunk(p.x, p.y);
        delete c;
    }
    return obj;
}
void Doska2::disassemble(ChunkObject *obj, const IntPosition &chunk_at) {
    Vector2 ch_start = obj->center - Vector2(obj->size).rotateRet(obj->ang);
    for(Line& l: obj->chunk.lines){
        Position p1(chunk_at, ch_start + l.start);
        p1.floor();
        Position p2(chunk_at, ch_start + l.end);
        p2.floor();
        addLine(p1, p2);
    }
    for(Object* o: obj->chunk.objects){
        o->center += ch_start;
        addObject(o, chunk_at);
    }
    delete obj;
}