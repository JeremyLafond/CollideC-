#include "sphere.h"
#include "geom.h"
#include "reuleauxtetrahedron.h"
#include "cube.h"

Sphere::Sphere(Point3D center, double radius)
{
    setCenter(center);
    setRadius(radius);
}

Point3D Sphere::center()
{
    return center_;
}

void Sphere::setCenter(const Point3D &center)
{
    center_.x = center.x;
    center_.y = center.y;
    center_.z = center.z;
}

double Sphere::radius()
{
    return radius_;
}

void Sphere::setRadius(double radius)
{
    radius_ = radius;
}
/*
*/
bool Sphere::containedBy(Sphere &sphere)
{
    return Geom::distance(center(), sphere.center()) <= (sphere.radius() - radius());
}
/*
*/
bool Sphere::containedBy(Cube &cube) 
{
	double norm = Geom::distance(cube.vertices()[0], cube.vertices()[1]);
	if( (Geom::distance(cube.center(), center() ) > radius()) || (radius() > norm) )
	{
		return false;
	}
    return true;
}

bool Sphere::containedBy(ReuleauxTetrahedron &rtet) 
{   
	for(int i = 0; i <= 3; i++)
	{
		int t2 = i + 1;
		if(i == 2)
		{
			t2 = 0;
		}
		double d1 = Geom::distance(rtet.vertices()[i], rtet.vertices()[t2]) - radius();
		double d2 = Geom::distance(rtet.vertices()[i], center());
		if(d2 > d1)
		{
			return false;
		}
	}
    return true;   
}