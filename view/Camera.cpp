//
// Created by Matvey on 18.03.2022.
//

#include "Camera.h"
Camera::Camera(SDL_Renderer* renderer, Doska2& doska):
scale(500), cells(16), pixel_per_line(5), doska2(doska),
width(0), height(0), renderer(renderer), selector(nullptr){}

void Camera::zoom(int screen_x, int screen_y, double wheel){
    Vector2 screen(screen_x - width / 2., height / 2. - screen_y);
    Vector2 delta = screen * (1 / scale);

    scale *= 1 + wheel / 5; //5 - множитель скорости увеличения

    pos.flop += delta - screen * (1 / scale);
    pos.floor();
}

void Camera::setSize(int _width, int _height){
    width = _width;
    height = _height;
    half_scr.set(_width / 2., _height / 2.);
}

Position Camera::getPosition(int screen_x, int screen_y) const{
    Vector2 screen(screen_x, screen_y);
    screen -= half_scr;
    screen.y = -screen.y;
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
void Camera::drawRect(const Vector2& center, const Vector2& size, const Vector2& ang) const{
    SDL_FPoint points[5];
    Vector2 p;
    p = center + Vector2(size.x, size.y).rotateRet(ang);
    p *= scale;
    p.y = -p.y;
    p += half_scr;
    points[0] = SDL_FPoint{(float)p.x, (float)p.y};
    p = center + Vector2(size.x, -size.y).rotateRet(ang);
    p *= scale;
    p.y = -p.y;
    p += half_scr;
    points[1] = SDL_FPoint{(float)p.x, (float)p.y};
    p = center + Vector2(-size.x, -size.y).rotateRet(ang);
    p *= scale;
    p.y = -p.y;
    p += half_scr;
    points[2] = SDL_FPoint{(float)p.x, (float)p.y};
    p = center + Vector2(-size.x, size.y).rotateRet(ang);
    p *= scale;
    p.y = -p.y;
    p += half_scr;
    points[3] = SDL_FPoint{(float)p.x, (float)p.y};
    points[4] = points[0];
    SDL_RenderDrawLinesF(renderer, points, 5);
}
void Camera::drawCells(){
    double curr_cells = cells;
    while(scale < curr_cells * pixel_per_line && curr_cells != 1){
        curr_cells /= 2;
    }

    Vector2 hs = half_scr * (1 / scale);
    Vector2 start(pos.flop - hs); // start = floor(pos - hs) - pos
    start.set(floor(start.x), floor(start.y));
    start -= pos.flop;
    Vector2 end(pos.flop + hs);//end = ceil(pos + hs) - pos
    end.set(ceil(end.x), ceil(end.y));
    end -= pos.flop;
    Vector2 size = (end - start) * curr_cells;
    int size_x = (int)size.x;
    int size_y = (int)size.y;
    Vector2 x_delta(0, end.y - start.y);
    Vector2 y_delta(end.x - start.x, 0);
    for(int i = 0; i <= size_x; ++i)
        drawLine(start + Vector2(i / curr_cells, 0), x_delta);
    for(int i = 0; i <= size_y; ++i)
        drawLine(start + Vector2(0, i / curr_cells), y_delta);
}
void Camera::renderAll(){
    ChunkIterator iter = doska2.select(pos + half_scr * (1 / scale), pos - half_scr * (1 / scale));

    SDL_SetRenderDrawColor(renderer, 255,  255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    drawCells();
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    //отрисовка
    while(iter.next()){
        IntPosition curr = {iter.getX(), iter.getY()};
        Vector2 size(1, 1);
        //нарисуем квадрат для каждого чанка
        Vector2 c_s = -(pos - curr).toFlo();//координата начала чанка
        //drawRect(c_s + Vector2(1, 1) * 0.02, Vector2(1, 1) * 0.96);

        iter.getChunk()->render(*this, c_s);
    }

    if(selector != nullptr)
        selector->render();

    SDL_RenderPresent(renderer);
}
