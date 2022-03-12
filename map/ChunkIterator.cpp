//
// Created by Matvey on 12.03.2022.
//

#include "ChunkIterator.h"
ChunkIterator::ChunkIterator(Doska& doska):
doska(doska),
max_net(nullptr),
curr_net(nullptr){}

void ChunkIterator::setBounds(int ox, int oy, int w, int h){
    this->rect = {ox, oy, w, h};
    //TODO
    //
    curr_net = max_net;
}
bool ChunkIterator::next(){
    if(!max_net)
        return false;
    //TODO
}
Chunk* ChunkIterator::getChunk(){
    return curr_net->chunk;
}
int ChunkIterator::getX(){
    return cur_x;
}
int ChunkIterator::getY(){
    return cur_y;
}