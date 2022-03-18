//
// Created by Matvey on 12.03.2022.
//

#include "ChunkNet.h"

ChunkNet::ChunkNet():net_width(1){
    net = new ChunkNode;
}
ChunkNode* ChunkNet::getChunk(int x, int y) const{
    ChunkRect rect = getRect();
    if(!rect.contains(x, y))
        return nullptr;
    ChunkNode* nod = net;

    while(true){
        if(rect.w == 1)
            return nod;
        int id = rect.getChildIdx(x, y);
        if(id == -1)//невозможно, если нет багов
            return nullptr;
        rect.toChild(id);
        nod = nod->ch[id];
        if(nod == nullptr)
            return nullptr;
    }
}
ChunkRect ChunkNet::getRect() const {
    return ChunkRect{-net_width, -net_width, 2 * net_width, 2 * net_width};
}