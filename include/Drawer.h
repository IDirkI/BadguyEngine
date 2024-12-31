#ifndef DRAWER_H
#define DRAWER_H

#include <SDL2/SDL.h>

#define WIDTH 640
#define HEIGHT 480

class Drawer {
    size_t _w;
    size_t _h;

    size_t _flags;
    
    SDL_Window      *_window;
    SDL_Renderer    *_renderer;

    static Drawer *_drawerPtr;

                         
  public:
  Drawer(size_t width, size_t height, size_t flags);
    Drawer(const Drawer& drawer) = delete;   
    ~Drawer();

    static Drawer* getInstance(size_t width = WIDTH, size_t height = HEIGHT, size_t flags = 0) {
        if(_drawerPtr == nullptr) {
            _drawerPtr = new Drawer(width, height, flags);
        }

        return _drawerPtr;
    }

    
};

Drawer *Drawer::_drawerPtr = nullptr;

#endif