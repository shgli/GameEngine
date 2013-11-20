#include "Math/EulerAngle.h"
#include "Math/Matrix.h"
#include "Math/Algorithm.h"
EulerAngle::EulerAngle(Angle angleX,Angle angleY,Angle angleZ)
    :x(angleX)
    ,y(angleY)
    ,z(angleZ)
    ,w(0)
{
}

const Matrix EulerAngle::GetMatrix( void ) const
{
    Real angle = 1.0;
    Real sinFact = Sin(angle);
    Real cosFact = 1 - Cos(angle);
    Real mXX = this->x * this->x,
	    mXY = this->x * this->y,
	    mXZ = this->x * this->z,
	    mYY = this->y * this->y,
            mYZ = this->y * this->z,
	    mZZ = this->z * this->z;
    Matrix  mat( (1 - cosFact) + cosFact * mXX      , -sinFact * this->z + cosFact * mXY, sinFact * this->y + cosFact * mXZ,0
	         ,sinFact * this->z + cosFact * mXY , (1 - cosFact) + cosFact * mYY     , -sinFact * this->x + cosFact * mYZ,0
		 ,-sinFact * this->y + cosFact * mXZ, sinFact * this->x + cosFact * mYZ , (1 - cosFact) + cosFact * mZZ,0
		 ,0,0,0,1);

    return mat;
}


