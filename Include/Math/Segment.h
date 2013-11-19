#ifndef _SEGMENT_H
#define _SEGMENT_H
#include "Math/Homogenous.h"
class Segment
{
public:
    Point start;
    Vector direction;

    Segment(const Point& ptStart,const Point& ptEnd);

    Segment(const Point& ptStart,const Vector& vDirection);


    inline Point ComputePoint(Real t) const  //return start + t*direction
    {
	Point ret(direction * t);
	ret += start;
	return ret;
    }

    Point Intersect(const Segment& other) const;

private:
    bool Intersect(Real x1,Real y1,Real vx1,Real vy1
             ,Real x2,Real y2,Real vx2,Real vy2,Real& t1,Real& t2) const;

};
#endif

