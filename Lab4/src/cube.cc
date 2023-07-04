#include "cube.h"
#include "geom.h"
#include "sphere.h"
#include "reuleauxtetrahedron.h"

Cube::Cube(Point3D upperFace[4], Point3D lowerFace[4])
{
    std::vector<Point3D> upperFace_;
    std::vector<Point3D> lowerFace_;
    std::vector<Point3D> verticesCube;
    verticesCube.insert(verticesCube.end(), lowerFace_.begin(), lowerFace_.end());
    verticesCube_ = verticesCube;
}

std::vector<Point3D> Cube::vertices()
{
    return verticesCube_;
}

Point3D Cube::center()
{
    double xAvg = 0;
    double yAvg = 0;
    double zAvg = 0;
    for (int i = 0; i < 7; i++)
    {
        xAvg += vertices()[i].x;
        yAvg += vertices()[i].y;
        zAvg += vertices()[i].z;
    }
    xAvg = xAvg / 8;
    yAvg = yAvg / 8;
    zAvg = zAvg / 8;
    return Point3D(xAvg,yAvg,zAvg);
}

bool Cube::containedBy(Sphere &sphere)
{
    for(int i = 0; i < 7; i++)
    {
        if( (Geom::distance(vertices()[i], center()) > sphere.radius()) || (Geom::distance(sphere.center(), vertices()[i]) > sphere.radius()) )
        {
            return false;
        }
    }
    return true;
}

bool Cube::containedBy(Cube &cube)
{
    Point3D p1;
    Point3D q1;
    Point3D p2;
    Point3D q2;
    unsigned int t2;
    unsigned int t3;
    unsigned int iVert = 7;
    unsigned int oVert = 7;
    for(unsigned int i = 0; i <= iVert; i++)
    {
        for(unsigned int j = 0; j <= oVert; j++)
        {
            t2 = i + 1;
            if(i == iVert)
            {
                t2 = 0;
            }
            t3 = j + 1;
            if(j == oVert)
            {
                t3 = 0;
            }
            p1 = vertices()[i];
            q1 = vertices()[t2];
            p2 = cube.vertices()[j];
            q2 = cube.vertices()[t3];
            if(Geom::doBounds(p1, q1, p2, q2))
            {
                return false;
            }
        }
    }
    return true;
}

bool Cube::containedBy(ReuleauxTetrahedron &rtet)
{
    unsigned int vertI = 7;//cube v# - 1
    unsigned int vertO = 3;//RTet v# - 1
    double rtRad = Geom::distance(rtet.vertices()[1], rtet.vertices()[0]);
    for(unsigned int i = 0; i <= vertI; i++)
    {
        for(unsigned int j = 0; j <= vertO; j++)
        {
            if(Geom::distance(vertices()[i], rtet.vertices()[j]) > rtRad)
            {
                return false;
            }
        }
    }
    return true;
}