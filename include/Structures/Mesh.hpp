#ifndef MESH_HPP
#define MESH_HPP

#include <vector>

#include "./Polygon.hpp"

using std::vector;

class Mesh {
    private:
        vector<Polygon> _poly;
    
    public:
        /* ##### Constructors ##### */
        Mesh() {
            _poly = {};
        }

        Mesh(vector<Polygon> polygons) {
            _poly = polygons;
        }

        /* ##### Funciton Headers ##### */
        vector<Polygon> getPolygons();
        Polygon getPoly(int);
        Vector3d getCenter();
        void moveCenter(Vector3d);
        void rotateMesh(Matrix4d);

};

    //* ##### Member Functions ##### *//

    // Returns the list of polygons making up the Mesh as a vector<Polygon>
    vector<Polygon> Mesh::getPolygons() {
        return _poly;
    }

    // Returns a polygons making up the Mesh matching the given index
    Polygon Mesh::getPoly(int index) {
        return _poly[index];
    }

    // Returns the mass center of all the polygons as a Vector3d, averaging out the centers of the polygons
    Vector3d Mesh::getCenter() {
        Vector3d sum = Vector3d::Zero();
        int num = 0;

        for(Polygon p : _poly) {
            sum += p.getCenter();
            num++;
        }

        return sum/num;
    }

    // Moves the center of the mesh to the given position
    void Mesh::moveCenter(Vector3d center) {
        for(vector<Polygon>::iterator it = _poly.begin(); it != _poly.end(); it++) {
            it -> moveCenter(center);
        }
    }   

    // Rotates all the polygons specified by the given homogeneous translation matrix
    void Mesh::rotateMesh(Matrix4d trans) {
        for(vector<Polygon>::iterator it = _poly.begin(); it != _poly.end(); it++) {
            it -> rotatePolygon(trans);
        }
    }

#endif