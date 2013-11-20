#ifndef _TRANSFORM_H
#define _TRANSFORM_H
#include "Math/Matrix.h"

class Quaternion;
class EulerAngle;
class Transform
    :public Matrix
{
public:
    Transform( void );
    Transform(const Matrix& m);

    void LoadIdentity( void );

    void Rotate(const Quaternion& q);
    void Rotate(const EulerAngle& angle);
    void Rotate(Real thetha,const Vector& v);
    void Rotate(Real xRot,Real yRot,Real zRot);

    void Translate(Real xTrans,Real yTrans,Real zTrans);
    void Translate(const Vector& vTrans);

    void Scale(Real s);
    void Scale(Real xScale,Real yScale,Real zScale);
    void Scale(const Vector& vScale);

    Transform Invert( void );
private:
    using Matrix::Invert;
    int32_t m_mType;
};
#endif

