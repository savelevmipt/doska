//
// Created by Matvey on 18.03.2022.
//

#include <cmath>
#include "Position.h"
IntPosition::IntPosition(int x, int y):x(x), y(y){}
IntPosition operator+(IntPosition a, IntPosition b){
    return {a.x + b.x, a.y + b.y};
}
IntPosition operator-(IntPosition a, IntPosition b){
    return {a.x - b.x, a.y - b.y};
}
IntPosition& operator+=(IntPosition& a, IntPosition b){
    a.x += b.x;
    a.y += b.y;
    return a;
}
IntPosition& operator-=(IntPosition& a, IntPosition b){
    a.x -= b.x;
    a.y -= b.y;
    return a;
}


FloPosition::FloPosition(float x, float y):x(x), y(y) {}
FloPosition operator+(FloPosition a, FloPosition b){
    return {a.x + b.x, a.y + b.y};
}
FloPosition operator-(FloPosition a, FloPosition b){
    return {a.x - b.x, a.y - b.y};
}
FloPosition& operator+=(FloPosition& a, FloPosition b){
    a.x += b.x;
    a.y += b.y;
    return a;
}

FloPosition& operator-=(FloPosition& a, FloPosition b){
    a.x -= b.x;
    a.y -= b.y;
    return a;
}


Position::Position(IntPosition intp, FloPosition flop):intp(intp), flop(flop) {}
Position::Position(int x, int y, float fx, float fy):intp(x, y), flop(fx, fy) {}
void Position::norm(){
    auto dx = (int)std::floor(flop.x), dy = (int)std::floor(flop.y);
    intp += {dx,dy};
    flop -= {(float)dx, (float)dy};
}
Position operator+(Position a, Position b){
    return {a.intp + b.intp, a.flop + b.flop};
}
Position& operator+=(Position& a, Position b){
    a.intp += b.intp;
    a.flop += b.flop;
    return a;
}
