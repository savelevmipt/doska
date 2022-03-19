//
// Created by Matvey on 12.03.2022.
//

#ifndef DOSKA_CHUNKITERATOR_H
#define DOSKA_CHUNKITERATOR_H
#include "ChunkNet.h"
/*Итератор по набору чанков
  Набор чанков задается прямоугольником (ox, oy, w, h)

  Использование:

  ChunkIterator it(doska);
  it.setBounds(0, 0, 4, 4);
  while(it.next()){
    Chunk* c = it.getChunk();
    int x = it.getX(), y = it.getY();
    //do something
  }

  проитерировались по всем ненулевым чанкам в области
  порядок итерирования - сумасшедший - не полагаться на него
*/
class ChunkIterator {
private:
    //неизменное поле
    ChunkNet& net;

    //поля одного цикла (меняются раз в цикл)
    ChunkRect rect;
    //меняются каждую итерацию
    ChunkNode* curr_net;
    ChunkRect curr_rect;
public:
    //net - неизменное поле итератора
    ChunkIterator(ChunkNet& net);
    //setBounds() - Задать набор чанков и приготовить итератор
    void setBounds(int ox, int oy, int w, int h);
    //перезапустить итератор на том же наборе
    void reset();
    //получить следующий ненулевой элемент curr_net и его координаты
    //возвращает true, если следующий элемент найден
    //если элемент не найден, то зануляем curr_net и возвращаем false
    bool next();
    //getterы
    Chunk* getChunk() const;
    int getX() const;
    int getY() const;

    ///////////////////
    // Для итерирования по всему дереву, не полько по чанкам
    bool _goDown;
    bool nextNode();
    int getW() const;
    int getH() const;
};


#endif //DOSKA_CHUNKITERATOR_H
