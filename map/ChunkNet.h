//
// Created by Matvey on 12.03.2022.
//
#ifndef DOSKA_CHUNKNET_H
#define DOSKA_CHUNKNET_H

#include "Chunk.h"
/*
 * Элемент чанковой сетки
 *
 * Содержит правый верхний - [0], правый нижний - [1], левый нижний - [2], левый верхний - [3] под-элементы сетки
 * или сам чанк
 * так же содержит родительский элемент
 * Такая структура данных обеспечит любые запросы к базе чанков за O(log(w)), где w - ширина используемой области доски в чанках
 * Итерация будет происходить за O(log(w) + N*log(N)), где N - количество видимых на экране чанков
 * */
struct ChunkNet {
public:
    ChunkNet *ch[4];

    ChunkNet *parent = nullptr;
    int parent_idx = -1;

    Chunk *chunk = nullptr;

    ChunkNet(){
        ch[0] = nullptr;
        ch[1] = nullptr;
        ch[2] = nullptr;
        ch[3] = nullptr;
    }
};


#endif //DOSKA_CHUNKNET_H
