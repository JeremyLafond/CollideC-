
#include "polygon.h"
#include "geom.h"
#include "circle.h"
#include "reuleauxtriangle.h"

RegularConvexPolygon::RegularConvexPolygon(std::vector<Point2D> vertices)
{
    vertices_ = vertices;
}

std::vector<Point2D> RegularConvexPolygon::vertices()
{
    return vertices_;
}

std::vector<Line> RegularConvexPolygon::edges()
{
    std::vector<Line> edges;
    for (unsigned int i = 0; i < vertices_.size()-1; i++) 
        edges.push_back(Line(vertices_[i],vertices_[i+1]));
    edges.push_back(Line(vertices_[vertices_.size()-1],vertices_[0]));
    return edges;
}

int RegularConvexPolygon::vertexCount()
{
    return vertices_.size();
}

bool RegularConvexPolygon::containedWithin(Circle &circle)
{
    for(unsigned int i = 0; i <= vertices_.size() - 1; i++)
    {
        if(Geom::distance(vertices()[i], circle.center() ) > circle.radius() )
        {
            return false;
        }
    }
    return true;
}

bool RegularConvexPolygon::containedWithin(RegularConvexPolygon &polygon)
{
    Point2D p1;
    Point2D q1;
    Point2D p2;
    Point2D q2;
    unsigned int t2;
    unsigned int t3;
    unsigned int iVert = vertices_.size() - 1;
    unsigned int oVert = polygon.vertices_.size() - 1;
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
            p2 = polygon.vertices()[j];
            q2 = polygon.vertices()[t3];
            if(Geom::doBounds(p1, q1, p2, q2))
            {
                return false;
            }
        }
    }
    return true;
}

bool RegularConvexPolygon::containedWithin(ReuleauxTriangle &rt)
{
    unsigned int vertI = vertices_.size() - 1; //n side poly v# - 1
    unsigned int vertO = 2;//RT v# - 1
    double rtRad = Geom::distance(rt.vertices()[1], rt.vertices()[0]);
    for(unsigned int i = 0; i <= vertI; i++)
    {
        for(unsigned int j = 0; j <= vertO; j++)
        {
            if(Geom::distance(vertices()[i], rt.vertices()[j]) > rtRad)
            {
                return false;
            }
        }
    }
    return true;
}