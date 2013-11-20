#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "Math/Algorithm.h"
#include "Math/MathException.h"
#include "Common/Common.h"
#include "Math/Plane.h"

BOOST_AUTO_TEST_SUITE(PlaneTest)
    BOOST_AUTO_TEST_CASE(TestTest)
    {
        Plane p(Point(0,0,0),Vector(1,1,1));
	BOOST_CHECK(p.Test(Point(50,50,50)) > 0);
        BOOST_CHECK_EQUAL(p.Test(Point(0,-1,1)),0.0);	
	BOOST_CHECK(p.Test(Point(-1,-1,-1)) < 0);
    }

    BOOST_AUTO_TEST_CASE(ParallelIntersectTest)
    {
	Segment seg(Point(3,-4,0),Vector(-2,-7,3));
	Plane pl(4,-2,-2,3);
	BOOST_CHECK_THROW(Intersect(seg,pl),PlaneParallel);
    }

    BOOST_AUTO_TEST_CASE(InPlaneIntersectTest)
    {
	Segment seg(Point(0,-7.0/5.0,2.0/5),Point(7.0/9,0,5.0/9));
	Plane pl(4,-3,7,-7);
	BOOST_CHECK_THROW(Intersect(seg,pl),IntersectEveryWhere);
    }

    BOOST_AUTO_TEST_CASE(SegPlaneIntersectTest)
    {
	Segment seg(Point(0,9,-4),Vector(1,-2,9));
	Plane pl(3,-4,7,-10);
	Point pt = Intersect(pl,seg);
	BOOST_CHECK_EQUAL(pt,Point(1,7,5));
    }
BOOST_AUTO_TEST_SUITE_END()

