#include <cstring>
#include <iomanip>
#include "Math/Matrix.h" 
#include "Math/Algorithm.h"
#include "Math/MathException.h"
const Matrix Matrix::Identity = Matrix(false);
const Matrix Matrix::Zero = Matrix(true);
Matrix::Matrix(const Homogenous& r0
    ,const Homogenous& r1
    ,const Homogenous& r2
    ,const Homogenous& r3)
:m00(r0.x),m01(r0.y),m02(r0.z),m03(r0.w)
,m10(r1.x),m11(r1.y),m12(r1.z),m13(r1.w)
,m20(r2.x),m21(r2.y),m22(r2.z),m23(r2.w)
,m30(r3.x),m31(r3.y),m32(r3.z),m33(r3.w)
{}

Matrix::Matrix(Real ele[16])
{
    std::memcpy(this,ele,sizeof(Matrix));
}

Matrix::Matrix(bool bZero)
{
    std::memset(this,0,sizeof(Matrix));
    if(!bZero)
    {
	m00 = m11 = m22 = m33 = 1.0;
    }
}

Matrix::Matrix(Real e00,Real e01,Real e02,Real e03
      ,Real e10,Real e11,Real e12,Real e13
      ,Real e20,Real e21,Real e22,Real e23
      ,Real e30,Real e31,Real e32,Real e33)
:m00(e00),m01(e01),m02(e02),m03(e03)
,m10(e10),m11(e11),m12(e12),m13(e13)
,m20(e20),m21(e21),m22(e22),m23(e23)
,m30(e30),m31(e31),m32(e32),m33(e33)
{}

Matrix Matrix::operator - ( void ) const
{
    return Matrix(-(*this)(0),-(*this)(1),-(*this)(2),-(*this)(3));
}

Matrix& Matrix::operator += (const Matrix& other)
{
    (*this)(0) += other(0);
    (*this)(1) += other(1);
    (*this)(2) += other(2);
    (*this)(3) += other(3);

    return *this;
}

Matrix& Matrix::operator -= (const Matrix& other)
{
    (*this)(0) -= other(0);
    (*this)(1) -= other(1);
    (*this)(2) -= other(2);
    (*this)(3) -= other(3);

    return *this;
}

Matrix& Matrix::operator *= (const Matrix& other)
{
    (*this)(0) *= other;
    (*this)(1) *= other;
    (*this)(2) *= other;
    (*this)(3) *= other;

    return *this;
}

Matrix& Matrix::operator += (Real k)
{
    (*this)(0) += k;
    (*this)(1) += k;
    (*this)(2) += k;
    (*this)(3) += k;

    return *this;
}

Matrix& Matrix::operator -= (Real k)
{
    (*this)(0) -= k;
    (*this)(1) -= k;
    (*this)(2) -= k;
    (*this)(3) -= k;

    return *this;
}

Matrix& Matrix::operator *= (Real k)
{
    (*this)(0) *= k;
    (*this)(1) *= k;
    (*this)(2) *= k;
    (*this)(3) *= k;

    return *this;
}

Matrix& Matrix::operator /= (Real k)
{
    Real reciprocal = 1.0 / k;
    *this *= reciprocal;

    return *this;
}

