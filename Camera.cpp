//
// Created by Matvey on 18.03.2022.
//

#include "Camera.h"
Camera::Camera(int width, int height):
scale(100), net(), iter(net),
pos(0, 0, 0, 0),
width(width), height(height){}

void Camera::translate(int d_screen_x, int d_screen_y){
    auto dx = (float)(d_screen_x / scale), dy = (float)(d_screen_y / scale);
    pos.flop += {-dx, dy};
    pos.norm();
}
void Camera::zoom(int screen_x, int screen_y, double wheel){
    double deltaX = screen_x / scale, deltaY = screen_y / scale;
    scale /= wheel;
    pos.flop += {(float)(-screen_x / scale + deltaX),
                 (float)(screen_y / scale + deltaY)};
    pos.norm();
}
void Camera::render(){
    //TODO
}