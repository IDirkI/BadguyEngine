#include <cassert>
#ifndef COLOR_HPP
#define COLOR_HPP

class Color {
    private:
        int _r;
        int _g;
        int _b;
        int _a;

    public:
        Color(int red, int green, int blue, int alpha = 255) {
            assert(((0 <= red && red < 256) && (0 <= blue && blue < 256)) && ((0 <= green && green < 256) && (0 <= alpha && alpha < 256))); // TODO: Add proper error handling
            
            _r = red;
            _g = green;
            _b = blue;
            _a = alpha;
        }

        /* ##### Function Headers ##### */
        int r();
        int g();
        int b();
        int a();
        void setR(int);
        void setG(int);
        void setB(int);
        void setA(int);

        static Color red();
        static Color green();
        static Color blue();
        static Color white();
        static Color black();
};

    //* ##### Member Functions ##### *//

    // Returns the R value
    int Color::r() {
        return _r;
    } 

    // Returns the G value
    int Color::g() {
        return _g;
    }

    // Returns the B value
    int Color::b() {
        return _b;
    }

    // Returns the Alpha value
    int Color::a() {
        return _a;
    }

    // Sets the R value
    void Color::setR(int red) {
        assert(0 <= red && red < 256); // TODO: Add proper error handling
        _r = red;
    } 

    // Sets the G value
    void Color::setG(int green) {
        assert(0 <= green && green < 256); // TODO: Add proper error handling
        _g = green;
    } 

    // Sets the B value
    void Color::setB(int blue) {
        assert(0 <= blue && blue < 256); // TODO: Add proper error handling
        _b = blue;
    } 

    // Sets the A value
    void Color::setA(int alpha) {
        assert(0 <= alpha && alpha < 256); // TODO: Add proper error handling
        _a = alpha;
    } 

    //* ##### Static Functions ##### *//

    // Returns the color Red, (255, 0, 0)
    Color red() {
        return Color(255, 0, 0);
    }

    // Returns the color Green, (0, 255, 0)
    Color green() {
        return Color(0, 255, 0);
    }

    // Returns the color Red, (0, 0, 255)
    Color blue() {
        return Color(0, 0, 255);
    }

    // Returns the color White, (255, 255, 255)
    Color white() {
        return Color(255, 255, 255, 255);
    }

    // Returns the color Black, (0, 0, 0)
    Color black() {
        return Color(0, 0, 0);
    }


#endif