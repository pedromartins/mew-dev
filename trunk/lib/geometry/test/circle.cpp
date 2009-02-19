// Geometry Library test file
//
// Copyright Barend Gehrels, Geodan Holding B.V. Amsterdam, the Netherlands.
// Copyright Bruno Lalande 2008
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/test/included/test_exec_monitor.hpp>
#include <geometry/geometries/point.hpp>
#include <geometry/geometries/circle.hpp>
#include <geometry/concepts/adapted/c_array.hpp>
#include "common.hpp"

using namespace geometry;


template <typename C, typename RT, typename CT>
void check_circle(C& to_check,
                  RT radius, CT center_x, CT center_y, CT center_z)
{
	BOOST_CHECK_EQUAL(to_check.radius(), radius);
	BOOST_CHECK_EQUAL(get<0>(to_check.center()), center_x);
	BOOST_CHECK_EQUAL(get<1>(to_check.center()), center_y);
	BOOST_CHECK_EQUAL(get<2>(to_check.center()), center_z);
}


template <typename P, typename T>
void test_construction()
{
	typedef typename support::coordinate<P>::type ctype;

	circle<P, T> c1;
	check_circle(c1, 0, 0,0,0);

	P center;
	init_point(center, 1, 2, 3);
	circle<P, T> c2(center, 4);
	check_circle(c2, 4, 1,2,3);
}

template <typename P, typename T>
void test_assignment()
{
	P center;
	init_point(center, 0, 0, 0);
	circle<P, T> c(center, 0);

	get<0>(c.center()) = 5;
	get<1>(c.center()) = 50;
	get<2>(c.center()) = 500;
	c.radius(5000);
	check_circle(c, 5000, 5,50,500);
}


template <typename P, typename T>
void test_all()
{
	test_construction<P, T>();
	test_assignment<P, T>();
}


template <typename P>
void test_all()
{
	test_all<P, int>();
	test_all<P, float>();
	test_all<P, double>();
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
