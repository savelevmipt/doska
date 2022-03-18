//
// Created by Matvey on 18.03.2022.
//

#include "Camera.h"
Camera::Camera(SDL_Renderer* renderer):
scale(100), net(), iter(net),
pos(0, 0, 0, 0),
width(0), height(0), renderer(renderer){}

void Camera::translate(int d_screen_x, int d_screen_y){
    pos.flop += Vector2(-d_screen_x, d_screen_y) * (1 / scale);
    pos.floor();
}
void Camera::zoom(int screen_x, int screen_y, double wheel){
    Vector2 screen(width / 2. - screen_x, screen_y - height / 2.);
    Vector2 delta = screen * (1 / scale);

    scale /= wheel;

    pos.flop += screen * (1 / scale) + delta;
    pos.floor();
}

Position Camera::getPosition(int screen_x, int screen_y){
    Vector2 screen(width / 2. - screen_x, screen_y - height / 2.);
    //TODO
}

void Camera::drawLine(const Position& start, const Vector2& delta) {
    Vector2 p = (start - pos).toFlo();

    Vector2 start_fp = p * scale;
    Vector2 end_fp = start_fp + delta * scale;
    SDL_RenderDrawLineF(renderer, (float)start_fp.x, (float)height - (float)start_fp.y, (float)end_fp.x, (float)height - (float)end_fp.y);
}

void Camera::renderAll(){
    {//инициализация итератора
        Vector2 half_screen = Vector2(width / 2., height / 2.) * (1 / scale);

        Position lbp = pos - half_screen;//left bottom corner position
        Position rtp = pos + half_screen;//right top corner position

        lbp.ceil();
        rtp.ceil();
        IntPosition delta = rtp.intp - lbp.intp;

        iter.setBounds(lbp.intp.x, lbp.intp.y, delta.x, delta.y);
    }

    //отрисовка
    while(iter.next()){
        Chunk* c = iter.getChunk();
        IntPosition curr = {iter.getX(), iter.getY()};

        //нарисуем просто квадрат для каждого чанка
        Position start(curr, Vector2(0.2, 0.2));
        Vector2 end(0.2, 0.8);
        drawLine(start, end);

        start.flop.set(end);
        end.set(0.8, 0.8);
        drawLine(start, end);

        start.flop.set(end);
        end.set(0.8, 0.2);
        drawLine(start, end);

        start.flop.set(end);
        end.set(0.2, 0.2);
        drawLine(start, end);
    }
}
