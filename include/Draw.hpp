#ifndef DRAW_HPP
#define DRAW_HPP

#include <math.h>
#include <iostream>
#include <queue>

#include <eigen3/Eigen/Dense>
#include <SDL2/SDL.h>

#include "./Structures/Shapes/Shape.hpp"
#include "./Structures/Polygon.hpp"
#include "./Structures/Mesh.hpp"
#include "./Color.hpp"

using std::queue;

using Eigen::Vector2d;
using Eigen::Vector4d;

class Draw {
    private:
        Screen *_screen;
        SDL_Renderer *_render;
        Color *_c;
    
    public:
        /* ##### Constructors ##### */
        Draw(Screen *screen) {
            _screen = screen;
            _render = _screen -> getRenderer();

            _c = new Color(255, 255, 255); // Set default color as white
            applyColor();
        }

        /* ##### Function Headers ##### */
        void changeColor(Color);
        void changeColor(int, int, int, int);
        void clean();
        void show();
        void drawPixel(Vector2d);
        void drawLine(Vector2d, Vector2d);
        void drawLine(Vector4d, Vector4d);
        void drawPolygon(Polygon);
        void drawMesh(Mesh);
        void drawShape(Shape *);
        void drawQueue(queue<Shape *> *, double);
    
    private:
        void applyColor(); // internal help function
};

    //* ##### Member Functions ##### *//

    // Changes the drawing color to the specified color
    void Draw::changeColor(Color color) {
        _c -> setR(color.r());
        _c -> setG(color.g());
        _c -> setB(color.b());
        _c -> setA(color.a());

        applyColor();
    }

    // Changes the drawing color to the specified color values
    void Draw::changeColor(int red, int green, int blue, int alpha) {
        assert(((0 <= red && red < 256) && (0 <= blue && blue < 256)) && ((0 <= green && green < 256) && (0 <= alpha && alpha < 256))); // TODO: Add proper error handling

        _c -> setR(red);
        _c -> setG(green);
        _c -> setB(blue);
        _c -> setA(alpha);

        applyColor();
    }

    // Applies the current color as the drawing color
    void Draw::applyColor() {
        SDL_SetRenderDrawColor(_render, _c -> r(), _c -> g(), _c -> b(), _c -> a());
    }

    // Updates the renderer with all the new drawings
    void Draw::clean() {
        SDL_SetRenderDrawColor(_render, 0, 0, 0, 255);
        SDL_RenderClear(_render);
        applyColor();
    }

    // Updates the renderer with all the new drawings
    void Draw::show() {
        SDL_RenderPresent(_render);
    }

    // Draws a pixel in the current drawing color at the specified point by the Vector2d
    void Draw::drawPixel(Vector2d pixel) {
        SDL_RenderDrawPoint(_render, pixel[0], pixel[1]);
    }

    // Draws a line between the given two Vector2d's
    void Draw::drawLine(Vector2d p1, Vector2d p2) {
        int length = (p2 - p1).norm();
        double angle = atan2(p2[1] - p1[1], p2[0] - p1[0]);

        for(int i = 0; i < length; i++) {
            drawPixel(Vector2d(p1[0] + i*cos(angle), p1[1]+ i*sin(angle)));
        }

        /*
        int length = (p2 - p1).norm();
        double angle = acos(((p2 - p1).dot(Vector2d(1, 0)))/length);

        for(int i = 0; i < length; i++) {
            drawPixel(Vector2d(p1[0] + cos(angle)*i, p1[1] + sin(angle)*i));
        }
        */
    }

    // Draws a line between the given two Vector4d's first two components
    void Draw::drawLine(Vector4d p1, Vector4d p2) {
        Vector2d v1 = p1.head<2>();
        Vector2d v2 = p2.head<2>();

        drawLine(v1, v2);
    }

    // Draws the given polygon on the screen with a perspective projection
    void Draw::drawPolygon(Polygon poly) {

        for(int i = 0; i < 3; i++) {
            drawLine(_screen -> scaledProject(poly.getVertex(i%3)), _screen -> scaledProject(poly.getVertex((i+1)%3)));
        }
    }

    // Draws the given mesh of polygons on the screen with a perspective projection
    void Draw::drawMesh(Mesh mesh) {
        for(Polygon p : mesh.getPolygons()) {
            drawPolygon(p);
        }
    }

    // Draws the mesh of the given shape on the screen with a perspective projection
    void Draw::drawShape(Shape *shape) {
        drawMesh(shape -> getMesh());
    }

    // Draws the mesh of the given shape on the screen with a perspective projection
    void Draw::drawQueue(queue<Shape *> *q, double dt) {
        Shape *s;
        for(int i = 0; i < q -> size(); i++) {
            s = q -> front();
            q -> pop();

            drawShape(s);
            s -> updateState(dt);

            if(s -> isAlive()) q -> push(s);
        }
    }
#endif