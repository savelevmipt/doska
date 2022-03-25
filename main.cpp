#include <iostream>
#include "view/Camera.h"
#include "MouseState.h"
int main(int argc, char** argv) {
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_HAPTIC)){
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

    Doska2 doska;
    Camera camera(renderer, doska);

    camera.setSize(1280, 720);

    MouseState state;

    SDL_Event event;
    bool running = true;
    while(running){
        while(!SDL_PollEvent(&event))
            camera.renderAll();

        switch(event.type){
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN: {
                switch(event.key.keysym.scancode){
                    case SDL_SCANCODE_D: {
                        state.key_state = STATE_DRAW;
                        break;
                    }
                    case SDL_SCANCODE_A: {
                        state.key_state = STATE_MOVE;
                        break;
                    }
                    default:
                        break;
                }
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
                state.x = event.motion.x;
                state.y = event.motion.y;
                state.st_x = state.x;
                state.st_y = state.y;
                state.has_last_state = true;
                if(event.button.button == 1) {
                    state.left_pressed = true;
                }
                break;
            case SDL_MOUSEBUTTONUP: {
                state.has_last_state = true;
                if (event.button.button == 1)
                    state.left_pressed = false;
                break;
            }
            case SDL_MOUSEWHEEL:
                camera.zoom(state.x, state.y, event.wheel.preciseY);
                break;
            case SDL_MOUSEMOTION: {
                int dx = event.motion.x - state.x, dy = event.motion.y - state.y;
                state.x = event.motion.x;
                state.y = event.motion.y;
                if (!state.has_last_state) {
                    state.has_last_state = true;
                    break;
                }
                if (state.left_pressed){
                    if(state.key_state == STATE_MOVE)
                        camera.translate(dx, dy);
                    else if(state.key_state == STATE_DRAW){
                        doska.addLine(camera.getPosition(state.x - dx, state.y - dy),
                                      camera.getPosition(state.x, state.y));
                    }
                }
                break;
            }
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
