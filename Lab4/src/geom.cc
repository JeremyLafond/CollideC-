

/*
 * Includes published pubic domain information and code from the following sources:
 *
 * https://math.stackexchange.com/questions/275529/check-if-line-intersects-with-circles-perimeter
 * https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
 * https://stackoverflow.com/questions/2792443/finding-the-centroid-of-a-polygon
 */

#include <iostream>
#include <string>
#include <math.h>
#include "geom.h"

double Geom::distance(const Point2D &a, const Point2D &b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

bool Geom::intersects(const Line &line, Circle &circle)
{
    return (abs((circle.center().y - line.a.y) * (line.b.x - line.a.x) - 
        (circle.center().x -  line.a.x) * (line.b.y - line.a.y)) / 
            distance(line.a, line.b)) <= circle.radius();
}

// Given three colinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
static bool onSegment(Point2D p, Point2D q, Point2D r)
{
    if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
        q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
        return true;
    return false;
}
 
// Finds the orientation of ordered triplet (p, q, r).
// Returns: 
//      0 --> p, q and r are colinear
//      1 --> Clockwise
//      2 --> Counterclockwise
static int orientation(Point2D p, Point2D q, Point2D r)
{
    // See https://www.geeksforgeeks.org/orientation-3-ordered-points/
    // for details of below formula.
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;  // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}
//had to change this to work with my old code
bool Geom::doBounds(const Point2D &p1, const Point2D &q1, const Point2D &p2, const Point2D &q2) 
{
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
    // General case
    if (o1 != o2 && o3 != o4)
        return true;
    if (o1 == 0 && onSegment(p1, p2, q1)) return false;
    if (o2 == 0 && onSegment(p1, p2, q1)) return false;
    if (o3 == 0 && onSegment(p2, p1, q2)) return false;
    if (o4 == 0 && onSegment(p2, q1, q2)) return false;
    return false;
}

Point2D Geom::center(RegularConvexPolygon &polygon) 
{
    double cx = 0.0;
    double cy = 0.0;
    double signedArea = 0.0;
    double x0 = 0.0; // Current vertex X
    double y0 = 0.0; // Current vertex Y
    double x1 = 0.0; // Next vertex X
    double y1 = 0.0; // Next vertex Y
    double a = 0.0;  // Partial signed area
    for (int i = 0; i < polygon.vertexCount(); i++)
    {
        x0 = polygon.vertices()[i].x;
        y0 = polygon.vertices()[i].y;
        x1 = polygon.vertices()[(i+1) % polygon.vertexCount()].x;
        y1 = polygon.vertices()[(i+1) % polygon.vertexCount()].y;
        a = x0*y1 - x1*y0;
        signedArea += a;
        cx += (x0 + x1)*a;
        cy += (y0 + y1)*a;
    }
    signedArea *= 0.5;
    cx /= (6.0*signedArea);
    cy /= (6.0*signedArea);
    return Point2D(cx,cy);
}