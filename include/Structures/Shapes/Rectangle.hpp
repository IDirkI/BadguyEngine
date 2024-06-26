#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "Shape.hpp"
#include "Triangle.hpp"
#include "Rectangle.hpp"

class Rectangle : public Shape {
    public: 
        /* ##### Constructor ##### */
        Rectangle(Mesh mesh, Vector3d position, double mass = 1) : Shape(mesh, position, mass) {
            // TODO: Implement check that at edges and corners connect
            assert( mesh.getPolygons().size() == 12); // TODO: Add proper error handling
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

        Rectangle(Triangle *tri[12], Vector3d position, double mass = 1) : Shape(Mesh({tri[0] -> getMesh().getPoly(0) , tri[1] -> getMesh().getPoly(0),
                                                                                       tri[2] -> getMesh().getPoly(0) , tri[3] -> getMesh().getPoly(0),
                                                                                       tri[4] -> getMesh().getPoly(0) , tri[5] -> getMesh().getPoly(0),
                                                                                       tri[6] -> getMesh().getPoly(0) , tri[7] -> getMesh().getPoly(0),
                                                                                       tri[8] -> getMesh().getPoly(0) , tri[9] -> getMesh().getPoly(0),
                                                                                       tri[10] -> getMesh().getPoly(0) , tri[11] -> getMesh().getPoly(0),
                                                                                       }), position, mass) {}

        Rectangle(Rectangle *rec[6], Vector3d position, double mass = 1) : Shape(Mesh({rec[0] -> getMesh().getPoly(0) , rec[1] -> getMesh().getPoly(0),
                                                                                       rec[2] -> getMesh().getPoly(0) , rec[3] -> getMesh().getPoly(0),
                                                                                       rec[4] -> getMesh().getPoly(0) , rec[5] -> getMesh().getPoly(0),
                                                                                       }), position, mass) {}
};

#endif