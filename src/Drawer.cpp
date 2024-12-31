#include "Drawer.h"

/* ### Private Member Functions ### */ 

Drawer::Drawer(size_t width, size_t height, size_t flags) {
        _w = width;
        _h = height;
        _flags = flags;

        SDL_CreateWindowAndRenderer(_w, _h, flags, &_window, &_renderer);
        SDL_Init(SDL_INIT_VIDEO);   // Need to initialize SDL on creation to draw correctly
}


/* ### Public Member Functions ### */ 

Drawer::~Drawer() {
    delete _drawerPtr;
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);
    SDL_Quit();
}