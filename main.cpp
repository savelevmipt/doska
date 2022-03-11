#include <iostream>
#include <SDL.h>
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
    if(window == NULL){
        std::cout << "Error making window\n";
        return 1;
    }

    SDL_Surface* surf = SDL_GetWindowSurface(window);
    SDL_FillRect(surf, NULL, SDL_MapRGB(surf->format, 0, 255, 0));

    SDL_UpdateWindowSurface(window);

    SDL_Event event;
    bool running = true;
    while(running){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                running = false;
                break;
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
