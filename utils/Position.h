//
// Created by Matvey on 18.03.2022.
//

#ifndef DOSKA_POSITION_H
#define DOSKA_POSITION_H
//Структуры для простого обращения с позициями объектов
struct IntPosition{
    int x, y;
    IntPosition(int x, int y);
};
IntPosition operator+(IntPosition a, IntPosition b);
IntPosition operator-(IntPosition a, IntPosition b);
IntPosition& operator+=(IntPosition& a, IntPosition b);
IntPosition& operator-=(IntPosition& a, IntPosition b);
struct FloPosition {
    float x, y;
    FloPosition(float x, float y);
};
FloPosition operator+(FloPosition a, FloPosition b);
FloPosition operator-(FloPosition a, FloPosition b);
FloPosition& operator+=(FloPosition& a, FloPosition b);
FloPosition& operator-=(FloPosition& a, FloPosition b);

struct Position{
    IntPosition intp;
    FloPosition flop;
    Position(IntPosition intp, FloPosition flop);
    Position(int x, int y, float fx, float fy);
    void norm();
};
Position operator+(Position a, Position b);
Position& operator+=(Position& a, Position b);
#endif //DOSKA_POSITION_H
