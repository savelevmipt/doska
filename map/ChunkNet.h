//
// Created by Matvey on 12.03.2022.
//

#ifndef DOSKA_DOSKA_H
#define DOSKA_DOSKA_H

#include "ChunkNode.h"

class ChunkNet {
public:
    ChunkNode* net;
    int net_width; //Определение размера наибольшего чанка

    //Создать пустую сеть
    ChunkNet();

    /* getChunk() - Найти 1 чанк по адресу (x, y)
     * или вернуть NULL, если чанк еще не был создан или его адрес отсутствует в сетке
     * адреса чанков начинаются с (-net_width, -net_width) и заполняют пространство до (net_width, net_width)
     * выглядит бесполезно, поскольку есть эффективный итератор
     */
     ChunkNode* getChunk(int x, int y) const;
     /*
      * getRect - возвращает область, которая адресуется net
      * преобразует net_width в ChunkRect;
      * */
     ChunkRect getRect() const;

};


#endif //DOSKA_DOSKA_H
