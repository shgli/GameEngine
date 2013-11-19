#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "Math/Algorithm.h"
#include "Math/MathException.h"
#include "Common/Common.h"
#include "Math/Homogenous.h"
BOOST_AUTO_TEST_SUITE(VectorTest)
    BOOST_AUTO_TEST_CASE(VectorAddTest)
    {
        Vector v1(1,2,3);
        Vector v2(5,6,7);

        Vector v3 = v1 + v2;
        BOOST_CHECK_EQUAL(v3,Vector(6,8,10));
    }

    BOOST_AUTO_TEST_CASE(VectorSubTest)
    {
        Vector v1(1,2,3);
        Vector v2(5,6,7);

        Vector v3 = v1 - v2;
        BOOST_CHECK_EQUAL(v3,Vector(-4,-4,-4));
    }

    BOOST_AUTO_TEST_CASE(VectorScaleTest)
    {
        Vector v1(1,2,3);

        Real k = 3.0;
        Vector v3 = k * v1;
        Vector v4 = v1 * 3.0;
        BOOST_CHECK_EQUAL(v3,Vector(3,6,9));
        BOOST_CHECK_EQUAL(v4,Vector(3,6,9));
    }

    BOOST_AUTO_TEST_CASE(VectorMinusTest)
    {
        Vector v1(1,2,3);

        Vector v3 = -v1; 
        BOOST_CHECK_EQUAL(v3,Vector(-1,-2,-3));
    }

    BOOST_AUTO_TEST_CASE(VectorDotTest)
    {
        Vector v1(1,2,3);
        Vector v2(2,3,8);
        Real dotV = v1.Dot(v2);
        BOOST_CHECK_EQUAL(dotV,32);
    }

    BOOST_AUTO_TEST_CASE(VectorCrossTest)
    {
        Vector v1(1,2,3);
        Vector v2(2,3,8);
        Vector cross= v1.Cross(v2);
        BOOST_CHECK_EQUAL(cross,Vector(7,-2,-1));
    }

    BOOST_AUTO_TEST_CASE(VectorLengthTest)
    {
        Vector v2(3,4,0);
        BOOST_CHECK_EQUAL(v2.Norm(),5.0);
    }

    BOOST_AUTO_TEST_CASE(VectorNormalizeTest)
    {
	Vector v(3,4,2);
	v.Normalize();
	BOOST_CHECK_EQUAL(v.Norm(),1.0);
    }
BOOST_AUTO_TEST_SUITE_END()

