//
// Created by Matvey on 12.03.2022.
//
#ifndef DOSKA_CHUNKNET_H
#define DOSKA_CHUNKNET_H

class Chunk;

//ChunkRect - прямоугольный набор чанков
#define NUM_CHUNKS 4
struct ChunkRect{
    int ox, oy, w, h;

    //ненулевое ли пересечение двух наборов?
    bool intersects(ChunkRect oth) const;
    bool contains(int x, int y) const;
    // Далее для правильных квадратных наборов (какими могут быть ChunkNode)
    // Находит набор родителя из набора ребенка
    void toParent(int parent_idx);
    // Находит набор ребенка
    void toChild(int child_id);
    // Находит номер ребенка по координатам
    // -1, если x, y не содержатся в rect
    int getChildIdx(int x, int y) const;
};

/*
 * Элемент чанковой сетки
 *
 * Содержит таблицу из 4 дочерних элементов.
 * 3 | 0
 * --+--
 * 2 | 1
 *
 * так же содержит родительский элемент и свою позицию в нем
 * Такая структура данных обеспечит любые запросы к базе чанков за O(log(w)), где w - ширина используемой области доски в чанках
 * Итерация будет происходить за O(log(w) + N), где N - количество видимых на экране, уже созданных чанков
 *
 * */

struct ChunkNode {
public:
    ChunkNode *ch[NUM_CHUNKS];

    ChunkNode *parent = nullptr;
    int parent_idx = -1;

    Chunk *chunk = nullptr;

    ChunkNode(int parent_idx, ChunkNode* parent);
    void setPar(int parent_idx, ChunkNode* parent);
};


#endif //DOSKA_CHUNKNET_H
