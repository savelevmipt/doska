//
// Created by Matvey on 12.03.2022.
//

#include "ChunkIterator.h"
ChunkIterator::ChunkIterator(ChunkNet& net):
net(net),
max_net(nullptr),
curr_net(nullptr){}

void ChunkIterator::setBounds(int ox, int oy, int w, int h){
    rect = {ox, oy, w, h};
    max_net_rect = net.normalize(rect);
    max_net = net.getContainerNode(max_net_rect);
    curr_net = max_net;
    cur_x = -1;
    cur_y = -1;
}
bool ChunkIterator::next(){
    if(!curr_net)
        return false;

    bool goDown = curr_net->chunk == nullptr;
    int px, py;
    int s;
    if(goDown){
        px = max_net_rect.ox;
        py = max_net_rect.oy;
        s = max_net_rect.w;
    }else{
        px = cur_x;
        py = cur_y;
        s = 1;
    }
    //TODO positions
    int pos = 0; //положение ребенка
    while(true){
        if(goDown){
            while(pos < NUM_CHUNKS && curr_net->ch[pos] == nullptr)
                pos++;// ищем существующего ребенка
            if(pos == NUM_CHUNKS) {//детей нет
                goDown = false;//разворачиваемся
            }else{
                curr_net = curr_net->ch[pos];//дети есть - переходим к ним
                if(curr_net->chunk != nullptr)//нашли чанк
                    return true;
                pos = 0;//продолжаем спуск
            }
        }else{
            if(curr_net == max_net) {//сказали выйти из верхнего узла - завершаем обход
                curr_net = nullptr;
                return false;
            }
            pos = curr_net->parent_idx + 1;// после подъема планируем спуститься в соседний узел
            curr_net = curr_net->parent;
            if(pos != NUM_CHUNKS)//соседние узлы не кончились, спускаемся
                goDown = true;
            //иначе продолжаем подниматься
        }
    }
}
Chunk* ChunkIterator::getChunk() const{
    return curr_net->chunk;
}
int ChunkIterator::getX() const{
    return cur_x;
}
int ChunkIterator::getY() const{
    return cur_y;
}