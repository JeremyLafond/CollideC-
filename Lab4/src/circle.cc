
#include "circle.h"
#include <math.h>
#include <cstdlib>
#include "geom.h"
#include "polygon.h"
#include "reuleauxtriangle.h"

Circle::Circle(const Point2D &center, double radius)
{
    setCenter(center);
    setRadius(radius);
}

Point2D Circle::center()
{
    return center_;
}

void Circle::setCenter(const Point2D &center)
{
    center_.x = center.x;
    center_.y = center.y;
}

double Circle::radius()
{
    return radius_;
}

void Circle::setRadius(double radius)
{
    radius_ = radius;
}

/*
 * If distance between centers is less than difference between the radius of containing 
 * circle and the radius of this circle, this circle is not contained
 */
bool Circle::containedWithin(Circle &circle)
{
    return Geom::distance(center(), circle.center()) <= (circle.radius() - radius());
}

/*
 * If circle intersects with any polygon edge, circle is not contained       
 * If line between centers intersects with any polygon edge, circle is not contained
 * Only other possibility is that the circle is contained
 */
bool Circle::containedWithin(RegularConvexPolygon &polygon) 
{
    double vX1;
    double vY1;
    double vX2;
    double vY2;
    double cX;
    double cY;
    double rad;
    double a;
    double b;
    double c;
    double mag;
    double dP;
    double distance;
    unsigned int p2;
    unsigned int vert = polygon.vertexCount() - 1;
    for(unsigned int i = 0; i <= vert; i++)
    {
        p2 = i + 1;
        if(i == vert)
        {
            p2 = 0;
        }
        vX1 = polygon.vertices()[i].x;
        vY1 = polygon.vertices()[i].y;
        vX2 = polygon.vertices()[p2].x;
        vY2 = polygon.vertices()[p2].y;
        cX = center().x;
        cY = center().y;
        rad = radius();
        a = vY2 - vY1;
        b = vX2 - vX1;
        c = (vX2 * vY1) - (vY2 * vX1);
        mag = sqrt( pow(a,2) + pow(b,2) );
        dP = abs ((a * cX) - (b * cY) + (c));
        distance = dP / mag;
        if(distance < rad)
        {
            return false;
        }
        if(Geom::distance(center(), Geom::center(polygon)) > radius())
        {
            return false;
        }
    }
    return true;
}

bool Circle::containedWithin(ReuleauxTriangle &rt) 
{   
    double rtRad = Geom::distance(rt.vertices()[1], rt.vertices()[0]);
    for(int i = 0; i <= 2; i++)
    {
        int t2 = i + 1;
        if(i == 2)
        {
            t2 = 0;
        }
        if(Geom::distance(rt.vertices()[i], center()) > (Geom::distance(rt.vertices()[i], rt.vertices()[t2]) - rtRad))
        {
            return false;
        }
    }
    return true;   
}