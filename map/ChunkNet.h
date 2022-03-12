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

    /* getChunk() - Найти 1 чанк по адресу (x, y)
     * или вернуть NULL, если чанк еще не был создан или его адрес отсутствует в сетке
     * адреса чанков начинаются с (-net_width, -net_width) и заполняют пространство до (net_width, net_width)
     * выглядит бесполезно, поскольку есть эффективный итератор
     */
     ChunkNode* getChunk(int x, int y);

    /* normalize - находит позицию наименьшего ChunkNode, содержащего rect
     * зависит от объекта ChunkNet
     * Адреса, не содержащиеся в net, игнорируются
     */
    ChunkRect normalize(ChunkRect rect) const;

    //getContainerNode - возвращает ChunkNode, соответствующий позиции,
    //возвращает NULL, если такой ChunkNode еще не был создан или его адрес отсутствует в сетке
    ChunkNode* getContainerNode(ChunkRect normalized);
};


#endif //DOSKA_DOSKA_H
