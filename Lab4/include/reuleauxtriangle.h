#ifndef _REULEAUXTRIANGLE_H_
#define _REULEAUXTRIANGLE_H_
#include <vector>
#include "containable.h"
#include "point.h"
#include "circle.h"
#include "line.h"
// C++ requires forward declaration of any cyclically dependent classes
class Circle;
class RegularConvex;
class ReuleauxTriangle : public Containable2D
{
    private:
        std::vector<Point2D> vertices__;
        Point2D center_;
    public:
        // do not change this constructor
        //reference to array of Point2D type members of size 3
        ReuleauxTriangle(Point2D vertices[3]);
        std::vector<Point2D> vertices();
        Point2D center();
        bool containedWithin(Circle &circle);
        bool containedWithin(RegularConvexPolygon &polygon);
        bool containedWithin(ReuleauxTriangle &rt);
};
#endif