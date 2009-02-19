// Geometry Library test file
//
// Copyright Barend Gehrels, Geodan Holding B.V. Amsterdam, the Netherlands.
// Copyright Bruno Lalande 2008
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <vector>
#include <boost/array.hpp>
#include <boost/test/included/test_exec_monitor.hpp>

#include <geometry/concepts/coordinate.hpp>
#include <geometry/concepts/adapted/c_array.hpp>

#include <geometry/geometries/point.hpp>

#include <geometry/algorithms/loop.hpp>

#include "common.hpp"

using namespace geometry;


struct test_operation_1
{
	template <typename Segment, typename State>
	bool operator()(Segment&, State& state) const
	{
		state +=1;
		return true;
	}
};

struct test_operation_2
{
	template <typename Segment, typename State>
	bool operator()(Segment& segment, State& state) const
	{
		state += get<0>(segment.first)
		       + get<1>(segment.first)
		       + get<2>(segment.first)
		       + get<0>(segment.second)
		       + get<1>(segment.second)
		       + get<2>(segment.second);

		static int count = 0;
		if (++count == 3)
		{
			count = 0;
			return false;
		}

		return true;
	}
};


template <typename P>
void test_all()
{
	boost::array<P, 5> a;
	init_point(a[0], 1, 2, 3);
	init_point(a[1], 4, 5, 6);
	init_point(a[2], 7, 8, 9);
	init_point(a[3], 10, 11, 12);
	init_point(a[4], 13, 14, 15);
	typename support::coordinate<P>::type state;

	state = 0;
	BOOST_CHECK_EQUAL(loop(a, test_operation_1(), state), true);
	BOOST_CHECK_EQUAL(state, 4);

	state = 0;
	BOOST_CHECK_EQUAL(loop(a, test_operation_2(), state), false);
	BOOST_CHECK_EQUAL(state, 1+2+3+4+5+6 + 4+5+6+7+8+9 + 7+8+9+10+11+12);
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
