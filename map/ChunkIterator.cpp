//
// Created by Matvey on 12.03.2022.
//

#include "ChunkIterator.h"
ChunkIterator::ChunkIterator(ChunkNet& net):
net(net),
curr_net(nullptr){}

void ChunkIterator::setBounds(int ox, int oy, int w, int h){
    rect = {ox, oy, w, h};
    reset();
}
void ChunkIterator::reset(){
    curr_rect = net.getRect();
    curr_net = net.net;

    _goDown = true;
}
bool ChunkIterator::next(){
    if(!curr_net)
        return false;

    bool goDown = curr_net->chunk == nullptr;

    int pos = 0; //положение ребенка
    while(true){
        if(goDown){
            ChunkRect r;
            pos--;
            while(true){
                pos++;
                if(pos == NUM_CHUNKS)
                    break;//прошли всех детей - завершаем цикл
                if(curr_net->ch[pos] == nullptr)
                    continue;// ребенка нет - ищем дальше
                r = curr_rect;
                r.toChild(pos);
                if(r.intersects(rect))
                    break;//найден пересекающийся ребенок
            }
            //ребенок не пересекается с заданным прямоугольником - ишем дальше
            if(pos == NUM_CHUNKS) {//детей нет
                goDown = false;//разворачиваемся
            }else{
                curr_net = curr_net->ch[pos];//дети есть - переходим к ним
                curr_rect = r;
                if(curr_net->chunk != nullptr)//нашли чанк
                    return true;
                pos = 0;//продолжаем спуск
            }
        }else{
            if(curr_net == net.net) {//сказали выйти из верхнего узла - завершаем обход
                curr_net = nullptr;
                return false;
            }
            pos = curr_net->parent_idx + 1;// после подъема планируем спуститься в соседний узел
            curr_rect.toParent(curr_net->parent_idx);
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
    return curr_rect.ox;
}
int ChunkIterator::getY() const{
    return curr_rect.oy;
}


bool ChunkIterator::nextNode(){
    if(!curr_net)
        return false;


    int pos = 0; //положение ребенка
    while(true){
        if(_goDown){
            ChunkRect r;
            pos--;
            while(true){
                pos++;
                if(pos == NUM_CHUNKS)
                    break;//прошли всех детей - завершаем цикл
                if(curr_net->ch[pos] == nullptr)
                    continue;// ребенка нет - ищем дальше
                r = curr_rect;
                r.toChild(pos);
                if(r.intersects(rect))
                    break;//найден пересекающийся ребенок
            }
            //ребенок не пересекается с заданным прямоугольником - ишем дальше
            if(pos == NUM_CHUNKS) {//детей нет
                _goDown = false;//разворачиваемся
            }else{
                curr_net = curr_net->ch[pos];//дети есть - переходим к ним
                curr_rect = r;
                if(curr_net->chunk != nullptr)//нашли чанк
                    _goDown = false;
                return true;
            }
        }else{
            if(curr_net == net.net) {//сказали выйти из верхнего узла - завершаем обход
                curr_net = nullptr;
                return false;
            }
            pos = curr_net->parent_idx + 1;// после подъема планируем спуститься в соседний узел
            curr_rect.toParent(curr_net->parent_idx);
            curr_net = curr_net->parent;
            if(pos != NUM_CHUNKS)//соседние узлы не кончились, спускаемся
                _goDown = true;
            //иначе продолжаем подниматься
        }
    }
}
int ChunkIterator::getW() const{
    return curr_rect.w;
}
int ChunkIterator::getH() const{
    return curr_rect.h;
}