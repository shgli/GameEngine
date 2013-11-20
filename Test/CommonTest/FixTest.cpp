#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE GameEngineTest
#include <boost/test/unit_test.hpp>
#include "Common/Common.h"
BOOST_AUTO_TEST_CASE(MainTest)
{
}

#include <iostream>
BOOST_AUTO_TEST_SUITE(Fix16Test)
BOOST_AUTO_TEST_CASE(Double2Fix)
{
    double i = 0.5;
    double j = 1.0;
    BOOST_CHECK_EQUAL(Fix16::Double2Fix(i) , (int)(i * 65536));
    BOOST_CHECK_EQUAL(Fix16::Double2Fix(j) , (int)(j * 65536));
}
BOOST_AUTO_TEST_SUITE_END()

