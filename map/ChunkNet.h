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
    //Удалить только узел net, остальное удалено хозяевами
    ~ChunkNet();
    /* getNewChunk() - Найти 1 чанк по адресу (x, y) и вернуть его.
     * если его адрес отсутствует в сетке, то расширить сетку
     * если чанк еще не создан, то создать функцией make_new()
     * адреса чанков начинаются с (net_width, -net_width) и заполняют пространство до (net_width, net_width)
     */
     Chunk* getNewChunk(int x, int y, Chunk* make_new());

     /* getChunk() - Найти 1 чанк по адресу (x, y) и вернуть его.
      * или вернуть NULL, если чанк еще не был создан или его адрес отсутствует в сетке
      */
     Chunk* getChunk(int x, int y) const;

     /* rmChunk() - Удалить 1 чанк по адресу (x, y) и вернуть его.
      * или вернуть NULL, если чанк еще не был создан или его адрес отсутствует в сетке
      * */
     Chunk* rmChunk(int x, int y);

     /*getRect - возвращает область, которая адресуется net
      * преобразует net_width в ChunkRect;
      * */
     ChunkRect getRect() const;

     /*
      * free - удалить все чанки дерева - очистить сеть
      */
     void free(void delete_chunk(Chunk* chunk)) const;
private:
    //Расширить таблицу в 2 раза по каждой координате
    void tableExpand();
    //Сузить таблицу, до предела.
    void tryTableTruncate();
};


#endif //DOSKA_DOSKA_H