Matrix Matrix::Invert(MType eType) const
{
    Matrix invert(*this);
    switch(eType)
    {
	case MI_IDENTITY:
	    break;
	case MI_UNIT_SCALE:
	    {
                invert.m00 = invert.m11 = invert.m22 = 1 / m00;
		break;
	    }
	case MI_UNIT_SCALE_TRANSLATE:
	    {
		Real reciprocalScale = 1 / m00;
                invert.m00 = invert.m11 = invert.m22 = reciprocalScale;
		invert.m03 *= -reciprocalScale;
		invert.m13 *= -reciprocalScale;
		invert.m23 *= -reciprocalScale;
		break;
	    }
	case MI_SCALE:
	    {
		Real s0Xs1 = m00 * m11;
		Real s1Xs2 = m11 * m22;
		Real s0Xs2 = m00 * m22;
		Real reciprocalS0Xs1Xs2 = 1 / (s0Xs1 * m22);
		invert.m00 = reciprocalS0Xs1Xs2 * s1Xs2;
		invert.m11 = reciprocalS0Xs1Xs2 * s0Xs2;
		invert.m22 = reciprocalS0Xs1Xs2 * s0Xs1;
		break;
	    }
	case MI_ROTATE:
	    {
	        Swap(invert.m10,invert.m01);
	        Swap(invert.m20,invert.m02);
	        Swap(invert.m21,invert.m12);	
		break;
	    }
	case MI_TRANSLATE:
	    {
		invert.m03 = -this->m03;
		invert.m13 = -this->m13;
		invert.m23 = -this->m23;
		break;
	    }
	case MI_3X3DMATRIX:
            {
		Real det = Determinant(MI_AFFINE);
		if (Fabs(det) < 0.0)
		{
		    throw NoInverse();
		}

		// compute inverse to save divides
		Real det_inv = 1.0 / det;
		//
		// // compute inverse using m-1 = adjoint(m)/det(m)
		invert.m00 =  det_inv * (this->m11*this->m22 - this->m21*this->m12);
		invert.m10 = -det_inv * (this->m10*this->m22 - this->m20*this->m12);
		invert.m20 =  det_inv * (this->m10*this->m21 - this->m20*this->m11);
		
		invert.m01 = -det_inv * (this->m01*this->m22 - this->m21*this->m02);
		invert.m11 =  det_inv * (this->m00*this->m22 - this->m20*this->m02);
		invert.m21 = -det_inv * (this->m00*this->m21 - this->m20*this->m01);
		
		invert.m02 =  det_inv * (this->m01*this->m12 - this->m11*this->m02);
		invert.m12 = -det_inv * (this->m00*this->m12 - this->m10*this->m02);
		invert.m22 =  det_inv * (this->m00*this->m11 - this->m10*this->m01);
	    }
	    break;
	case MI_SCALE_TRANSLATE:
	    {
		Real s0Xs1 = this->m00 * this->m11;
		Real s1Xs2 = this->m11 * this->m22;
		Real s0Xs2 = this->m00 * this->m22;
		Real reciprocalS0Xs1Xs2 = 1 / (s0Xs1 * m22);
		invert.m00 = reciprocalS0Xs1Xs2 * s1Xs2;
		invert.m11 = reciprocalS0Xs1Xs2 * s0Xs2;
		invert.m22 = reciprocalS0Xs1Xs2 * s0Xs1;

		invert.m03 *= -invert.m00;
		invert.m13 *= -invert.m11;
		invert.m23 *= -invert.m22;
		break;
	    }
	case MI_ROTATE_TRANSLATE:
	    {
		Swap(invert.m10,invert.m01);
	        Swap(invert.m20,invert.m02);
	        Swap(invert.m21,invert.m12);	
                
	        invert.m03 = -(invert.m00 * this->m03 + invert.m01 * this->m13 + invert.m02 * this->m23);
                invert.m13 = -(invert.m10 * this->m03 + invert.m11 * this->m13 + invert.m12 * this->m23);
                invert.m23 = -(invert.m20 * this->m03 + invert.m21 * this->m13 + invert.m22 * this->m23);
		break;
	    }
	case MI_AFFINE:
	    {
		Real det = Determinant(MI_AFFINE);
		if (Fabs(det) < 0.0)
		{
		    throw NoInverse();
		}

		// compute inverse to save divides
		Real det_inv = 1.0 / det;
		//
		// // compute inverse using m-1 = adjoint(m)/det(m)
		invert.m00 =  det_inv * (this->m11*this->m22 - this->m21*this->m12);
		invert.m10 = -det_inv * (this->m10*this->m22 - this->m20*this->m12);
		invert.m20 =  det_inv * (this->m10*this->m21 - this->m20*this->m11);
		
		invert.m01 = -det_inv * (this->m01*this->m22 - this->m21*this->m02);
		invert.m11 =  det_inv * (this->m00*this->m22 - this->m20*this->m02);
		invert.m21 = -det_inv * (this->m00*this->m21 - this->m20*this->m01);
		
		invert.m02 =  det_inv * (this->m01*this->m12 - this->m11*this->m02);
		invert.m12 = -det_inv * (this->m00*this->m12 - this->m10*this->m02);
		invert.m22 =  det_inv * (this->m00*this->m11 - this->m10*this->m01);
		
	        invert.m03 = -(invert.m00 * this->m03 + invert.m01 * this->m13 + invert.m02 * this->m23);
                invert.m13 = -(invert.m10 * this->m03 + invert.m11 * this->m13 + invert.m12 * this->m23);
                invert.m23 = -(invert.m20 * this->m03 + invert.m21 * this->m13 + invert.m22 * this->m23);
	    }
	    break;
        default:
	    {
		Real det = Determinant(MI_GENERIC);
		if (Fabs(det) < 0.0)
		{
		    throw NoInverse();
		}

		// compute inverse to save divides
		Real det_inv = 1.0 / det;
		invert.m00 =  det_inv * Determinant3X3(m11,m12,m13,m21,m22,m23,m31,m32,m33);
		invert.m10 = -det_inv * Determinant3X3(m10,m12,m13,m20,m22,m23,m30,m32,m33);
		invert.m20 =  det_inv * Determinant3X3(m10,m11,m13,m20,m21,m23,m30,m31,m33);
		invert.m30 = -det_inv * Determinant3X3(m10,m11,m12,m20,m21,m22,m30,m31,m32);
                         
		invert.m01 = -det_inv * Determinant3X3(m01,m02,m03,m21,m22,m23,m31,m32,m33);
		invert.m11 =  det_inv * Determinant3X3(m00,m02,m03,m20,m22,m23,m30,m32,m33);
		invert.m21 = -det_inv * Determinant3X3(m00,m01,m03,m20,m21,m23,m30,m31,m33);
		invert.m31 =  det_inv * Determinant3X3(m00,m01,m02,m20,m21,m22,m30,m31,m32);
                         
		invert.m02 =  det_inv * Determinant3X3(m01,m02,m03,m11,m12,m13,m31,m32,m33);
		invert.m12 = -det_inv * Determinant3X3(m00,m02,m03,m10,m12,m13,m30,m32,m33);
		invert.m22 =  det_inv * Determinant3X3(m00,m01,m03,m10,m11,m13,m30,m31,m33);
		invert.m32 = -det_inv * Determinant3X3(m00,m01,m02,m10,m11,m12,m30,m31,m32);
                         
		invert.m03 = -det_inv * Determinant3X3(m01,m02,m03,m11,m12,m13,m21,m22,m23);
		invert.m13 =  det_inv * Determinant3X3(m00,m02,m03,m10,m12,m13,m20,m22,m23);
		invert.m23 = -det_inv * Determinant3X3(m00,m01,m03,m10,m11,m13,m20,m21,m23);
		invert.m33 =  det_inv * Determinant3X3(m00,m01,m02,m10,m11,m12,m20,m21,m22);
	    }
	    break;
    }

    return invert;
}

