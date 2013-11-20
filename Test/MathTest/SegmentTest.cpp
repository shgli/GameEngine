#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "Math/Algorithm.h"
#include "Math/MathException.h"
#include "Common/Common.h"
#include "Math/Segment.h"

BOOST_AUTO_TEST_SUITE(SegmentTest)
    BOOST_AUTO_TEST_CASE(ComputePointTest)
    {
	Segment seg(Point(1,3,5),Point(1,4,8));
	Point ptStart = seg.ComputePoint(0.0);
	Point ptEnd = seg.ComputePoint(1.0);
	Point ptMid = seg.ComputePoint(0.5);

	BOOST_CHECK_EQUAL(ptStart,Point(1,3,5));
	BOOST_CHECK_EQUAL(ptEnd,Point(1,4,8));
	BOOST_CHECK_EQUAL(ptMid,Point(1,3.5,6.5));
    }
    
    BOOST_AUTO_TEST_CASE(SegmentAntarafacialTest)
    {
	Segment seg1(Point(0,0,-1),Vector(1,-1,0));
	Segment seg2(Point(1,1,1),Vector(1,1,0));
	BOOST_CHECK_THROW(seg1.Intersect(seg2),SegmentAntarafacial);
    }

    BOOST_AUTO_TEST_CASE(SegmentParallelTest)
    {
	Segment seg1(Point(0,0,0),Vector(1,1,1));
	Segment seg2(Point(1,2,3),Vector(2,2,2));
	BOOST_CHECK_THROW(seg1.Intersect(seg2),SegmentParallel);
    }

    BOOST_AUTO_TEST_CASE(SegmentIntersectEveryWhereTest)
    {
    	Segment seg1(Point(0,0,0),Vector(1,1,1));
	Segment seg2(Point(-1,-1,-1),Vector(2,2,2));
	BOOST_CHECK_THROW(seg1.Intersect(seg2),IntersectEveryWhere);
    }

    BOOST_AUTO_TEST_CASE(NoIntersectTest)
    {
    	Segment seg1(Point(0,1,-2),Vector(1,2,-1));
	Segment seg2(Point(1,4,-2),Vector(4,7,-5));
	BOOST_CHECK_THROW(seg1.Intersect(seg2),NoIntersect);
      
    }

    BOOST_AUTO_TEST_CASE(IntersectTest)
    {
    	Segment seg1(Point(4.5,10,-6.5),Vector(1,2,-1));
	Segment seg2(Point(1,4,-2),Vector(4,7,-5));
	BOOST_CHECK_EQUAL(seg1.Intersect(seg2),Point(5,11,-7));
      
    }

BOOST_AUTO_TEST_SUITE_END()

