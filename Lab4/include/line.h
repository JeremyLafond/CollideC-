

#ifndef _LINE_H_
#define _LINE_H_

#include "point.h"

class Line {
    public:
        Point2D a;
        Point2D b;
        // do not change this constructor
        Line(Point2D pa, Point2D pb) { a = pa; b = pb; }
};
#endif