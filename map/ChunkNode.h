//
// Created by Matvey on 12.03.2022.
//
#ifndef DOSKA_CHUNKNET_H
#define DOSKA_CHUNKNET_H

#include "Chunk.h"
//ChunkRect - прямоугольный набор чанков
#define NUM_CHUNKS 4
struct ChunkRect{
    int ox, oy, w, h;
    //ненулевое ли пересечение двух наборов?
    bool intersects(ChunkRect oth) const{
        return (ox + w > oth.ox && oth.ox + oth.w > ox)
               && (oy + h > oth.oy && oth.oy + h > oy);
    }
};

/*
 * Элемент чанковой сетки
 *
 * Содержит таблицу из 4 дочерних элементов.
 * так же содержит родительский элемент и свою позицию в нем
 * Такая структура данных обеспечит любые запросы к базе чанков за O(log(w)), где w - ширина используемой области доски в чанках
 * Итерация будет происходить за O(N*log(w)), где N - количество видимых на экране чанков
 *
 * */
struct ChunkNode {
public:
    ChunkNode *ch[NUM_CHUNKS];

    ChunkNode *parent = nullptr;
    int parent_idx = -1;

    Chunk *chunk = nullptr;

    ChunkNode(){
        ch[0] = nullptr;
        ch[1] = nullptr;
        ch[2] = nullptr;
        ch[3] = nullptr;
    }

};


#endif //DOSKA_CHUNKNET_H
