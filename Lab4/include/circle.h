
#ifndef _CIRCLE_H_
#define _CIRCLE_H_
#include "containable.h"
#include "point.h"
#include "polygon.h"
#include "reuleauxtriangle.h"

class Circle : public Containable2D
{
    private:
        Point2D center_;
        double radius_;
    public:
        // do not change this constructor
        Circle(const Point2D &center, double radius);
        Point2D center();
        void setCenter(const Point2D &center);
        double radius();
        void setRadius(double radius);
        bool containedWithin(Circle &circle);
        bool containedWithin(RegularConvexPolygon &polygon);
        bool containedWithin(ReuleauxTriangle &rt);
};
#endif