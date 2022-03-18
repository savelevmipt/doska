//
// Created by Matvey on 18.03.2022.
//

#ifndef DOSKA_CAMERA_H
#define DOSKA_CAMERA_H
#include "SDL.h"
#include "utils/Position.h"
#include "map/ChunkIterator.h"
/*
 * Структура, которая будет хранить все данные о доске и позицию камеры
 * Отрисовывает на экране элементы доски
 * */
struct Camera {
    /*
     * ось y: на доске - вверх, на экране - вниз,
     * это пораждает неочевидные знаки +- в формулах
     *
     * ось x: и на доске и на экране - вправо
     * */
    Position pos;
    double scale;
    int width, height;

    ChunkNet net;
    ChunkIterator iter;

    Camera(int width, int height);

    //переместить камеру (подается перемещение мыши по экрану)
    void translate(int d_screen_x, int d_screen_y);
    //приблизить/отдалить камеру, сохраняя положение заданной точки на экране
    void zoom(int screen_x, int screen_y, double wheel);

    void render();//TODO

};


#endif //DOSKA_CAMERA_H
