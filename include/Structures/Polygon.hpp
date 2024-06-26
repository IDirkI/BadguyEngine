#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>

#include <eigen3/Eigen/Dense>

using Eigen::Matrix4d;
using Eigen::Vector3d;
using Eigen::Vector4d;

class Polygon {
    private:
        Vector3d _vertices[3];

    public: 
        /* ##### Constructors ###### */
        Polygon(Vector3d v1, Vector3d v2, Vector3d v3) {
            assert(((v1 - v2).norm() != 0 && (v2 - v3).norm() != 0) && (v1 - v3).norm() != 0); // TODO: Replace with proper error handling

            _vertices[0] = v1;
            _vertices[1] = v2;
            _vertices[2] = v3;
        }

        Polygon(Vector3d *vects) {
            assert(((vects[0] - vects[1]).norm() != 0 && (vects[1] - vects[3]).norm() != 0) && (vects[0] - vects[2]).norm() != 0); // TODO: Replace with proper error handling

            _vertices[0] = vects[0];
            _vertices[1] = vects[1];
            _vertices[2] = vects[2];
        }

        /* ##### Function Headers ##### */
        Vector3d getVertex(int);
        Vector3d *getVertices();
        Vector3d getCenter();
        void moveCenter(Vector3d);
        void rotatePolygon(Matrix4d);
};


    //* ##### Member Functions ##### *//

    // Returns the array of Vector3d vertices of the polygon as a pointer to the first vertex
    Vector3d *Polygon::getVertices() {
        return _vertices;
    }

    // Returns the vertex of the polygon matching the given index
    Vector3d Polygon::getVertex(int index) {
        assert(0 <= index && index < 3); // TODO: Replace with proper error handling

        return _vertices[index];
    }

    // Returns the mass center of all vertices as a Vector3d
    Vector3d Polygon::getCenter() {
        return (_vertices[0] + _vertices[1] + _vertices[2])/3;
    }

    // Moves the center of the polygon to the given Vector3d
    void Polygon::moveCenter(Vector3d center) {
        for(int i = 0; i < 3; i++) {
            _vertices[i] += center;
        }
    } 

    // Transforms all the vertecies of the polygon according to the homogeneous transformation matrix
    void Polygon::rotatePolygon(Matrix4d trans) {
        Vector4d v4 = {0, 0, 0, 1};
        for(int i = 0; i < 3; i++) {
            v4 = {_vertices[i][0], _vertices[i][1], _vertices[i][2], 1};

            _vertices[i] = (trans*v4).head<3>();
        }
    }

#endif