bool Matrix::operator == (const Matrix& m) const
{
    return (*this)(0) == m(0) && (*this)(1) == m(1) && (*this)(2) == m(2) && (*this)(3) == m(3);
}

Matrix Matrix::Transpose( void ) const
{
    Matrix result;
    result.m00 = this->m00;
    result.m01 = this->m10;
    result.m02 = this->m20;
    result.m03 = this->m30;

    result.m10 = this->m01;
    result.m11 = this->m11;
    result.m12 = this->m21;
    result.m13 = this->m31;

    result.m20 = this->m02;
    result.m21 = this->m12;
    result.m22 = this->m22;
    result.m23 = this->m32;

    result.m30 = this->m03;
    result.m31 = this->m13;
    result.m32 = this->m23;
    result.m33 = this->m33;
    
    return result;
}

Real Matrix::Determinant(MType eType) const
{
    Real result = 0.0;
    switch(eType)
    {
	case MI_IDENTITY:
	    result = 1.0;
	    break;
	case MI_UNIT_SCALE:
	case MI_UNIT_SCALE_TRANSLATE:
	    result = Pow(this->m00,3);
	    break;
	case MI_SCALE_TRANSLATE:
	case MI_SCALE:
	    result = this->m00 * this->m11 * this->m22;
	    break;
	case MI_ROTATE:
	case MI_TRANSLATE:
	case MI_ROTATE_TRANSLATE:
	    result = 1.0;
	    break;
	case MI_3X3DMATRIX:
	case MI_AFFINE:
	    result = Determinant3X3(m00,m01,m02,m10,m11,m12,m20,m21,m22);
	//    result = this->m00 * (this->m11 * this->m22 - this->m21 * this->m12)
	//	   - this->m01 * (this->m10 * this->m22 - this->m20 * this->m12)
	//	   + this->m02 * (this->m10 * this->m21 - this->m20 * this->m11);
	    break;
	case MI_GENERIC:
            result = m00 * (m11 * (m22 * m33 - m23 * m32) - m12 * (m21 *  m33 - m23 * m31)
		   + m13 * (m21 * m32 - m22  * m31)) - m01 * (m10 * (m22 * m33 - m23 * m32)
	           - m12 * (m20 * m33 - m23  * m30) + m13 * (m20 * m32 - m22 * m30))
	           + m02 * (m10 * (m21 *  m33 - m23 * m31) - m11 * (m20 * m33 - m23 * m30)
		   + m13 * (m20 * m31 - m21 * m30)) - m03 * (m10 * (m21 * m32 - m22 * m31)
		   - m11 * (m20 * m32 - m22 * m30) + m12 * (m20 * m31 - m21 * m30));
	    break;
    }
    return result;
}

std::ostream& operator<< (std::ostream& os,const Matrix& m)
{
#define SW std::setw(11)
    SAVE_INDENT(cindent);
    os  << std::setiosflags(std::ios::fixed | std::ios::right) << std::setprecision(6);
    os  << "Matrix: " << &m <<std::endl;
    os  << cindent.Shift(2) << "["<< SW << m.m00 << " , " << SW << m.m01 << " , " << SW << m.m02 << " , " << SW << m.m03 << "]" <<std::endl; 
    os	<< cindent.Shift(0) << "["<< SW << m.m10 << " , " << SW << m.m11 << " , " << SW << m.m12 << " , " << SW << m.m13 << "]" <<std::endl;
    os	<< cindent.Shift(0) << "["<< SW << m.m20 << " , " << SW << m.m21 << " , " << SW << m.m22 << " , " << SW << m.m23 << "]" <<std::endl;
    os	<< cindent.Shift(0) << "["<< SW << m.m30 << " , " << SW << m.m31 << " , " << SW << m.m32 << " , " << SW << m.m33 << "]" <<std::endl;
#undef SW

    return os;
}

