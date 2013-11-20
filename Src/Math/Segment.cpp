#include "Math/Segment.h"
#include "Math/Algorithm.h"
#include "Math/MathException.h"
Segment::Segment(const Point& ptStart,const Point& ptEnd)
    :start(ptStart)
    ,direction(ptEnd - ptStart)
{
}

Segment::Segment(const Point& ptStart,const Vector& vDirection)
    :start(ptStart)
    ,direction(vDirection)
{
}

bool Segment::Intersect(Real x1,Real y1,Real vx1,Real vy1
                       ,Real x2,Real y2,Real vx2,Real vy2,Real& t1,Real& t2) const
{
    Real det = vx1 * vy2 - vy1 * vx2;
    if(0 == Fabs(det))
    {
	return false;
    }

    t1 = (vx2 * (y1 - y2) - vy2 * (x1 - x2)) / det;
    t2 = (vx1 * (y1 - y2) - vy1 * (x1 - x2)) / det;

    return true;
}

Point Segment::Intersect(const Segment& o) const
{
    Vector cross = direction.Cross(o.direction);
    Real det = (o.start.x - start.x) * cross.x
             + (o.start.y - start.y) * cross.y
	     + (o.start.z - start.z) * cross.z;
    if(det != 0)
    {
	throw SegmentAntarafacial();
    }
    else
    {
        if(Vector::Zero == cross)        
	{
	    Vector v = start - o.start;
	    v = v.Cross(direction);
            
	    if(Vector::Zero != v)
	    {
	        throw SegmentParallel();
	    }
	    else
	    {
		throw IntersectEveryWhere();
	    }
	}
	else
	{
	    Real t1,t2;
	    if ( Intersect(start.x,start.y,direction.x,direction.y,o.start.x,o.start.y,o.direction.x,o.direction.y,t1,t2)
	      || Intersect(start.y,start.z,direction.y,direction.z,o.start.y,o.start.z,o.direction.y,o.direction.z,t1,t2)
	      || Intersect(start.x,start.z,direction.x,direction.z,o.start.x,o.start.z,o.direction.x,o.direction.z,t1,t2))
	    {
		if (t1 >= 0 && t1 <= 1 && t2 >=0 && t2<= 1)
		{
		    return ComputePoint(t1);
		}
		else
		{
		    throw NoIntersect();
		}
	    }
	    assert(false);
	}
    }
}

