//
// Created by Matvey on 18.03.2022.
//

#include "Camera.h"
Camera::Camera(SDL_Renderer* renderer, Doska2& doska):
scale(500), doska2(doska),
width(0), height(0), renderer(renderer){}

void Camera::translate(int d_screen_x, int d_screen_y){
    pos.flop += Vector2(-d_screen_x, d_screen_y) * (1 / scale);
    pos.floor();
}
void Camera::zoom(int screen_x, int screen_y, double wheel){
    Vector2 screen(screen_x - width / 2., height / 2. - screen_y);
    Vector2 delta = screen * (1 / scale);

    scale *= pow(1.1, wheel);//1.1 - множитель скорости увеличения

    pos.flop += -screen * (1 / scale) + delta;
    pos.floor();
}

void Camera::setSize(int _width, int _height){
    width = _width;
    height = _height;
    half_scr.set(_width / 2., _height / 2.);
}

Position Camera::getPosition(int screen_x, int screen_y) const{
    Vector2 screen(screen_x - width / 2., height / 2. - screen_y);
    Position p({0, 0}, screen * (1 / scale));
    p += pos;
    p.floor();
    return p;
}

void Camera::drawLine(const Vector2& start, const Vector2& delta) {
    Vector2 start_fp = start * scale;//
    start_fp.y = -start_fp.y;
    start_fp += half_scr;
    Vector2 end_fp = delta * scale;
    end_fp.y = -end_fp.y;
    end_fp += start_fp;
    SDL_RenderDrawLineF(renderer, (float)start_fp.x, (float)start_fp.y, (float)end_fp.x, (float)end_fp.y);
}
void Camera::drawRect(const Vector2& start, const Vector2& delta){
    Vector2 start_fp = start * scale;//
    start_fp.y = -start_fp.y;
    start_fp += half_scr;
    Vector2 size = delta * scale;
    start_fp.y -= size.y;
    SDL_FRect rect{(float)start_fp.x, (float)start_fp.y, (float)size.x, (float)size.y};
    SDL_RenderDrawRectF(renderer, &rect);
}
void Camera::renderAll(){
    ChunkIterator iter = doska2.select(pos + half_scr * (1 / scale), pos - half_scr * (1 / scale));

    SDL_SetRenderDrawColor(renderer, 255,  255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    //отрисовка
    while(iter.next()){
        IntPosition curr = {iter.getX(), iter.getY()};
        Vector2 size(1, 1);
        //нарисуем квадрат для каждого чанка
        Vector2 c_s = -(pos - curr).toFlo();//координата начала чанка
        drawRect(c_s + size * 0.02, size * 0.96);

        //отрисуем линии
        Chunk* c = iter.getChunk();
        for(auto &l: c->lines)
            drawLine(c_s + l.start, l.end - l.start);
    }

    if(has_sel){
        drawRect((sel_start - pos).toFlo(), (sel_end - sel_start).toFlo());
    }

    SDL_RenderPresent(renderer);
}
