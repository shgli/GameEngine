#ifndef _HOMOGENOUS_H
#define _HOMOGENOUS_H
#include "Common/Common.h"
class Matrix;
class Homogenous
    :public boost::additive<Homogenous
    ,boost::multiplicative<Homogenous,Real
    ,boost::equality_comparable<Homogenous
    > > >
{
public:
    Real x,y,z,w;

    Homogenous(Real x = 0.0, Real y = 0.0, Real z = 0.0, Real w = 0.0);
    Homogenous(Real v[4]);

    Homogenous& operator+= (const Homogenous& other);
    Homogenous& operator-= (const Homogenous& other);
    Homogenous& operator+= (Real k);
    Homogenous& operator-= (Real k);
    Homogenous& operator*= (Real k);
    Homogenous& operator/= (Real k);
    Homogenous& operator*= (const Matrix& mat);

    Homogenous operator- ( void ) const;

    Real Dot(const Homogenous& other) const;
    Homogenous Cross(const Homogenous& other) const;

    Real Length( void ) const;
    Real Norm( void ) const;
    Real NormSqure( void ) const;

    Homogenous& Normalize( void );

    void ProjectDiv( void );

    friend Homogenous operator* (const Homogenous& homo,const Matrix& mat);
    friend Homogenous operator* (const Matrix& mat,const Homogenous& home);
    friend Homogenous operator- (Real k,const Homogenous& homo);
    friend bool operator == (const Homogenous& lhs,const Homogenous& rhs);
    
    friend std::ostream& operator<< (std::ostream& os,const Homogenous& h);
};

class Vector
    :public Homogenous
{
public:
    Vector(Real x = 0.0,Real y = 0.0, Real z = 0.0)
        :Homogenous(x,y,z,0.0)
    {}

    Vector(const Homogenous& v)
        :Homogenous(v)
    {}

    static const Vector X_UNIT;
    static const Vector Y_UNIT;
    static const Vector Z_UNIT;
    static const Vector Zero;
};

class Point 
    :public Homogenous
{
public:
    Point(Real x = 0.0,Real y = 0.0, Real z = 0.0)
        :Homogenous(x,y,z,1.0)
    {}

    Point(const Homogenous& v)
        :Homogenous(v)
    {}

    static const Point ORIGION;
};
#endif

