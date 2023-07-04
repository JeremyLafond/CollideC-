#include "reuleauxtriangle.h"
#include "geom.h"
#include "polygon.h"
#include "circle.h"

ReuleauxTriangle::ReuleauxTriangle(Point2D vertices[3])
{
	std::vector<Point2D> vertices_; 
	vertices__ = vertices_;
}

std::vector<Point2D> ReuleauxTriangle::vertices()
{
    return vertices__;
}

Point2D ReuleauxTriangle::center()
{
    double xAvg = 0;
    double yAvg = 0;
    for (int i = 0; i < 3; i++)
    {
        xAvg += vertices()[i].x;
        yAvg += vertices()[i].y;
    }
    xAvg = xAvg / 3;
    yAvg = yAvg / 3;
    return Point2D(xAvg,yAvg);
}

bool ReuleauxTriangle::containedWithin(ReuleauxTriangle &rt)
{
    double oRad = Geom::distance(rt.vertices()[0], rt.vertices()[1]);
    double iRad = Geom::distance(vertices()[0], vertices()[1]);
    double cRad = Geom::distance(center(), rt.center());
    if(oRad < iRad)
    {
        return false;
    }
    else if(cRad > oRad)
    {
        return false;
    }
    return true;
}

bool ReuleauxTriangle::containedWithin(RegularConvexPolygon &polygon) 
{
    return true;
}

bool ReuleauxTriangle::containedWithin(Circle &circle)
{
	for(int i = 0; i <= 2; i++)
	{
		if(Geom::distance(vertices()[i], circle.center()) > circle.radius())
		{
			return false;
		}
	}
    return true;
}