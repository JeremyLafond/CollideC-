#ifndef _REULEAUXTETRAHEDRON_H_
#define _REULEAUXTETRAHEDRON_H_
#include <vector>
#include "point.h"
#include "sphere.h"
#include "cube.h"

class Cube;
class Sphere;
class ReuleauxTetrahedron
{
    private:
        std::vector<Point3D> vertices__;
    public:
        ReuleauxTetrahedron(Point3D vertices[4]);
        Point3D center();
        std::vector<Point3D> vertices();
        bool containedBy(Sphere &sphere);
        bool containedBy(Cube &Cube);
        bool containedBy(ReuleauxTetrahedron &rtet);
};
#endif