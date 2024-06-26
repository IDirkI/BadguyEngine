#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <math.h>

#include <eigen3/Eigen/Dense>

#include "./Screen.hpp"

using Eigen::Vector3d;

class Camera {
    private:
        Vector3d _pos;
        Vector3d _dir; //norm = 1

        Screen *_screen;
        double _w;  // Screen width (in pixel)
        double _h;  // Screen height (in pixel)
        double _fov; // Field of view (in radians)

        double _zClose; // min view distance
        double _zFar; // max view distance

    public:
        Camera(Vector3d position = Vector3d(0, 0, 0), Vector3d direction  = Vector3d(0, 0, 1), double width = 640, double height = 480, double fov = M_PI/2, double minZ = 0.1, double maxZ = 1000 ) {
            _pos = position;
            _dir = direction;

            _w = width;
            _h = height;
            _fov = fov;

            _zClose = minZ;
            _zFar = maxZ;

            _screen = new Screen(_w, _h, _fov, _zClose, _zFar);
        }

        ~Camera() {
            delete(_screen);
        }

        /* ##### Function Headers ##### */
        Screen *getScreen();
};

    //* ##### Member Functions ##### *//

    // Returns the Screen associated of the camera
    Screen *Camera::getScreen() {
        return _screen;
    }

#endif