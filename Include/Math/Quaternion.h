#ifndef _QUATERNION_HPP
#define _QUATERNION_HPP
#include "Common/Common.h"
#include "Math/Homogenous.h"
#include "Math/Matrix.h"
class EulerAngle;
class Quaternion
    :public boost::additive<Quaternion
    ,boost::multipliable<Quaternion
    ,boost::multiplicative<Quaternion,Real
    > > >
{
public:
    Real w, x,y,z;

    Quaternion( void );
    Quaternion(Real ww,Real xx,Real yy,Real zz)
	:w(ww),x(xx),y(yy),z(zz)
    {}

    Quaternion(Real theta,const Vector& v);
    Quaternion(const EulerAngle& angle);

    Quaternion& operator+= (const Quaternion& other);
    Quaternion& operator-= (const Quaternion& other);
    Quaternion& operator+= (Real k);
    Quaternion& operator-= (Real k);
    Quaternion& operator*= (Real k);
    Quaternion& operator/= (Real k);
    Quaternion& operator*= (const Quaternion& other);

    Real Norm( void ) const;
    Real NormSqure( void ) const;
    void Normalize( void );

    Quaternion Conjugate( void ) const;
    Quaternion UnitInvert( void ) const;
    Quaternion Invert( void ) const;

    void ToVectorThetha(Real& thetha,Vector& v);
    Matrix ToMatrix( void ) const;

    friend std::ostream& operator<< (std::ostream& os,const Quaternion& q);
};

#endif

