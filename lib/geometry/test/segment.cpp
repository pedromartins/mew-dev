// Geometry Library test file
//
// Copyright Barend Gehrels, Geodan Holding B.V. Amsterdam, the Netherlands.
// Copyright Bruno Lalande 2008
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/test/included/test_exec_monitor.hpp>

#include <geometry/geometries/segment.hpp>
#include <geometry/geometries/point.hpp>

#include <geometry/concepts/adapted/c_array.hpp>
#include "common.hpp"


using namespace geometry;


template <typename P>
void test_all()
{
	P p1;
	P p2;
	segment<P> s(p1, p2);
	BOOST_CHECK_EQUAL(&s.first, &p1);
	BOOST_CHECK_EQUAL(&s.second, &p2);
}


int test_main(int, char* [])
{
	test_all<int[3]>();
	test_all<float[3]>();
	test_all<double[3]>();
	test_all<test_point>();
	test_all<point<int, 3> >();
	test_all<point<float, 3> >();
	test_all<point<double, 3> >();

	return 0;
}
