#include "main.h"

int main(void) {
    int width = 640;
    int height = 480;

    Drawer *drawer = Drawer::getInstance();

/*
    // SDL Setup
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    // Draw
    for(int i = 0; i < width; ++i)
        SDL_RenderDrawPoint(renderer, i, height/2);
    SDL_RenderPresent(renderer);

    // Exit
    while (1) {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
*/
    return 0;
}
