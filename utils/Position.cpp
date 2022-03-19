//
// Created by Matvey on 18.03.2022.
//

#include <cmath>
#include "Position.h"
IntPosition::IntPosition(int x, int y):x(x), y(y){}
IntPosition::IntPosition(const Vector2 &round_from): x((int)round_from.x), y((int)round_from.y){}
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


Position::Position(const IntPosition& intp, const Vector2& flop):intp(intp), flop(flop) {}
Position::Position(int x, int y, float fx, float fy):intp(x, y), flop(fx, fy) {}
void Position::floor(){
    auto dx = (int)std::floor(flop.x), dy = (int)std::floor(flop.y);
    intp += {dx,dy};
    flop -= {(double)dx, (double)dy};
}
void Position::ceil(){
    auto dx = (int)std::ceil(flop.x), dy = (int)std::ceil(flop.y);
    intp += {dx, dy};
    flop -= {(double)dx, (double)dy};
}
Vector2 Position::toFlo() const {
    return {intp.x + flop.x, intp.y + flop.y};
}
Position operator+(const Position& a, const Position& b){
    return {a.intp + b.intp, a.flop + b.flop};
}
Position operator-(const Position& a, const Position& b){
    return {a.intp - b.intp, a.flop - b.flop};
}
Position& operator+=(Position& a, const Position& b){
    a.intp += b.intp;
    a.flop += b.flop;
    return a;
}
Position& operator-=(Position& a, const Position& b){
    a.intp -= b.intp;
    a.flop -= b.flop;
    return a;
}
Position operator+(const Position& a, const Vector2& b){
    return {a.intp, a.flop + b};
}
Position operator-(const Position& a, const Vector2& b){
    return {a.intp, a.flop - b};
}
Position& operator+=(Position& a, const Vector2& b){
    a.flop += b;
    return a;
}
Position& operator-=(Position& a, const Vector2& b){
    a.flop -= b;
    return a;
}

Position operator+(const Position& a, const IntPosition& b){
    return {a.intp + b, a.flop};
}
Position operator-(const Position& a, const IntPosition& b){
    return {a.intp - b, a.flop};
}
Position& operator+=(Position& a, const IntPosition& b){
    a.intp += b;
    return a;
}
Position& operator-=(Position& a, const IntPosition& b){
    a.intp -= b;
    return a;
}