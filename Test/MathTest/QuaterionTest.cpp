#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "Math/Algorithm.h"
#include "Math/MathException.h"
#include "Common/Common.h"
#include "Math/Quaternion.h"

BOOST_AUTO_TEST_SUITE(QuaternionTest)
    BOOST_AUTO_TEST_CASE(ConstructTest)
    {
        Vector v(1,1,1);
        v.Normalize();	
	Quaternion q(PI_DIV_2,v);
	BOOST_CHECK_EQUAL(q.w, Cos(PI_DIV_4));
    	BOOST_CHECK_EQUAL(q.x, v.x * Sin(PI_DIV_4));
	BOOST_CHECK_EQUAL(q.y, v.y * Sin(PI_DIV_4));
	BOOST_CHECK_EQUAL(q.z, v.z * Sin(PI_DIV_4));
    }

    BOOST_AUTO_TEST_CASE(EulerConstructTest)
    {
        Vector v(1,1,1);
        v.Normalize();	
	Quaternion q(PI_DIV_2,v);
	//BOOST_CHECK_EQUAL(v.w, Cos(PI_DIV_4));
    	//BOOST_CHECK_EQUAL(v.x, v.x * Sin(PI_DIV_4));
	//BOOST_CHECK_EQUAL(v.y, v.y * Sin(PI_DIV_4));
	//BOOST_CHECK_EQUAL(v.z, v.z * Sin(PI_DIV_4));
    }

    BOOST_AUTO_TEST_CASE(ToVectorThethaTest)
    {
        Vector v(1,1,1);
        v.Normalize();	
	Quaternion q(PI_DIV_2,v);

	Real thetha;
	Vector v1;
	q.ToVectorThetha(thetha,v1);

	BOOST_CHECK_EQUAL(thetha,PI_DIV_2);
	BOOST_CHECK_EQUAL(v,v1);
    }

    BOOST_AUTO_TEST_CASE(QuaternionAdd)
    {
	Quaternion q1;
	q1.w = 1;
	q1.x = 2;
	q1.y = 3;
	q1.z = 4;

        Quaternion q2;
    	q2.w = 5;
	q2.x = 6;
	q2.y = 7;
	q2.z = 8;

	Quaternion sum = q1 + q2;
	BOOST_CHECK_EQUAL(sum.w,6);
	BOOST_CHECK_EQUAL(sum.x,8);
	BOOST_CHECK_EQUAL(sum.y,10);
	BOOST_CHECK_EQUAL(sum.z,12);
    }

    BOOST_AUTO_TEST_CASE(QuaternionSub)
    {
	Quaternion q1;
	q1.w = 1;
	q1.x = 2;
	q1.y = 3;
	q1.z = 4;

        Quaternion q2;
    	q2.w = 5;
	q2.x = 6;
	q2.y = 7;
	q2.z = 8;

	Quaternion sum = q1 - q2;
	BOOST_CHECK_EQUAL(sum.w,-4);
	BOOST_CHECK_EQUAL(sum.x,-4);
	BOOST_CHECK_EQUAL(sum.y,-4);
	BOOST_CHECK_EQUAL(sum.z,-4);
    }

    BOOST_AUTO_TEST_CASE(QuaternionConjugate)
    {
	Quaternion q1;
	q1.w = 1;
	q1.x = 2;
	q1.y = 3;
	q1.z = 4;

	Quaternion conj = q1.Conjugate();
	BOOST_CHECK_EQUAL(conj.w,1);
	BOOST_CHECK_EQUAL(conj.x,-2);
	BOOST_CHECK_EQUAL(conj.y,-3);
	BOOST_CHECK_EQUAL(conj.z,-4);
    }

    BOOST_AUTO_TEST_CASE(QuaternionScale)
    {
    	Quaternion q1;
	q1.w = 1;
	q1.x = 2;
	q1.y = 3;
	q1.z = 4;

	Quaternion scale = 5 * q1;
	BOOST_CHECK_EQUAL(scale.w,5);
	BOOST_CHECK_EQUAL(scale.x,10);
	BOOST_CHECK_EQUAL(scale.y,15);
	BOOST_CHECK_EQUAL(scale.z,20);

    }

    BOOST_AUTO_TEST_CASE(QuaternionNorm)
    {
    	Quaternion q1;
	q1.w = 1;
	q1.x = 2;
	q1.y = 3;
	q1.z = 4;

	Real norm = q1.Norm();
        BOOST_CHECK_EQUAL(norm,5.47722557);
    }

    BOOST_AUTO_TEST_CASE(QuaternionNormalize)
    {
	Quaternion q1;
   	q1.w = 1;
	q1.x = 2;
	q1.y = 3;
	q1.z = 4;

	q1.Normalize();
	BOOST_CHECK_EQUAL(q1.w,0.18257418583506);
	BOOST_CHECK_EQUAL(q1.x,0.36514837167011);
	BOOST_CHECK_EQUAL(q1.y,0.54772255750517);
	BOOST_CHECK_EQUAL(q1.z,0.73029674334022);
     }

     BOOST_AUTO_TEST_CASE(QuaternionInverse)
     {
	Quaternion q1;
   	q1.w = 1;
	q1.x = 2;
	q1.y = 3;
	q1.z = 4;

	Quaternion q2 = q1.Invert();

	Real normRoot = q1.NormSqure();
	BOOST_CHECK_EQUAL(normRoot,30);

     	BOOST_CHECK_EQUAL(q2.w,1/normRoot);
	BOOST_CHECK_EQUAL(q2.x,-2/normRoot);
	BOOST_CHECK_EQUAL(q2.y,-3/normRoot);
	BOOST_CHECK_EQUAL(q2.z,-4/normRoot);
    }

    BOOST_AUTO_TEST_CASE(QuaternionUnitInvert)
    {
        Vector v(1,1,1);
        v.Normalize();	
	Quaternion q(PI_DIV_2,v);

	Quaternion inv = q.UnitInvert();
	Real normRoot = q.NormSqure();
	BOOST_CHECK_EQUAL(normRoot,1.0);
	BOOST_CHECK_EQUAL(inv.w, q.w/normRoot);
	BOOST_CHECK_EQUAL(inv.x,-q.x/normRoot);
	BOOST_CHECK_EQUAL(inv.y,-q.y/normRoot);
	BOOST_CHECK_EQUAL(inv.z,-q.z/normRoot);

    }

    BOOST_AUTO_TEST_CASE(QuaternionMult)
    {
        Quaternion q1(1,2,3,4),q2(5,6,7,8);
	Quaternion mul = q1 * q2;

	BOOST_CHECK_EQUAL(mul.w,-60);
	BOOST_CHECK_EQUAL(mul.x,12);
	BOOST_CHECK_EQUAL(mul.y,30);
	BOOST_CHECK_EQUAL(mul.z,24);
    }

    BOOST_AUTO_TEST_CASE(QuadterToMatrix)
    {
        Quaternion q(PI,Vector(0,1,0));
        Matrix mat = q.ToMatrix();

        Matrix desMat = Matrix(-1.0, 0.0, 0.0, 0.0
                              , 0.0, 1.0, 0.0, 0.0
                              , 0.0, 0.0,-1.0, 0.0
                              , 0.0, 0.0, 0.0, 1.0);
        BOOST_CHECK_EQUAL(mat,desMat);


        Quaternion q1(PI_DIV_2,Vector(0,1,0));
        mat = q1.ToMatrix();
        Matrix desMat1 = Matrix( 0.0, 0.0, 1.0, 0.0
                              , 0.0, 1.0, 0.0, 0.0
                              , 0.0, 0.0, 0.0, 0.0
                              ,-1.0, 0.0, 0.0, 1.0);

    }

BOOST_AUTO_TEST_SUITE_END()

