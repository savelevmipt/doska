//
// Created by Matvey on 18.03.2022.
//

#ifndef DOSKA_VECTOR2_H
#define DOSKA_VECTOR2_H

#include <cmath>
class Vector2
{
public:
    double x = 0, y = 0;
    Vector2()= default;
    Vector2(const Vector2& oth) = default;
    Vector2(double x, double y): x(x), y(y) {}
    Vector2(double angle);
    void set(const Vector2& oth);
    void set(double x, double y);
    void angle(double angle);
    double len2() const;
    double len() const;
    double scl(const Vector2& oth) const;
    double vec(const Vector2& oth) const;
    void rotateBack(const Vector2& ang);
    void rotate(const Vector2& ang);
    void rotate(double angle);
    void norm();
    friend Vector2 operator-(const Vector2& a);
};
Vector2 operator+(const Vector2& a, const Vector2& b);
Vector2 operator-(const Vector2& a, const Vector2& b);
Vector2& operator+=(Vector2& a, const Vector2& b);
Vector2& operator-=(Vector2& a, const Vector2& b);
Vector2 operator*(const Vector2& a, double b);
Vector2& operator*=(Vector2& a, double b);
double operator>>(const Vector2& a, const Vector2& b);

#endif //DOSKA_VECTOR2_H
