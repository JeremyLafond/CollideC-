#ifndef _CUBE_H_
#define _CUBE_H_
#include "point.h"
#include "sphere.h"
#include <vector>
#include "reuleauxtetrahedron.h"

class Sphere;
class ReuleauxTetrahedron;
class Cube
{
    private:
        Point3D centerCube_;
        std::vector<Point3D> verticesCube_;
    public:
        Cube(Point3D upperFace[4], Point3D lowerFace[4]);
        Point3D center();
        std::vector<Point3D> vertices();
        bool containedBy(Sphere &sphere);
        bool containedBy(Cube &Cube);
        bool containedBy(ReuleauxTetrahedron &rtet);
};
#endif