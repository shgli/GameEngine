#include "Math/Sphere.h"
std::ostream& operator<< (std::ostream& os,const Sphere& sp)
{
    os<<"Sphere : center("<<sp.center<<"),radius "<<sp.radius;
    return os;
}
