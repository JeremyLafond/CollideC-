#ifndef _SPHERE_H_
#define _SPHERE_H_
#include "point.h"
#include "cube.h"
#include "reuleauxtetrahedron.h"

class Cube;
class ReuleauxTetrahedron;
class Sphere
{
    private:
        Point3D center_;
        double radius_;
    public:
        Sphere(Point3D center, double radius);
        Point3D center();
        void setCenter(const Point3D &center);
        double radius();
        void setRadius(double radius);
        bool containedBy(Sphere &sphere);
        bool containedBy(Cube &Cube);
        bool containedBy(ReuleauxTetrahedron &rtet);
};
#endif