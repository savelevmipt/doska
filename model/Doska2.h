//
// Created by Matvey on 25.03.2022.
//

#ifndef DOSKA_DOSKA2_H
#define DOSKA_DOSKA2_H
#include "../map/ChunkIterator.h"
#include "Chunk.h"
/*
 * Doska - класс, абстрагированный от структуры дерева чанков и содержащий методы для работы с доской
 * множество методов для работы с доской в координатах доски
 */
class Doska2 {
   ChunkNet net;
public:
    /*
    * конструктор создает пустую таблицу
    */
   Doska2();

   //деструктор удаляет все чанки
   ~Doska2();

   ChunkIterator select(Position rtp, Position lbp);
   void addLine(const Position& begin, const Position& end);
   void deleteVolume(Position begin, Position end);
};


#endif //DOSKA_DOSKA2_H