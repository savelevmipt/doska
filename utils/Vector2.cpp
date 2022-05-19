//
// Created by Matvey on 18.03.2022.
//

#include "Vector2.h"
Vector2::Vector2(const double ang) {
    angle(ang);
}
void Vector2::set(const Vector2& oth) {
    x = oth.x;
    y = oth.y;
}
void Vector2::set(double _x, double _y) {
    x = _x;
    y = _y;
}
void Vector2::angle(double angle) {
    x = cos(angle);
    y = sin(angle);
}
double Vector2::len2() const {
    return x * x + y * y;
}
double Vector2::len() const {
    return hypot(x, y);
}
double Vector2::scl(const Vector2& oth) const{
    return x * oth.x + y * oth.y;
}
double Vector2::vec(const Vector2& oth) const{
    return x * oth.y - y * oth.x;
}
void Vector2::rotateBack(const Vector2& ang) {
    double _x = this->x * ang.x + this->y * ang.y;
    double _y = this->y * ang.x - this->x * ang.y;
    this->x = _x;
    this->y = _y;
}
void Vector2::rotate(const Vector2& ang) {
    double _x = this->x * ang.x - this->y * ang.y;
    double _y = this->y * ang.x + this->x * ang.y;
    this->x = _x;
    this->y = _y;
}
void Vector2::rotate(double angle){
    rotate(Vector2(angle));
}
Vector2& Vector2::rotateRet(const Vector2 &ang) {
    rotate(ang);
    return *this;
}
void Vector2::norm() {
    double len = this->len();
    x /= len;
    y /= len;
}
Vector2 operator-(const Vector2& a) {
    return {-a.x, -a.y};
}
Vector2 operator+(const Vector2& a, const Vector2& b) {
    return {a.x + b.x, a.y + b.y};
}
Vector2 operator-(const Vector2& a, const Vector2& b) {
    return {a.x - b.x, a.y - b.y};
}
Vector2& operator+=(Vector2& a, const Vector2& b) {
    a.x += b.x;
    a.y += b.y;
    return a;
}
Vector2& operator-=(Vector2& a, const Vector2& b) {
    a.x -= b.x;
    a.y -= b.y;
    return a;
}
Vector2 operator*(const Vector2& a, double b) {
    return {a.x * b, a.y * b};
}
Vector2& operator*=(Vector2& a, double b) {
    a.x *= b;
    a.y *= b;
    return a;
}
double operator>>(const Vector2& a, const Vector2& b) {
    return hypot(a.x - b.x, a.y - b.y);
}

std::string Vector2::to_string() const {
    return std::to_string(x) + "$" + std::to_string(y) + "$";
}
