#ifndef PLANE_HPP
#define PLANE_HPP

#include "Shape.hpp"
#include "Triangle.hpp"

class Plane : public Shape{
    public:
        /* ##### Constructor ##### */
        Plane(Mesh mesh, Vector3d position, double mass = 1) : Shape(mesh, position, mass) {
            // TODO: Implement check that at least two vertecies are the same Vector3d
            assert( mesh.getPolygons().size() == 2); // TODO: Add proper error handling
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

        Plane(Triangle *tri[2], Vector3d position, double mass = 1) : Shape(Mesh({tri[0] -> getMesh().getPoly(0), tri[1] -> getMesh().getPoly(0)}), position, mass) {}
};

#endif