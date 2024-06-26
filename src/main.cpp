#include "main.hpp"


int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    const size_t FPS = 60;
    const double dt = 1.0/FPS;

    Camera cam = Camera();
    Draw draw = Draw(cam.getScreen());
    queue<Shape *> queue;

    //* ##### TEST CODE ##### *//
    Mesh m = Mesh({ Polygon({Vector3d(0, 0, 0), Vector3d(0, 0.3, 0), Vector3d(0.3, 0.3, 0)}),
                    Polygon({Vector3d(0, 0, 0), Vector3d(0.3, 0.3, 0), Vector3d(0.3, 0, 0)}),
                    Polygon({Vector3d(0, 0.3, 0), Vector3d(0, 0.3, 0.3), Vector3d(0.3, 0.3, 0.3)}),
                    Polygon({Vector3d(0, 0.3, 0), Vector3d(0.3, 0.3, 0.3), Vector3d(0.3, 0.3, 0)}),
                    Polygon({Vector3d(0.3, 0, 0), Vector3d(0.3, 0.3, 0), Vector3d(0.3, 0.3, 0.3)}),
                    Polygon({Vector3d(0.3, 0, 0), Vector3d(0.3, 0.3, 0.3), Vector3d(0.3, 0, 0.3)}),
                    Polygon({Vector3d(0, 0, 0.3), Vector3d(0, 0.3, 0.3), Vector3d(0, 0.3, 0)}),
                    Polygon({Vector3d(0, 0, 0.3), Vector3d(0, 0.3, 0), Vector3d(0, 0, 0)}),
                    Polygon({Vector3d(0.3, 0, 0.3), Vector3d(0.3, 0.3, 0.3), Vector3d(0, 0.3, 0.3)}),
                    Polygon({Vector3d(0.3, 0, 0.3), Vector3d(0.3, 0.3, 0), Vector3d(0, 0, 0.3)}),
                    Polygon({Vector3d(0, 0, 0.3), Vector3d(0, 0, 0), Vector3d(0.3, 0, 0)}),
                    Polygon({Vector3d(0, 0, 0.3), Vector3d(0.3, 0, 0), Vector3d(0.3, 0, 0.3)})});
    Rectangle s1 = Rectangle(m, Vector3d(0, 0, 0));
    s1.setAngVelocity(Vector3d(0.1, 0.05, 0.3));

    Rectangle s2 = Rectangle(m, Vector3d(-1, -0.2, 0));
    s2.setAngVelocity(Vector3d(0.2, 0, -0.1));

    Plane s3 = Plane(Mesh({  Polygon(Vector3d(0, 0, 0), Vector3d(0.3, 0.4, 0), Vector3d(0.3, 0, 0)), 
                        Polygon(Vector3d(0, 0, 0), Vector3d(0.3, 0.4, 0), Vector3d(0, 0.4, 0))}), Vector3d(0.7, 0.6, 0));
    s3.setAngVelocity(Vector3d(0.06, 0.2, 0.01));

    queue.push(&s1);
    queue.push(&s2);
    queue.push(&s3);
    //* ##### TEST CODE END ##### *//

    while(input()) {
        SDL_Delay(dt);
        update(dt, &draw, &queue);
    }

    return 0;
}

// Update function called repeatedly every second, frequency definedby "FPS"
void update(double dt, Draw *d, queue<Shape *> *q) {
    d -> clean(); // Clears the previous drawings. Always at the start of update()

    if(q -> size() > 0) {
        d -> drawQueue(q, dt);
    }
    
    d -> show(); // Shows the newly drawn pixels. Always at the end of update()
}

// Check if esc is pressed
bool input() {
    SDL_Event e;
    const Uint8 *keystates = SDL_GetKeyboardState(NULL);

    while(SDL_PollEvent(&e)) {
        if(e.type == SDL_QUIT || keystates[SDL_SCANCODE_ESCAPE]) return false;
    }

    return true;
}
