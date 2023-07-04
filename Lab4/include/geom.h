

#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include "point.h"
#include "line.h"
#include "circle.h"
#include "polygon.h"

class Geom {
    public:
        static double  distance(const Point2D &a, const Point2D &b);
        static bool intersects(const Line &line, Circle &circle);
        static bool    doBounds(const Point2D &p1, const Point2D &p2, const Point2D &q1, const Point2D &q2);
      	static Point2D center(RegularConvexPolygon &polygon);
};
#endif
