//
// Created by Matvey on 18.03.2022.
//

#ifndef DOSKA_CAMERA_H
#define DOSKA_CAMERA_H
#include "SDL.h"
#include "../model/Doska2.h"
/*
 * Структура, которая будет хранить все данные о доске и позицию камеры
 * Отрисовывает на экране элементы доски
 *
 * ось y: на доске - вверх, на экране - вниз,
 * это пораждает неочевидные знаки +- в формулах
 *
 * ось x: и на доске и на экране - вправо
 * */
class Camera {
private:
    SDL_Renderer* renderer;

    Vector2 half_scr; // пол ширины и высоты
    int width, height; //ширина и высота экрана в пикселях
public:
    Position pos; //координата точки доски, находящейся в центре экрана
    double scale; //количество пикселей экрана, находящиеся в 1 чанке (размер чанка - 1)

    Doska2& doska2;

    /* Создание: создать обьект, подав renderer,
     * Установить size,
     * по желанию установить scale и pos
     * */
    Camera(SDL_Renderer *renderer, Doska2& doska);

    void setSize(int _width, int _height);

    //переместить камеру (подается перемещение мыши по экрану)
    void translate(int d_screen_x, int d_screen_y);
    //приблизить/отдалить камеру, сохраняя положение заданной точки доски на экране
    void zoom(int screen_x, int screen_y, double wheel);

    Position getPosition(int screen_x, int screen_y) const;

    //отрисовывает весь экран
    void renderAll();

    //отрисовывает линию, сдвинутую относительно центра экрана
    void drawLine(const Vector2& start, const Vector2& delta);

    void drawRect(const Vector2& start, const Vector2& size);
};


#endif //DOSKA_CAMERA_H
