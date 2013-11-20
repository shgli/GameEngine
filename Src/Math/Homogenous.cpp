#include "Math/Homogenous.h"
#include "Math/Matrix.h"
#include "Math/Algorithm.h"
const Point Point::ORIGION = Point(0.0,0.0,0.0);
const Vector Vector::Zero = Vector(0.0,0.0,0.0);
const Vector Vector::X_UNIT  = Vector(1.0,0.0,0.0);
const Vector Vector::Y_UNIT  = Vector(0.0,1.0,0.0);
const Vector Vector::Z_UNIT  = Vector(0.0,0.0,1.0);

Homogenous::Homogenous(Real xx, Real yy, Real zz, Real ww)
    :x(xx),y(yy),z(zz),w(ww)
{
}

Homogenous Homogenous::operator- ( void ) const
{
    return Homogenous(-this->x,-this->y,-this->z,-this->w);
}

Homogenous& Homogenous::operator+= (const Homogenous& other)
{
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    this->w += other.w;

    return *this;
}

Homogenous& Homogenous::operator-= (const Homogenous& other)
{
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
    this->w -= other.w;

    return *this;
}

Homogenous& Homogenous::operator+= (Real k)
{
    this->x += k;
    this->y += k;
    this->z += k;
    this->w += k;

    return *this;
}

Homogenous& Homogenous::operator-= (Real k)
{
    this->x -= k;
    this->y -= k;
    this->z -= k;
    this->w -= k;

    return *this;

}

Homogenous& Homogenous::operator*= (Real k)
{
    this->x *= k;
    this->y *= k;
    this->z *= k;
    this->w *= k;

    return *this;
}

Homogenous& Homogenous::operator/= (Real k)
{
    this->x /= k;
    this->y /= k;
    this->z /= k;
    this->w /= k;

    return *this;
}

Homogenous& Homogenous::operator*= (const Matrix& mat)
{
    Homogenous tmp(*this);
    this->x = tmp.x * mat(0,0) + tmp.y * mat(1,0) + tmp.z * mat(2,0) + tmp.w * mat(3,0);
    this->y = tmp.x * mat(0,1) + tmp.y * mat(1,1) + tmp.z * mat(2,1) + tmp.w * mat(3,1);
    this->z = tmp.x * mat(0,2) + tmp.y * mat(1,2) + tmp.z * mat(2,2) + tmp.w * mat(3,2);
    this->w = tmp.x * mat(0,3) + tmp.y * mat(1,3) + tmp.z * mat(2,3) + tmp.w * mat(3,3);

    return *this;
}

Real Homogenous::Dot(const Homogenous& other) const
{
    Real dotValue = this->x * other.x + this->y * other.y
	+ this->z * other.z + this->w * other.w;

    return dotValue;
}

Homogenous Homogenous::Cross(const Homogenous& other) const
{
    Homogenous crossRet;
    crossRet.x = this->y * other.z - other.y * this->z;
    crossRet.y = this->z * other.x - other.z * this->x;
    crossRet.z = this->x * other.y - other.x * this->y;
    return crossRet;
}


Real Homogenous::Length( void ) const
{
    return Norm();
}

Real Homogenous::Norm( void ) const
{
    return Sqrt(NormSqure());
}

Real Homogenous::NormSqure( void ) const
{
    return this->Dot(*this);
}

Homogenous& Homogenous::Normalize( void )
{
    Real normReciprocal = 1.0 / Norm();
    *this *= normReciprocal;
    return *this;
}

void Homogenous::ProjectDiv( void )
{
    *this *= 1.0 / this->w;
}

Homogenous operator* (const Homogenous& homo,const Matrix& mat)
{
    Homogenous result = homo;
    result *= mat;

    return result;
}

Homogenous operator* (const Matrix& mat,const Homogenous& homo)
{
    Homogenous result = homo;
    result.x = mat(0).Dot(homo);
    result.y = mat(1).Dot(homo);
    result.z = mat(2).Dot(homo);
    result.w = mat(3).Dot(homo);

    return result;
}

Homogenous operator- (Real k,const Homogenous& homo)
{
    Homogenous result(k,k,k,k);
    result -= homo;

    return result;
}

bool operator == (const Homogenous& lhs,const Homogenous& rhs)
{
    return (lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w);
}

std::ostream& operator<< (std::ostream& os,const Homogenous& h)
{
    boost::format fmt("Homogenous(%10f,%10f,%10f,%10f)");
    fmt % h.x % h.y % h.z % h.w;
    os << fmt.str();

    return os;
}

