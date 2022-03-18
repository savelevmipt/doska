//
// Created by Matvey on 18.03.2022.
//

#ifndef DOSKA_CAMERA_H
#define DOSKA_CAMERA_H
#include "SDL.h"
#include "../utils/Position.h"
#include "../map/ChunkIterator.h"
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
public:
    Position pos; //координата точки доски, находящейся в центре экрана
    double scale; //количество пикселей экрана, находящиеся в 1 чанке (размер чанка - 1)
    int width, height; //ширина и высота экрана в пикселях

    ChunkNet net;

    ChunkIterator iter;

    /* Создание: создать обьект, подав renderer,
     * Установить поля width и height
     * по желанию установить scale и pos
     * */
    Camera(SDL_Renderer *renderer);

    //переместить камеру (подается перемещение мыши по экрану)
    void translate(int d_screen_x, int d_screen_y);
    //приблизить/отдалить камеру, сохраняя положение заданной точки доски на экране
    void zoom(int screen_x, int screen_y, double wheel);

    Position getPosition(int screen_x, int screen_y);

    //отрисовывает весь экран
    void renderAll();

    //отрисовывает линию
    void drawLine(const Position& start, const Vector2& delta);

};


#endif //DOSKA_CAMERA_H
