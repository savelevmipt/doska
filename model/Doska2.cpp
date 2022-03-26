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
void Doska2::deleteVolume(const Position& begin, const Position& end){
    Position rtp = begin, lbp = end;
    lbp.buildRectWith(rtp);
    ChunkIterator iter = select(rtp + IntPosition(1, 1), lbp - IntPosition(1, 1));
    std::vector<IntPosition> chunk_to_delete;
    while(iter.next()){
        Chunk* c = iter.getChunk();
        Position p({iter.getX(), iter.getY()}, {0, 0});
        if(p.liesInside(rtp, lbp) && (p + IntPosition(1, 1)).liesInside(rtp, lbp)){
            chunk_to_delete.push_back(p.intp);
            continue;
        }
        for(int i = (int)c->lines.size() - 1; i >= 0; --i){
            Position p2 = p;
            p2.flop = c->lines[i].start;
            if(p2.liesInside(rtp, lbp)){
                c->lines.erase(c->lines.begin() + i);
                continue;
            }
            p2.flop = c->lines[i].end;
            p2.floor();
            if(p2.liesInside(rtp, lbp)){
                c->lines.erase(c->lines.begin() + i);
            }
        }
        if(c->lines.empty())
            chunk_to_delete.push_back(p.intp);
    }
    for(auto p : chunk_to_delete){
        Chunk* c = net.rmChunk(p.x, p.y);
        delete c;
    }
}