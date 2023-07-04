

#ifndef _CONTAINABLE_H_
#define _CONTAINABLE_H_

// C++ requires forward declaration of any cyclically dependent classes
class Circle;
class RegularConvexPolygon;
class ReuleauxTriangle;

class Containable2D
{
    public:
        virtual bool containedWithin(Circle &circle) = 0;
        virtual bool containedWithin(RegularConvexPolygon &polygon) = 0;
        virtual bool containedWithin(ReuleauxTriangle &rt) = 0;
};
#endif