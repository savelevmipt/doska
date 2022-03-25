//
// Created by Matvey on 12.03.2022.
//

#include "ChunkNet.h"

ChunkNet::ChunkNet():net_width(1){
    net = new ChunkNode(-1, nullptr);
}
ChunkNet::~ChunkNet(){
    delete net;
}
void ChunkNet::tableExpand(){
    net_width *= 2;
    ChunkNode *ch;
    for(int i = 0; i < NUM_CHUNKS; ++i){
        if(net->ch[i] != nullptr){
            int i2 = (i + 2) % NUM_CHUNKS;
            ch = new ChunkNode(i, net);
            net->ch[i]->setPar(i2, ch);
            ch->ch[i2] = net->ch[i];
            net->ch[i] = ch;
        }
    }
}
void ChunkNet::tryTableTruncate(){
    ChunkNode **nod;
    ChunkNode *n;
    bool canOnce = true;
    while(canOnce && net_width > 1){
        for(int i = 0; i < NUM_CHUNKS; ++i){
            if(net->ch[i] != nullptr){
                int i2 = (i + 2) % NUM_CHUNKS;
                nod = net->ch[i]->ch;
                for(int j = 0; j < NUM_CHUNKS; ++j){
                    if(j != i2)
                        canOnce &= nod[j] == nullptr;
                }
            }
        }
        if(canOnce){
            for(int i = 0; i < NUM_CHUNKS; ++i){
                n = net->ch[i];
                if(n == nullptr)
                    continue;
                int i2 = (i + 2) % NUM_CHUNKS;
                net->ch[i] = n->ch[i2];
                net->ch[i]->setPar(i, net);
                delete n;
            }
            net_width /= 2;
        }
    }
}
Chunk* ChunkNet::getNewChunk(int x, int y, Chunk* make_new()){
    ChunkRect rect = getRect();
    while(!rect.contains(x, y)) {
        tableExpand();
        rect = getRect();
    }
    ChunkNode* nod = net;
    while(true){
        if(rect.w == 1) {
            if(nod->chunk == nullptr)
                nod->chunk = make_new();
            return nod->chunk;
        }
        int id = rect.getChildIdx(x, y);
        if(id == -1)//невозможно, если нет багов
            return nullptr;
        if(nod->ch[id] == nullptr)
            nod->ch[id] = new ChunkNode(id, nod);
        rect.toChild(id);
        nod = nod->ch[id];
    }
}
Chunk* ChunkNet::getChunk(int x, int y) const{
    ChunkRect rect = getRect();
    if(!rect.contains(x, y))
        return nullptr;
    ChunkNode* nod = net;
    while(true){
        if(rect.w == 1)
            return nod->chunk;
        int id = rect.getChildIdx(x, y);
        if(id == -1 || nod->ch[id] == nullptr)
            return nullptr;
        rect.toChild(id);
        nod = nod->ch[id];
    }
}
Chunk* ChunkNet::rmChunk(int x, int y) {
    ChunkRect rect = getRect();
    if(!rect.contains(x, y))
        return nullptr;
    //Find the chunk
    ChunkNode* nod = net;
    while(true){
        if(rect.w == 1)
            break;
        int id = rect.getChildIdx(x, y);
        if(id == -1 || nod->ch[id] == nullptr)
            return nullptr;
        rect.toChild(id);
        nod = nod->ch[id];
    }
    //remove branch
    Chunk* toReturn = nod->chunk;
    bool hasNext;
    do{
        int id = nod->parent_idx;
        nod = nod->parent;
        delete nod->ch[id];
        nod->ch[id] = nullptr;
        if(nod == net)
            break;
        hasNext = true;
        for(auto & i : nod->ch){
            if(i != nullptr) {
                hasNext = false;
                break;
            }
        }
    }while(hasNext);
    //Truncate table
    if(nod == net || nod->parent == net)
        tryTableTruncate();
    return toReturn;
}
ChunkRect ChunkNet::getRect() const {
    return ChunkRect{-net_width, -net_width, 2 * net_width, 2 * net_width};
}

void freeNode(ChunkNode* node, void delete_chunk(Chunk* chunk)){
    if(node->chunk != nullptr)
        delete_chunk(node->chunk);
    else{
        for(auto & i : node->ch){
            if(i != nullptr){
                freeNode(i, delete_chunk);
                delete i;
            }
        }
    }
}
void ChunkNet::free(void delete_chunk(Chunk* chunk)) const{
    freeNode(net, delete_chunk);
    for(auto & i : net->ch)
        i = nullptr;
}