#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Shape.hpp"

class Triangle : public Shape {
    public:
        /* ##### Constructor ##### */
        Triangle(Mesh mesh, Vector3d position, double mass = 1) : Shape(mesh, position, mass) {
            assert(mesh.getPolygons().size() == 1); // TODO: Add proper error handling
            _mesh = mesh;
            _pos = position;
            _mass = mass;
            _time = 0;

            _vel = Vector3d::Zero();
            _acc = Vector3d::Zero();
            _angVel = Vector3d::Zero();
            _angAcc = Vector3d::Zero();

            _isAlive = true;

            _mesh.moveCenter(_pos);
        }

        Triangle(Vector3d *vert[3], Vector3d position, double mass = 1) : Shape(Mesh({vert[0], vert[1], vert[2]}), position, mass) {}

        Triangle(Polygon polygon, Vector3d position, double mass = 1) : Shape(Mesh({polygon}), position, mass) {}
};

#endif