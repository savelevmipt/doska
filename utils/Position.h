//
// Created by Matvey on 18.03.2022.
//
#include <string>

#ifndef DOSKA_POSITION_H
#define DOSKA_POSITION_H
#include "Vector2.h"

//Структуры для простого обращения к позициям объектов
struct IntPosition{
    int x, y;
    IntPosition(int x, int y);
    IntPosition(const Vector2& round_from);

    std::string to_string() const;
};
IntPosition operator+(IntPosition a, IntPosition b);
IntPosition operator-(IntPosition a, IntPosition b);
IntPosition& operator+=(IntPosition& a, IntPosition b);
IntPosition& operator-=(IntPosition& a, IntPosition b);

/* Зачем четырехмерный вектор для обозначения координаты на плоскости?
 *
 * Все равно бы пришлось работать с позициями чанков, тут они уже заложены, как часть вектора.
 * Дробные части отвечают за позицию объекта внутри чанка
 *
 * цель - ассоциативность при больших значениях координат, лучше, чем у double. Хотя это и не нужно.
 *
 * Возможно, стоит заменить на просто вектор из двух doublе
 *
 * */

struct Position{
    Vector2 flop;
    IntPosition intp;

    Position();
    Position(const IntPosition& intp, const Vector2& flop);
    Position(int x, int y, double fx, double fy);
    void floor();
    void ceil();
    void div2();
    void buildRectWith(Position& oth);
    bool liesInside(const Position& rtp, const Position& lbp) const;
    Vector2 toFlo() const;
    std::string to_string() const;
};
Position operator+(const Position& a, const Position& b);
Position operator-(const Position& a, const Position& b);
Position& operator+=(Position& a, const Position& b);
Position& operator-=(Position& a, const Position& b);
Position operator+(const Position& a, const Vector2& b);
Position operator-(const Position& a, const Vector2& b);
Position& operator+=(Position& a, const Vector2& b);
Position& operator-=(Position& a, const Vector2& b);
Position operator+(const Position& a, const IntPosition& b);
Position operator-(const Position& a, const IntPosition& b);
Position& operator+=(Position& a, const IntPosition& b);
Position& operator-=(Position& a, const IntPosition& b);

#endif //DOSKA_POSITION_H
