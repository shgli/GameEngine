#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "Math/Algorithm.h"
#include "Math/MathException.h"
#include "Common/Common.h"
#include "Math/Matrix.h"
BOOST_AUTO_TEST_SUITE(MatrixTest)
    BOOST_AUTO_TEST_CASE(MatrixIndex)
    {
        Matrix m1(1,2,3,2
                 ,8,2,8,0
                 ,4,8,7,1
                 ,3,9,1,2);
	BOOST_CHECK_EQUAL(m1(0,0),1.0);
	BOOST_CHECK_EQUAL(m1(0,1),2.0);
	BOOST_CHECK_EQUAL(m1(0,2),3.0);
	BOOST_CHECK_EQUAL(m1(0,3),2.0);

    	BOOST_CHECK_EQUAL(m1(1,0),8.0);
	BOOST_CHECK_EQUAL(m1(1,1),2.0);
	BOOST_CHECK_EQUAL(m1(1,2),8.0);
	BOOST_CHECK_EQUAL(m1(1,3),0.0);

	BOOST_CHECK_EQUAL(m1(2,0),4.0);
	BOOST_CHECK_EQUAL(m1(2,1),8.0);
	BOOST_CHECK_EQUAL(m1(2,2),7.0);
	BOOST_CHECK_EQUAL(m1(2,3),1.0);

	BOOST_CHECK_EQUAL(m1(3,0),3.0);
	BOOST_CHECK_EQUAL(m1(3,1),9.0);
	BOOST_CHECK_EQUAL(m1(3,2),1.0);
	BOOST_CHECK_EQUAL(m1(3,3),2.0);
    }

    BOOST_AUTO_TEST_CASE(MatrixAdd)
    {
        Matrix m1(1,2,3,2
                 ,8,2,8,0
                 ,4,8,7,1
                 ,3,9,1,2);
        Matrix m2(7,5,1,9
                 ,8,2,8,2
                 ,2,6,3,0
                 ,2,8,3,9);

        Matrix add = m1 + m2;

        BOOST_CHECK_EQUAL(add,Matrix(8,7,4,11
                                    ,16,4,16,2
                                    ,6,14,10,1
                                    ,5,17,4,11));
    }


    BOOST_AUTO_TEST_CASE(MatrixSub)
    {
        Matrix m1(1,2,3,2
                 ,8,2,8,0
                 ,4,8,7,1
                 ,3,9,1,2);
        Matrix m2(7,5,1,9
                 ,8,2,8,2
                 ,2,6,3,0
                 ,2,8,3,9);

        Matrix sub = m1 - m2;

        BOOST_CHECK_EQUAL(sub,Matrix(-6,-3,2,-7
                                    ,0,0,0,-2
                                    ,2,2,4,1
                                    ,1,1,-2,-7));
    }

    BOOST_AUTO_TEST_CASE(MatrixMult)
    {
        Matrix m1(1,2,3,2
                 ,8,2,8,0
                 ,4,8,7,1
                 ,3,9,1,2);
        Matrix m2(7,5,1,9
                 ,8,2,8,2
                 ,2,6,3,0
                 ,2,8,3,9);

        Matrix mult = m1 * m2;

        BOOST_CHECK_EQUAL(mult,Matrix(33,43,32,31
		                    ,88,92,48,76
				    ,108,86,92,61
                                    ,99 ,55,84,63)); 

    }

    BOOST_AUTO_TEST_CASE(MatrixScale)
    {
        Matrix m1(1,2,3,2
                 ,8,2,8,0
                 ,4,8,7,1
                 ,3,9,1,2);
        Matrix scale = 3 * m1;
 
        BOOST_CHECK_EQUAL(scale,Matrix(3 ,6 ,9 ,6
                                      ,24,6 ,24,0
                                      ,12,24,21,3
                                      ,9 ,27,3 ,6));

    }

    BOOST_AUTO_TEST_CASE(MatrixTranspose)
    {
        Matrix m1(1,2,3,2
                 ,8,2,8,0
                 ,4,8,7,1
                 ,3,9,1,2);
        Matrix scale = m1.Transpose();
 
        BOOST_CHECK_EQUAL(scale,Matrix( 1,8,4,3 
                                      , 2,2,8,9
                                      , 3,8,7,1
                                      , 2,0,1,2));

    }

    BOOST_AUTO_TEST_CASE(MatrixMultVec)
    {
        Matrix m1(1,2,3,2
                 ,8,2,8,0
                 ,4,8,7,1
                 ,3,9,1,2);

        Homogenous v(4,8,2,1);

        Homogenous v1 = m1 * v;
        BOOST_CHECK_EQUAL(v1,Homogenous(28,64,95,88));
    }

    BOOST_AUTO_TEST_CASE(VecMultMatrix)
    {
        Matrix m1(1,2,3,2
                 ,8,2,8,0
                 ,4,8,7,1
                 ,3,9,1,2);

        Homogenous v(4,8,2,1);

        Homogenous v1 = v * m1;
        BOOST_CHECK_EQUAL(v1,Homogenous(79,49,91,12));
    }

    BOOST_AUTO_TEST_CASE(MatrixUnitScaleDeterminant)
    {
        Matrix m1(2,0,0,0
		 ,0,2,0,0
		 ,0,0,2,0
		 ,0,0,0,1);
	
	Real det = m1.Determinant(MI_UNIT_SCALE);
	BOOST_CHECK_EQUAL(det,8);
    }

    BOOST_AUTO_TEST_CASE(MatrixScaleDeterminant)
    {
        Matrix m(2,0,0,0
                ,0,3,0,0
                ,0,0,9,0
                ,0,0,0,1);
        Real det = m.Determinant(MI_SCALE);
        BOOST_CHECK_EQUAL(det,54);
    }

    BOOST_AUTO_TEST_CASE(MatrixRotateDeterminant)
    {
        Matrix m1(1,0        ,0         ,0
                 ,0,Cos(PI/4),-Sin(PI/4),0
                 ,0,Sin(PI/4),Cos(PI/4) ,0
                 ,0,0,0,1);

        Real det = m1.Determinant(MI_ROTATE);
        BOOST_CHECK_EQUAL(det,1.0);
    }

    BOOST_AUTO_TEST_CASE(MatrixTranslateDeterminant)
    {
        Matrix m(1,0,0,7
                ,0,1,0,3
                ,0,0,1,2
                ,0,0,0,1);
        Real det = m.Determinant(MI_TRANSLATE);
        BOOST_CHECK_EQUAL(det,1.0);
    }

    BOOST_AUTO_TEST_CASE(MatrixUNITScaleTranslateDeterminant)
    {
        Matrix m(3,0,0,7
                ,0,3,0,3
                ,0,0,3,2
                ,0,0,0,1);
        Real det = m.Determinant(MI_UNIT_SCALE_TRANSLATE);
        BOOST_CHECK_EQUAL(det,27);
    }

    BOOST_AUTO_TEST_CASE(MatrixScaleTranslateDeterminant)
    {
        Matrix m(2,0,0,7
                ,0,3,0,3
                ,0,0,8,2
                ,0,0,0,1);
        Real det = m.Determinant(MI_SCALE_TRANSLATE);
        BOOST_CHECK_EQUAL(det,48);
    }

    BOOST_AUTO_TEST_CASE(MatrixRotateTranslateDeterminant)
    {
        Matrix m1(1,0        ,0         ,2
                 ,0,Cos(PI/4),-Sin(PI/4),8
                 ,0,Sin(PI/4),Cos(PI/4) ,3
                 ,0,0,0,1);
        Real det = m1.Determinant(MI_ROTATE_TRANSLATE);
        BOOST_CHECK_EQUAL(det,1.0);
    }

    BOOST_AUTO_TEST_CASE(MatrixAffineTranslateDeterminant)
    {
        Matrix m(2,3,7,8
                ,2,1,3,2
                ,1,3,8,3
                ,0,0,0,1);
        Real det = m.Determinant(MI_AFFINE);
        BOOST_CHECK_EQUAL(det,-6.0);
    }

    BOOST_AUTO_TEST_CASE(MatrixDeterminant)
    {
        Matrix m1(1,2,3,2
                 ,8,2,8,0
                 ,4,8,7,1
                 ,3,9,1,2);

        BOOST_CHECK_EQUAL(m1.Determinant(),600);
    }

    BOOST_AUTO_TEST_CASE(MatrixInverseUnitScale)
    {
        Matrix m1(2,0,0,0
                 ,0,2,0,0
                 ,0,0,2,0
                 ,0,0,0,1);

        Matrix revert = m1.Invert(MI_UNIT_SCALE);
        BOOST_CHECK_EQUAL(m1 * revert,Matrix::Identity);
    }

    BOOST_AUTO_TEST_CASE(MatrixInverseTranslate)
    {
        Matrix m1(1,0,0,2
                 ,0,1,0,5
                 ,0,0,1,7
                 ,0,0,0,1);

        Matrix revert = m1.Invert(MI_TRANSLATE);
        BOOST_CHECK_EQUAL(m1 * revert,Matrix::Identity);
    }

    BOOST_AUTO_TEST_CASE(MatrixInverseUnitScaleTranslate)
    {
        Matrix m1(2,0,0,7
                 ,0,2,0,8
                 ,0,0,2,2
                 ,0,0,0,1);

        Matrix revert = m1.Invert(MI_UNIT_SCALE_TRANSLATE);
        BOOST_CHECK_EQUAL(m1 * revert,Matrix::Identity);
    }

    BOOST_AUTO_TEST_CASE(MatrixInverseRotate)
    {
        Matrix m1(1,0        ,0         ,0
                 ,0,Cos(PI/4),-Sin(PI/4),0
                 ,0,Sin(PI/4),Cos(PI/4) ,0
                 ,0,0,0,1);

        Matrix revert = m1.Invert(MI_ROTATE);
        BOOST_CHECK_EQUAL(m1 * revert,Matrix::Identity);
    }

    BOOST_AUTO_TEST_CASE(MatrixInverseScale)
    {
        Matrix m1(1,0,0,0
                 ,0,2,0,0
                 ,0,0,7,0
                 ,0,0,0,1);

        Matrix revert = m1.Invert(MI_SCALE);
        BOOST_CHECK_EQUAL(m1 * revert,Matrix::Identity);
    }

    BOOST_AUTO_TEST_CASE(MatrixRoateTranslate)
    {
        Matrix m1(1,0        ,0         ,2
                 ,0,Cos(PI/4),-Sin(PI/4),8
                 ,0,Sin(PI/4),Cos(PI/4) ,3
                 ,0,0,0,1);

        Matrix revert = m1.Invert(MI_ROTATE_TRANSLATE);
        BOOST_CHECK_EQUAL(m1 * revert,Matrix::Identity);
    }

    BOOST_AUTO_TEST_CASE(MatrixInverseScaleTranslate)
    {
        Matrix m1(2,0,0,7
                 ,0,7,0,8
                 ,0,0,3,2
                 ,0,0,0,1);

        Matrix revert = m1.Invert(MI_SCALE_TRANSLATE);
        BOOST_CHECK_EQUAL(m1 * revert,Matrix::Identity);
    }

    BOOST_AUTO_TEST_CASE(MatrixInverseAffine)
    {
        Matrix m1(2,7,2,7
                 ,0,7,1,8
                 ,9,3,3,2
                 ,0,0,0,1);

        Matrix revert = m1.Invert(MI_AFFINE);
	//std::cout<<revert<<std::endl;
        BOOST_CHECK_EQUAL(m1 * revert,Matrix::Identity);
    }

    BOOST_AUTO_TEST_CASE(MatrixInverseGeneric)
    {
        Matrix m1(1,2,3,2
                 ,8,2,8,0
                 ,4,8,7,1
                 ,3,9,1,2);

        Matrix revert = m1.Invert(MI_GENERIC);
        BOOST_CHECK_EQUAL(revert * m1,Matrix::Identity);
    }
BOOST_AUTO_TEST_SUITE_END()

