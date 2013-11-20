#ifndef _MATRIX_HPP
#define _MATRIX_HPP
#include "Common/Common.h"
#include "Math/Homogenous.h"

enum MType
{
    MI_IDENTITY =  0x0000,
    //automic type
    MI_UNIT_SCALE = 0x0001,
    MI_SCALE = 0x0003,        //MI_UNIT_SCALE | MI_SCALE == MI_SCALE
    MI_ROTATE = 0x0006,       //MI_ROTATE | MI_UNIT_SCALE == MI_ROTATE | MI_SCALE
    MI_TRANSLATE = 0x0008,

    //composite type
    MI_3X3DMATRIX = MI_SCALE | MI_ROTATE,  //or MI_UNIT_SCALE | MI_ROTATE
    MI_UNIT_SCALE_TRANSLATE = MI_UNIT_SCALE | MI_TRANSLATE,
    MI_SCALE_TRANSLATE = MI_SCALE | MI_TRANSLATE,
    MI_ROTATE_TRANSLATE = MI_ROTATE | MI_TRANSLATE,

    MI_AFFINE = MI_3X3DMATRIX | MI_TRANSLATE,
    MI_GENERIC
};

class Matrix
    :public boost::additive<Matrix
    ,boost::multipliable<Matrix
    ,boost::multiplicative<Matrix,Real
    > > >
{
public:
   Real m00,m01,m02,m03,
	m10,m11,m12,m13,
	m20,m21,m22,m23,
	m30,m31,m32,m33;

    static const Matrix Identity;
    static const Matrix Zero;

    Matrix(const Homogenous& r0
           ,const Homogenous& r1
           ,const Homogenous& r2
           ,const Homogenous& r3);

    Matrix(Real ele[16]);

    explicit Matrix(bool bZero = true);  //bZero = true -> all element is zero else you will get a identity matrix

    Matrix(Real e00,Real e01,Real e02,Real e03
          ,Real e10,Real e11,Real e12,Real e13
          ,Real e20,Real e21,Real e22,Real e23
          ,Real e30,Real e31,Real e32,Real e33);
    
    Matrix operator - ( void ) const;

    Matrix& operator += (const Matrix& other);
    Matrix& operator -= (const Matrix& other);
    Matrix& operator *= (const Matrix& other);

    Matrix& operator += (Real k);
    Matrix& operator -= (Real k);
    Matrix& operator *= (Real k);
    Matrix& operator /= (Real k);

    bool operator == (const Matrix& m) const;

    Matrix Invert(MType eType = MI_GENERIC) const;
    Matrix Transpose( void ) const;

    inline const Real& operator() (int iRow,int iCol) const 
    {
       	return ((const Real*)this)[(iRow << 2) + iCol];
    }

    inline Real& operator() (int iRow,int iCol) 
    {
       	return ((Real*)this)[(iRow << 2) + iCol];
    }

    inline const Homogenous& operator() (int iRow) const 
    {
	return ((const Homogenous*)this)[iRow];

    }

    inline Homogenous& operator() (int iRow) 
    {
	return const_cast<Homogenous&>(((const Matrix&)(*this))(iRow));
    }
 
    Real Determinant(MType eType = MI_GENERIC) const;


    friend std::ostream& operator<< (std::ostream& os,const Matrix& m);
};

inline Real Determinant3X3(Real m00,Real m01,Real m02
	,Real m10,Real m11,Real m12
	,Real m20,Real m21,Real m22)
{
    Real result = m00 * (m11 * m22 - m21 * m12)
		- m01 * (m10 * m22 - m20 * m12)
		+ m02 * (m10 * m21 - m20 * m11);
    return result;
}
#endif

