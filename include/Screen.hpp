#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <math.h>

#include <eigen3/Eigen/Dense>
#include <SDL2/SDL.h>

using Eigen::Matrix4d;
using Eigen::Vector4d;
using Eigen::Vector3d;

class Screen {
    private:
        SDL_Window* _win;
        SDL_Renderer* _render;

        double _w;  // Screen width (in pixel)
        double _h;  // Screen height (in pixel)
        double _a;  // Aspect ratio (h/w)
        double _fov; // Field of view (in radians)

        double _zClose; // min view distance
        double _zFar; // max view distance

    public:
        Screen(double width, double height, double fov, double minZ, double maxZ) {
            _w = width;
            _h = height;
            _a = _h / _w;
            _fov = fov;

            _zClose = minZ;
            _zFar = maxZ;

            SDL_CreateWindowAndRenderer(_w, _h, 0, &_win, &_render);
        }

        /* ##### Function Headers ##### */
        Vector4d scaledProject(Vector3d);
        SDL_Renderer *getRenderer();
        SDL_Window *getWindow();
    private:
        Vector4d project(Vector3d);
        Vector4d scale(Vector4d);

};

    //* ##### Member Functions ##### *//

    // Handles converting 3d positions of points onto the screen
    Vector4d Screen::scaledProject(Vector3d p) {
        return scale(project(p));
    }

    // Projects the given Vector3d onto the screen with a homogeneous matrix transformation and returns the results as a Vector4d
    Vector4d Screen::project(Vector3d p) {
        Vector4d hP = Vector4d(p[0], p[1], p[2], 1); 
        Matrix4d proj;  // Screen projection matrix
        proj << _a/tan(_fov/2), 0, 0, 0,
                0, 1/tan(_fov/2), 0, 0,
                0, 0, _zFar/(_zFar - _zClose), 1,
                0, 0, (-_zFar)*(_zClose)/(_zFar - _zClose), 0;

        return proj*hP;
    }

    // Scales the given vectors to appropriate size to fill the screen after projection
    Vector4d Screen::scale(Vector4d p) {
        Vector4d v = p;
        v += Vector4d(1, 1, 0, 0);
        v[0] *= 0.5*_w;
        v[1] *= 0.5*_h;

        return v;
    }

    // Returns the pointer to the renderer associated with the Screen
    SDL_Renderer *Screen::getRenderer() {
        return _render;
    }

    // Returns the pointer to the window associated with the Screen
    SDL_Window *Screen::getWindow() {
        return _win;
    }

#endif