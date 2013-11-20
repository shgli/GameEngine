#ifndef _SPHERE_H
#define _SPHERE_H
#include "Math/Homogenous.h"
class Sphere
{
public:
    Point center;
    Real  radius;

    friend std::ostream& operator<< (std::ostream& os,const Sphere& sp);
};
#endif

