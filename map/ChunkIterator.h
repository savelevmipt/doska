//
// Created by Matvey on 12.03.2022.
//

#ifndef DOSKA_CHUNKITERATOR_H
#define DOSKA_CHUNKITERATOR_H
#include "Doska.h"
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
    Doska& doska;

    //поля одного цикла (меняются раз в цикл)
    ChunkRect rect;
    ChunkNet* max_net;//наименьший элемент сетки, содержащий в себе все чанки набора

    //меняются каждую итерацию
    ChunkNet* curr_net;
    int cur_x, cur_y;
public:
    //doska - неизменное поле итератора
    ChunkIterator(Doska& doska);
    //setBounds() - Задать набор чанков
    //и найти max_net, curr_net = NULL
    void setBounds(int ox, int oy, int w, int h);

    //получить следующий ненулевой элемент cur_net и его координаты
    //возвращает true, если следующий элемент найден
    //если элемент не найден, то зануляем max_net и возвращаем false
    bool next();
    //getterы
    Chunk* getChunk();
    int getX();
    int getY();
};


#endif //DOSKA_CHUNKITERATOR_H
