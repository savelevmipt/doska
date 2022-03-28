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
   Doska2() = default;

   //деструктор удаляет все чанки
   ~Doska2();
   //возвращяет итератор по набору задетых чанков, rtp, lbp - правый верхний и левый нижний углы прамоугольника
   //если это не так, воспользуйтесь методом buildRectWith класса Position
   ChunkIterator select(Position rtp, Position lbp);
   //Добавить линию по координатам
   void addLine(const Position& begin, const Position& end);

   void addObject(Object* obj, const IntPosition& chunk);
   //Удалить все объекты, пересекающиеся с данным прямоугольником
   void deleteVolume(const Position& begin, const Position& end);
};


#endif //DOSKA_DOSKA2_H
