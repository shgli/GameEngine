#include <cstring>
#include "Math/Quaternion.h"
#include "Math/Algorithm.h"
#include "Math/EulerAngle.h"
Quaternion::Quaternion( void )
{
    std::memset(this,0,sizeof(Quaternion));
}

Quaternion::Quaternion(Real theta,const Vector& v)
{
    Real halfThetha = theta / 2;
    this->w = Cos(halfThetha);
    
    Real sin = Sin(halfThetha);
    this->x = sin * v.x;
    this->y = sin * v.y;
    this->z = sin * v.z;
}

Quaternion::Quaternion(const EulerAngle& angle)
{
    Real cos_z_2 = 0.5 * Cos(angle.z);
    Real cos_y_2 = 0.5 * Cos(angle.y);
    Real cos_x_2 = 0.5 * Cos(angle.x);

    Real sin_z_2 = 0.5 * Sin(angle.z);
    Real sin_y_2 = 0.5 * Sin(angle.y);
    Real sin_x_2 = 0.5 * Sin(angle.x);

    this->w = cos_z_2 * cos_y_2 * cos_x_2 + sin_z_2 * sin_y_2 * sin_x_2;
    this->x = cos_z_2 * cos_y_2 * sin_x_2 - sin_z_2 * sin_y_2 * cos_x_2;
    this->y = cos_z_2 * sin_y_2 * cos_x_2 + sin_z_2 * cos_y_2 * sin_x_2;
    this->z = sin_z_2 * cos_y_2 * cos_x_2 - cos_z_2 * sin_y_2 * sin_x_2;
}

void Quaternion::ToVectorThetha(Real& thetha,Vector& v)
{
    thetha = ACos(this->w);

    Real sinThethaReciprocal = 1.0 / Sin(thetha);
    v.x = this->x * sinThethaReciprocal;
    v.y = this->y * sinThethaReciprocal;
    v.z = this->z * sinThethaReciprocal;

    thetha *= 2;
}

Quaternion& Quaternion::operator+= (const Quaternion& other)
{
    this->w += other.w;
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;

    return *this;
}

Quaternion& Quaternion::operator-= (const Quaternion& other)
{
    this->w -= other.w;
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;

    return *this;
}

Quaternion& Quaternion::operator+= (Real k)
{
    this->w += k;
    this->x += k;
    this->y += k;
    this->z += k;

    return *this;
}

Quaternion& Quaternion::operator-= (Real k)
{
    this->w -= k;
    this->x -= k;
    this->y -= k;
    this->z -= k;

    return *this;
}

Quaternion& Quaternion::operator*= (Real k)
{
    this->w *= k;
    this->x *= k;
    this->y *= k;
    this->z *= k;

    return *this;
}

Quaternion& Quaternion::operator/= (Real k)
{
    Real reciprocal = 1.0 / k;
    *this *= reciprocal;
    
    return *this;
}

Quaternion& Quaternion::operator*= (const Quaternion& other)
{
    Real prd_0 = (this->z - this->y) * (other.y - other.z);
    Real prd_1 = (this->w + this->x) * (other.w + other.x);
    Real prd_2 = (this->w - this->x) * (other.y + other.z);
    Real prd_3 = (this->y + this->z) * (other.w - other.x);
    Real prd_4 = (this->z - this->x) * (other.x - other.y);
    Real prd_5 = (this->z + this->x) * (other.x + other.y);
    Real prd_6 = (this->w + this->y) * (other.w - other.z);
    Real prd_7 = (this->w - this->y) * (other.w + other.z);

    Real prd_8 = prd_5 + prd_6 + prd_7;
    Real prd_9 = 0.5 * (prd_4 + prd_8);

    // and finally build up the result with the temporary products
    //
    this->w = prd_0 + prd_9 - prd_5;
    this->x = prd_1 + prd_9 - prd_8;
    this->y = prd_2 + prd_9 - prd_7;
    this->z = prd_3 + prd_9 - prd_6;
    return *this;
}

Real Quaternion::Norm( void ) const
{
    return Sqrt(NormSqure());
}

Real Quaternion::NormSqure( void ) const
{
    return this->w * this->w + this->x * this->x + this->y * this->y + this->z * this->z;
}

void Quaternion::Normalize( void )
{
    *this *= InvSqrt(NormSqure());
}

Quaternion Quaternion::UnitInvert( void ) const
{
    //因为这里的四元数只是为了支持旋转
    return Conjugate();
}

Quaternion Quaternion::Conjugate( void ) const
{
    Quaternion qResult;
    qResult.w = this->w;
    qResult.x = -this->x;
    qResult.y = -this->y;
    qResult.z = -this->z;
    return qResult;
}

Quaternion Quaternion::Invert( void ) const
{
    Quaternion qResult;
    Real norm2_inv = 1.0 / NormSqure(); 

    // and plug in
    qResult.w =  this->w * norm2_inv;
    qResult.x = -this->x * norm2_inv;
    qResult.y = -this->y * norm2_inv;
    qResult.z = -this->z * norm2_inv;

    return qResult;
}

std::ostream& operator<< (std::ostream& os,const Quaternion& q)
{
    boost::format fmt("Quaternion: (%10f,%10f,%10f,%10f)");
    fmt % q.w % q.x % q.y % q.z;
    os << fmt.str();

    return os;
}

Matrix Quaternion::ToMatrix( void ) const
{
    Real wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;

    Matrix m;
    //计算相关的系数
    x2 = this->x + this->x;
    y2 = this->y + this->y;
    z2 = this->z + this->z;

    xx = this->x * x2;
    xy = this->x * y2;
    xz = this->x * z2;
    yy = this->y * y2;
    yz = this->y * z2;
    zz = this->z * z2;
    wx = this->w * x2;
    wy = this->w * y2;
    wz = this->w * z2;
						    
    //将其填入矩阵位置
    m.m00 = 1.0 - (yy + zz);
    m.m10 = xy + wz;
    m.m20 = xz - wy;
    m.m30 = 0.0;
    m.m01 = xy - wz;
    m.m11 = 1.0 - (xx + zz);
    m.m21 = yz + wx;
    m.m31 = 0.0;
    m.m02 = xz + wy;
    m.m12 = yz - wx;
    m.m22 = 1.0 - (xx + yy);
    m.m32 = 0.0;
    m.m03 = 0.0;
    m.m13 = 0.0;
    m.m23 = 0.0;
    m.m33 = 1.0;

    return m;                                                     
}

