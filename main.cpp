#include <iostream>
#include "view/Camera.h"
#include "MouseState.h"
int main(int argc, char** argv) {
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER)){
        std::cout << "Error initialising\n";
        return 1;
    }
    SDL_Window* window = SDL_CreateWindow("Doska",
                             SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED,
                             1280, 720,
                             SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
    if(window == nullptr){
        std::cout << "Error making window\n";
        return 1;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    Camera camera(renderer);
    camera.setSize(1280, 720);

    MouseState state;

    SDL_Event event;
    bool running = true;
    while(running){
        if(!SDL_PollEvent(&event))
            camera.renderAll();
        switch(event.type){
            case SDL_QUIT:
                running = false;
                break;
            case SDL_WINDOWEVENT:
                switch (event.window.type){
                    case SDL_WINDOWEVENT_RESIZED:
                        camera.setSize(event.window.data1, event.window.data2);
                        break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                state.x = event.motion.x;
                state.y = event.motion.y;
                state.has_last_state = true;
                if(event.button.button == 1) {
                    state.left_pressed = true;
                }else if(event.button.button == 3) {
                    state.right_pressed = true;
                    Position p = camera.getPosition(state.x, state.y);
                    Chunk* c = camera.net.getChunk(p.intp.x, p.intp.y);
                    if(c == nullptr){
                        camera.net.getNewChunk(p.intp.x, p.intp.y, Chunk_constructor);
                    }else{
                        camera.net.rmChunk(p.intp.x, p.intp.y);
                        delete c;
                    }
                }
                break;
            case SDL_MOUSEBUTTONUP:
                state.x = event.motion.x;
                state.y = event.motion.y;
                state.has_last_state = true;
                if(event.button.button == 1)
                    state.left_pressed = false;
                else if(event.button.button == 3)
                    state.right_pressed = false;
                break;
            case SDL_MOUSEWHEEL:
                camera.zoom(state.x, state.y, event.wheel.preciseY);
                break;
            case SDL_MOUSEMOTION:
                int dx = event.motion.x - state.x, dy = event.motion.y - state.y;
                state.x = event.motion.x;
                state.y = event.motion.y;
                if(!state.has_last_state) {
                    state.has_last_state = true;
                    break;
                }
                if(state.left_pressed)
                    camera.translate(dx, dy);
                break;
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
