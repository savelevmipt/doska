#include <iostream>
#include "view/Camera.h"
int main(int argc, char** argv) {
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER)){
        std::cout << "Error initialising\n";
        return 1;
    }
    SDL_Window* window =
            SDL_CreateWindow("Doska",
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
    camera.width = 1280;
    camera.height = 720;

    SDL_Event event;
    bool running = true;
    while(running){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                running = false;
                break;
            case SDL_WINDOWEVENT:
                switch (event.window.type){
                    case SDL_WINDOWEVENT_RESIZED:
                        camera.width = event.window.data1;
                        camera.height = event.window.data2;
                        break;
                }
                break;
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
