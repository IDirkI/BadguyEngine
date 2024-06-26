#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <vector>
#include <cassert>

#include <eigen3/Eigen/Dense>

#include "../Mesh.hpp"

using Eigen::Vector3d;
using Eigen::Vector4d;
using Eigen::Matrix3d;

class Shape {
    protected:
        Mesh _mesh;
        Vector3d _pos;

        double _mass;
        double _time;
        double _scale;

        Vector3d _vel;
        Vector3d _acc;
        Vector3d _angVel;
        Vector3d _angAcc;

        bool _isAlive;

    public:

        Shape(Mesh mesh, Vector3d position, double mass = 1) {
            _mesh = mesh;
            _pos = position;
            _mass = mass;
            _time = 0;
            _scale = 1;

            _vel = Vector3d::Zero();
            _acc = Vector3d::Zero();
            _angVel = Vector3d::Zero();
            _angAcc = Vector3d::Zero();

            _isAlive = true;

            _mesh.moveCenter(_pos);
        }

        /* ##### Function Headers ##### */
        Mesh getMesh();
        Vector3d getPosition();
        double getMass();
        double getAliveTime();
        double getScale();
        Vector3d getVelocity();
        Vector3d getAcceleration();
        Vector3d getAngVelocity();
        Vector3d getAngAcceleration();
        Vector3d getCenter();
        bool isAlive();

        void setPosition(Vector3d);
        void addPosition(Vector3d);
        void setMass(double);
        void addMass(double);
        void setScale(double);
        void addScale(double);
        void setVelocity(Vector3d);
        void addVelocity(Vector3d);
        void setAcceleration(Vector3d);
        void addAcceleration(Vector3d);
        void setAngVelocity(Vector3d);
        void addAngVelocity(Vector3d);
        void setAngAcceleration(Vector3d);
        void addAngAcceleration(Vector3d);

        void kill();
        void revive();

        void updateState(double);
        void updateOrientation(double, double, double);
};

    //* ##### Member Functions ##### *//

    // Returns the mesh of the shape
    Mesh Shape::getMesh() {
        return _mesh;
    }

    // Returns the position of the shape as a Vector3d
    Vector3d Shape::getPosition() {
        return _pos;
    }

    // Returns the (virtual) mass of the shape
    double Shape::getMass() {
        return _mass;
    }

    // Returns the time the shape has been alive for
    double Shape::getAliveTime() {
        return _time;
    }

    // Returns the velocity of the shape as a Vector3d
    Vector3d Shape::getVelocity() {
        return _vel;
    }

    // Returns the acceleration of the shape as a Vector3d
    Vector3d Shape::getAcceleration() {
        return _acc;
    }

    // Returns the angular velocity of the shape as a Vector3d
    Vector3d Shape::getAngVelocity() {
        return _angVel;
    }

    // Returns the angular acceleration of the shape as a Vector3d
    Vector3d Shape::getAngAcceleration() {
        return _angAcc;
    }

    // Returns the center of mass of the shape as a Vector3d
    Vector3d Shape::getCenter() {
        return _mesh.getCenter();
    }

    // Returns if the object is currently alive/shown
    bool Shape::isAlive() {
        return _isAlive;
    }

    // Sets the position of the shape as the given Vector3d
    void Shape::setPosition(Vector3d position) {
        _mesh.moveCenter(-_pos);
        _pos = position;
        _mesh.moveCenter(_pos);
    }

    // Add the given Vector3d to the position of the shape
    void Shape::addPosition(Vector3d position) {
        setPosition(getPosition() + position);
    }

    // Sets the (virtual) mass of the shape
    void Shape::setMass(double mass) {
        _mass = mass;
    }

    // Adds the given mass to the (virtual) mass of the shape
    void Shape::addMass(double mass) {
        _mass += mass;
    }

    // Sets the scale of the shape
    void Shape::setScale(double scale) {
        _scale = scale;
    }

    // Adds the given scale to the scale of the shape
    void Shape::addScale(double scale) {
        _scale += scale;
    }

    // Sets the velocity of the shape as the given Vector3d
    void Shape::setVelocity(Vector3d velocity) {
        _vel = velocity;
    }

    // Adds the given velocity Vector3d to the velocity of the shape
    void Shape::addVelocity(Vector3d velocity) {
        _vel += velocity;
    }

    // Sets the acceleration of the shape as the given Vector3d
    void Shape::setAcceleration(Vector3d acceleration) {
        _acc = acceleration;
    }

    // Adds the given acceleration Vector3d to the acceleration of the shape
    void Shape::addAcceleration(Vector3d acceleration) {
        _acc += acceleration;
    }

    // Sets the angular velocity of the shape as the given Vector3d
    void Shape::setAngVelocity(Vector3d angularVelocity) {
        _angVel = angularVelocity;
    }

    // Adds the given angular velocity Vector3d angular velocity of the shape 
    void Shape::addAngVelocity(Vector3d angularVelocity) {
        _angVel += angularVelocity;
    }

    // Sets the angular acceleration of the shape as the given Vector3d
    void Shape::setAngAcceleration(Vector3d angularAcceleration) {
        _angAcc = angularAcceleration;
    }

    // Adds the given angular acceleration Vector3d to the angular acceleration of the shape 
    void Shape::addAngAcceleration(Vector3d angularAcceleration) {
        _angAcc += angularAcceleration;
    }

    // Kills and removes the shape from the draw queue if it's alive
    void Shape::kill() {
        if(_isAlive) _isAlive = false;
        // TODO: Add draw queue functionality
    }

    // Revives and adds the shape to the draw queue if it's dead
    void Shape::revive() {
        if(!_isAlive) _isAlive = true;
        // TODO: Add draw queue functionality
    }

    // Updates the velocity, position, rotation, etc. of the shape
    void Shape::updateState(double dt) {
        _time += dt;

        setPosition(_pos + _vel*dt);
        updateOrientation((dt*_angVel)[0], (dt*_angVel)[1], (dt*_angVel)[2]);

        _vel += _acc*dt;
        _angVel += _angAcc*dt;
    }

    // Helper function to rotate the shape in updateState() 
    void Shape::updateOrientation(double rX, double rY, double rZ) {
        Vector3d cent = getCenter();
        Vector4d pos4 = {_pos[0], _pos[1], _pos[2], 1};
        Matrix4d rot, transF, transB;
        transF << 1, 0, 0, -cent[0],
                  0, 1, 0, -cent[1],
                  0, 0, 1, -cent[2],
                  0, 0, 0, 1; // Back to the origin

        transB << 1, 0, 0, cent[0],
                  0, 1, 0, cent[1],
                  0, 0, 1, cent[2],
                  0, 0, 0, 1; // Back to the original location

        rot << cos(rY)*cos(rZ), sin(rX)*sin(rY)*cos(rZ) - cos(rX)*sin(rZ), cos(rX)*sin(rY)*cos(rZ) + sin(rX)*sin(rZ), 0,
               cos(rY)*sin(rZ), sin(rX)*sin(rY)*sin(rZ) + cos(rX)*cos(rZ), cos(rX)*sin(rY)*sin(rZ) - sin(rX)*cos(rZ), 0,
                       -sin(rY),                sin(rX)*cos(rY),                   cos(rX)*cos(rY)                   , 0,
                       0,                                0,                            0,                              1; // Rotation at the origin

        _mesh.rotateMesh(transB * _scale * rot * transF);
    }
#endif