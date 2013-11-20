#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MathTest
#include <boost/test/unit_test.hpp>
#include "Math/Algorithm.h"
#include "Math/MathException.h"
#include "Common/Common.h"
BOOST_AUTO_TEST_CASE(MainTest)
{
}

BOOST_AUTO_TEST_SUITE(MathSuitTest)
    BOOST_AUTO_TEST_CASE(SqrtTest)
    {
	BOOST_CHECK_EQUAL(1.11,Sqrt(1.2321));
	BOOST_CHECK_EQUAL(2.5,Sqrt(6.25));
	BOOST_CHECK_EQUAL(0,Sqrt(0));
	BOOST_CHECK_THROW(Sqrt(-1),NoDefinedOp);
    }

    BOOST_AUTO_TEST_CASE(InvSqrtTest)
    {
        BOOST_CHECK_EQUAL(1/1.11,InvSqrt(1.2321));
        BOOST_CHECK_EQUAL(1/2.5,InvSqrt(6.25));
        BOOST_CHECK_THROW(InvSqrt(-1),NoDefinedOp);
    
    }

    BOOST_AUTO_TEST_CASE(FabsTest)
    {
        BOOST_CHECK_EQUAL(Fabs(-1.0),1.0);
        BOOST_CHECK_EQUAL(Fabs(1.0),1.0);
        BOOST_CHECK_EQUAL(Fabs(0.0),0.0);
    }

    BOOST_AUTO_TEST_CASE(CosTest)
    {
        BOOST_CHECK_EQUAL(Cos(0.0),1);
        BOOST_CHECK_EQUAL(Cos(PI/6),0.866025403);
        BOOST_CHECK_EQUAL(Cos(PI/4),0.707106780);
        BOOST_CHECK_EQUAL(Cos(PI/3),0.5);
        BOOST_CHECK_EQUAL(Cos(PI/2),0.0);
        BOOST_CHECK_EQUAL(Cos(PI*3/4),-0.70710678);
        BOOST_CHECK_EQUAL(Cos(PI),-1.0);
        BOOST_CHECK_EQUAL(Cos(PI*5/4),-0.707106780);
        BOOST_CHECK_EQUAL(Cos(PI*3/2),0.0);
        BOOST_CHECK_EQUAL(Cos(PI*7/4),0.70710678);
        BOOST_CHECK_EQUAL(Cos(PI2),1);
    }

    BOOST_AUTO_TEST_CASE(SinTest)
    {
        BOOST_CHECK_EQUAL(Sin(0.0),0.0);
        BOOST_CHECK_EQUAL(Sin(PI/6),0.5);
        BOOST_CHECK_EQUAL(Sin(PI/4),0.707106780);
        BOOST_CHECK_EQUAL(Sin(PI/3),0.86602540);
        BOOST_CHECK_EQUAL(Sin(PI/2),1.0);
        BOOST_CHECK_EQUAL(Sin(PI*3/4),0.70710678);
        BOOST_CHECK_EQUAL(Sin(PI),0.0);
        BOOST_CHECK_EQUAL(Sin(PI*5/4),-0.707106780);
        BOOST_CHECK_EQUAL(Sin(PI*3/2),-1.0);
        BOOST_CHECK_EQUAL(Sin(PI*7/4),-0.70710678);
        BOOST_CHECK_EQUAL(Sin(PI2),0.0);
    }

    BOOST_AUTO_TEST_CASE(RoundTest)
    {
        BOOST_CHECK_EQUAL(Round(1.2),1);
        BOOST_CHECK_EQUAL(Round(-1.2),-1);
        BOOST_CHECK_EQUAL(Round(1.0),1);
        BOOST_CHECK_EQUAL(Round(-1.0),-1);
    }

    BOOST_AUTO_TEST_CASE(PowTest)
    {
        BOOST_CHECK_EQUAL(Pow(1.2,2),1.44);
        BOOST_CHECK_EQUAL(Pow(1.1,3),1.331);
        BOOST_CHECK_EQUAL(Pow(1.2,0),1.0);
        BOOST_CHECK_EQUAL(Pow(1.3,1),1.3);
        BOOST_CHECK_EQUAL(Pow(1.32,8),9.21703952);
        BOOST_CHECK_EQUAL(Pow(1.32,7),6.98260569);
    }
BOOST_AUTO_TEST_SUITE_END()

