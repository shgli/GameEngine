#ifndef _PLANE_H
#define _PLANE_H
#include "Segment.h"
class Plane
{
public:
    Homogenous  p;

    Plane( void ) {}
    Plane(const Point& point,const Vector& normal);

    Plane(Real a,Real b,Real c,Real d);

    Plane(Real d,const Vector& normal);

    inline Real Test(const Point& pt) const
    {
	return p.Dot(pt);
    }
};

Point Intersect(const Segment& seg,const Plane& plane);
Point Intersect(const Plane& plane,const Segment& seg);
#endif

