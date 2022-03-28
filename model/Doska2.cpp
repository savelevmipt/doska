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
void Doska2::deleteVolume(const Position& begin, const Position& end){
    Position rtp = begin, lbp = end;
    lbp.buildRectWith(rtp);
    Position center = lbp + rtp;
    Vector2 size = (rtp - lbp).toFlo();
    ChunkIterator iter = select(rtp + IntPosition(1, 1), lbp - IntPosition(1, 1));
    std::vector<IntPosition> chunk_to_delete;
    while(iter.next()){
        Chunk* c = iter.getChunk();
        Position chunk({iter.getX(), iter.getY()}, {0, 0});
        if(chunk.liesInside(rtp, lbp) && (chunk + IntPosition(1, 1)).liesInside(rtp, lbp)){
            chunk_to_delete.push_back(chunk.intp);
            continue;
        }
        for(int i = (int)c->lines.size() - 1; i >= 0; --i){
            Line &l = c->lines[i];  //Технология трассировки лучей - пересекаем луч (линию) c квадратом
            Vector2 d = (l.end - l.start);
            Vector2 p = (center - chunk - chunk).toFlo() - l.start - l.start;
            if(d.x == 0 && fabs(p.x) > size.x || d.y == 0 && fabs(p.y) > size.y)
                continue;
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
            if(s1 < e1 && !(s1 < 0 && e1 < 0 || s1 > 2 && e1 > 2)){
                c->lines.erase(c->lines.begin() + i);
                continue;
            }
        }
        if(c->lines.empty())
            chunk_to_delete.push_back(chunk.intp);
    }
    for(auto p : chunk_to_delete){
        Chunk* c = net.rmChunk(p.x, p.y);
        delete c;
    }
}