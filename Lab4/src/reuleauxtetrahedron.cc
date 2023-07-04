#include "reuleauxtetrahedron.h"
#include "geom.h"
#include "sphere.h"
#include "cube.h"

ReuleauxTetrahedron::ReuleauxTetrahedron(Point3D vertices[4])
{
	std::vector<Point3D> vertices_;
	vertices__ = vertices_;
}

std::vector<Point3D> ReuleauxTetrahedron::vertices()
{
    return vertices__;
}

Point3D ReuleauxTetrahedron::center()
{
    double xAvg = 0;
    double yAvg = 0;
    double zAvg = 0;
    for (int i = 0; i < 3; i++)
    {
        xAvg += vertices()[i].x;
        yAvg += vertices()[i].y;
        zAvg += vertices()[i].z;
    }
    xAvg = xAvg / 3;
    yAvg = yAvg / 3;
    zAvg = zAvg / 3;
    return Point3D(xAvg,yAvg,zAvg);
}

bool ReuleauxTetrahedron::containedBy(ReuleauxTetrahedron &rtet)
{
    double oRad = Geom::distance(rtet.vertices()[0], rtet.vertices()[1]);
    double iRad = Geom::distance(vertices()[0], vertices()[1]);
    double cRad = Geom::distance(center(), rtet.center());
    if(oRad < iRad)
    {
        return false;
    }
    if(cRad > oRad)
    {
        return false;
    }
    return true;
}

bool ReuleauxTetrahedron::containedBy(Cube &cube) 
{
    return true;
}

bool ReuleauxTetrahedron::containedBy(Sphere &sphere)
{
    for(int i = 0; i <= 2; i++)
    {
        if(Geom::distance(vertices()[i], sphere.center()) > sphere.radius())
        {
            return false;
        }
    }
    return true;
}