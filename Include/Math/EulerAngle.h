#ifndef _EULERANGLE_HPP
#define _EULERANGLE_HPP
#include "Common/Common.h"
#include "Math/Matrix.h"
typedef Real Angle;
class EulerAngle
{
public:
    EulerAngle(Angle angleX = 0.0,Angle angleY = 0.0,Angle angleZ = 0.0);

    const Matrix GetMatrix( void ) const;

    Angle x,y,z,w;
};
#endif

