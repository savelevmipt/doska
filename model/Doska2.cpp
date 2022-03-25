//
// Created by Matvey on 25.03.2022.
//

#include "Doska2.h"
Doska2::Doska2() {}

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
void Doska2::deleteVolume(Position begin, Position end){

}