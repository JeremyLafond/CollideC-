

#ifndef _POINT_H_
#define _POINT_H_

class Point2D {
    public:
        double x;
        double y;

        // do not change these constructors
        Point2D() { x = 0.0, y = 0.0; }
        Point2D(double dx, double dy) { x = dx; y = dy; }
        Point2D(const Point2D &p) { x = p.x; y = p.y; }
};

//added 3d point implementation
class Point3D: public Point2D {
    public:
        double x;
        double y;
        double z;
        Point3D() { x = 0.0, y = 0.0, z = 0.0; }
        Point3D(double dx, double dy, double dz) { x = dx; y = dy; z = dz; }
        Point3D(const Point3D &p) { x = p.x; y = p.y; z = p.z; }
};

#endif