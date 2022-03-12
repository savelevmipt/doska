//
// Created by Matvey on 12.03.2022.
//

#ifndef DOSKA_DOSKA_H
#define DOSKA_DOSKA_H

#include "ChunkNet.h"
//ChunkRect - прямоугольный набор чанков
struct ChunkRect{
    int ox, oy, w, h;
};
class Doska {
public:
    ChunkNet* net;
    int net_width; //Определение размера наибольшего чанка

    // getChunk() - Найти 1 чанк по адресу (x, y)
    // или вернуть NULL, если чанк еще не был создан или его адрес отсутствует в сетке
    // адреса чанков начинаются с (-net_width, -net_width) и заполняют пространство до (net_width, net_width)
    Chunk* getChunk(int x, int y);

};


#endif //DOSKA_DOSKA_H
