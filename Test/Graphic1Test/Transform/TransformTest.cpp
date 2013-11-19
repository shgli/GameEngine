#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE GameEngineTest
#include "Math/Algorithm.h"
#include "Math/MathException.h"
#include "Common/Common.h"
#include "Graphic/Transform.h"
#include <boost/test/unit_test.hpp>
#include "Common/Common.h"
BOOST_AUTO_TEST_CASE(MainTest)
{
}

BOOST_AUTO_TEST_SUITE(TransformTest)
    BOOST_AUTO_TEST_CASE(XRotateTest)
    {
        Transform trans1;
        Transform trans2;

        trans1.Rotate(PI_DIV_4,0.0,0.0);
        trans2.Rotate(PI_DIV_4,Vector(1.0,0.0,0.0));

        BOOST_CHECK_EQUAL(trans1,trans2);

        trans1.LoadIdentity();
        trans2.LoadIdentity();

        trans1.Rotate(PI3_DIV_4,0.0,0.0);
        trans2.Rotate(PI3_DIV_4,Vector(1.0,0.0,0.0));
        BOOST_CHECK_EQUAL(trans1,trans2);

        trans1.LoadIdentity();
        trans2.LoadIdentity();

        trans1.Rotate(PI5_DIV_4,0.0,0.0);
        trans2.Rotate(PI5_DIV_4,Vector(1.0,0.0,0.0));
        BOOST_CHECK_EQUAL(trans1,trans2);

        trans1.LoadIdentity();
        trans2.LoadIdentity();

        trans1.Rotate(PI7_DIV_4,0.0,0.0);
        trans2.Rotate(PI7_DIV_4,Vector(1.0,0.0,0.0));
        BOOST_CHECK_EQUAL(trans1,trans2);
    }

    BOOST_AUTO_TEST_CASE(YRotateTest)
    {
        Transform trans1;
        Transform trans2;

        trans1.Rotate(0.0,PI_DIV_4,0.0);
        trans2.Rotate(PI_DIV_4,Vector(0.0,1.0,0.0));

        BOOST_CHECK_EQUAL(trans1,trans2);

        trans1.LoadIdentity();
        trans2.LoadIdentity();

        trans1.Rotate(0.0,PI3_DIV_4,0.0);
        trans2.Rotate(PI3_DIV_4,Vector(0.0,1.0,0.0));
        BOOST_CHECK_EQUAL(trans1,trans2);

        trans1.LoadIdentity();
        trans2.LoadIdentity();

        trans1.Rotate(0.0,PI5_DIV_4,0.0);
        trans2.Rotate(PI5_DIV_4,Vector(0.0,1.0,0.0));
        BOOST_CHECK_EQUAL(trans1,trans2);

        trans1.LoadIdentity();
        trans2.LoadIdentity();

        trans1.Rotate(0.0,PI7_DIV_4,0.0);
        trans2.Rotate(PI7_DIV_4,Vector(0.0,1.0,0.0));
        BOOST_CHECK_EQUAL(trans1,trans2);
    }

    BOOST_AUTO_TEST_CASE(ZRotateTest)
    {
        Transform trans1;
        Transform trans2;

        trans1.Rotate(0.0,0.0,PI_DIV_4);
        trans2.Rotate(PI_DIV_4,Vector(0.0,0.0,1.0));

        BOOST_CHECK_EQUAL(trans1,trans2);

        trans1.LoadIdentity();
        trans2.LoadIdentity();

        trans1.Rotate(0.0,0.0,PI3_DIV_4);
        trans2.Rotate(PI3_DIV_4,Vector(0.0,0.0,1.0));
        BOOST_CHECK_EQUAL(trans1,trans2);

        trans1.LoadIdentity();
        trans2.LoadIdentity();

        trans1.Rotate(0.0,0.0,PI5_DIV_4);
        trans2.Rotate(PI5_DIV_4,Vector(0.0,0.0,1.0));
        BOOST_CHECK_EQUAL(trans1,trans2);

        trans1.LoadIdentity();
        trans2.LoadIdentity();

        trans1.Rotate(0.0,0.0,PI7_DIV_4);
        trans2.Rotate(PI7_DIV_4,Vector(0.0,0.0,1.0));
        BOOST_CHECK_EQUAL(trans1,trans2);

    }
BOOST_AUTO_TEST_SUITE_END()

