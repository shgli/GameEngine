#include "Math/Math.h"
#include "Graphic/Transform.h"
Transform::Transform(const Matrix& m)
    :Matrix(m)
{}

Transform::Transform( void )
    :Matrix(false)
    ,m_mType(MI_IDENTITY)
{}

void Transform::Rotate(const Quaternion& q)
{
    Matrix m = q.ToMatrix();
    *this = m * *this;    
    m_mType |= MI_ROTATE;
}

void Transform::Rotate(const EulerAngle& angle)
{
    //Rotate(Quaternion(angle));
    Rotate(angle.x,angle.y,angle.z);
}

void Transform::Rotate(Real thetha,const Vector& v)
{
    Rotate(Quaternion(thetha,v));
}

void Transform::Rotate(Real xRot,Real yRot,Real zRot)
{
    //Rotate(EulerAngle(xRot,yRot,zRot));
    Real cosX = Cos(xRot),sinX = Sin(xRot);
    Matrix rotX = Matrix( 1.0, 0.0, 0.0, 0.0
                        , 0.0,cosX,-sinX,0.0
                        , 0.0,sinX,cosX, 0.0
                        , 0.0, 0.0, 0.0, 1.0);

    Real cosY = Cos(yRot),sinY = Sin(yRot);
    Matrix rotY = Matrix(cosY, 0.0,sinY, 0.0
                        , 0.0, 1.0, 0.0,0.0
                        ,-sinY,0.0,cosY, 0.0
                        , 0.0, 0.0, 0.0, 1.0);

    Real cosZ = Cos(zRot),sinZ = Sin(zRot);
    Matrix rotZ = Matrix(cosZ,-sinZ,0.0, 0.0
                        ,sinZ,cosZ, 0.0, 0.0
                        , 0.0, 0.0, 1.0, 0.0
                        , 0.0, 0.0, 0.0, 1.0);

    *this = rotX * rotY * rotZ * *this;
    m_mType != MI_ROTATE;
}

void Transform::Translate(Real xTrans,Real yTrans,Real zTrans)
{
    this->m03 += xTrans;
    this->m13 += yTrans;
    this->m23 += zTrans;
    //Matrix m(false);
    //m.m03 = xTrans;
    //m.m13 = yTrans;
    //m.m23 = zTrans;
    //*this = m * *this;
    m_mType |= MI_TRANSLATE;
}

void Transform::Translate(const Vector& vTrans)
{
    Translate(vTrans.x,vTrans.y,vTrans.z);
}

void Transform::Scale(Real s)
{
    (*this)(0) *= s;
    (*this)(1) *= s;
    (*this)(2) *= s;
    m_mType |= MI_UNIT_SCALE;
}

void Transform::Scale(Real xScale,Real yScale,Real zScale)
{
    (*this)(0) *= xScale;
    (*this)(1) *= yScale;
    (*this)(2) *= zScale;
    m_mType |= MI_SCALE;
}

void Transform::Scale(const Vector& vScale)
{
    Scale(vScale.x,vScale.y,vScale.z);
}

void Transform::LoadIdentity( void )
{
    *this = Matrix::Identity;
    m_mType = MI_IDENTITY;
}

Transform Transform::Invert( void )
{
    return Transform(Matrix::Invert(static_cast<MType>(m_mType)));
}

