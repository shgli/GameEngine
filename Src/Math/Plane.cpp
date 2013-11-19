#include "Math/Plane.h"
#include "Math/MathException.h"
Plane::Plane(const Point& point,const Vector& normal)
    :p(normal.x,normal.y,normal.z,point.Dot(-normal))
{}

Plane::Plane(Real aa,Real bb,Real cc,Real dd)
    :p(aa,bb,cc,dd)
{}

Plane::Plane(Real d,const Vector& normal)
    :p(normal.x,normal.y,normal.z,d)
{}

Point Intersect(const Segment& seg,const Plane& plane)
{
    Real planeDotLine = plane.p.Dot(seg.direction);

    if(0 == planeDotLine)
    {
	if(0 == plane.Test(seg.start)) //判断线段是否在平面内
	{
            throw IntersectEveryWhere();
	}
	else
	{
	    throw PlaneParallel();
	}
    }
    else
    {
	Real t = -seg.start.Dot(plane.p) / seg.direction.Dot(plane.p);

	if(t >= 0 && t <= 1)
	{
            return seg.ComputePoint(t);
	}
	else
	{
	    throw NoIntersect();
	}
    }
}

Point Intersect(const Plane& plane,const Segment& seg)
{
    return Intersect(seg,plane);
}

