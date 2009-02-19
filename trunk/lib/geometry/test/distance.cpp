// Geometry Library test file
//
// Copyright Barend Gehrels, Geodan Holding B.V. Amsterdam, the Netherlands.
// Copyright Bruno Lalande 2008
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/test/included/test_exec_monitor.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <boost/array.hpp>

#include <geometry/algorithms/distance.hpp>
#include <geometry/concepts/adapted/c_array.hpp>
#include <geometry/geometries/linestring.hpp>

#include "common.hpp"


namespace geometry {

template <typename T, int N>
struct strategy_traits<T[N], T[N]>
{
	typedef strategy::distance::pythagoras<T[N], T[N]> point_distance;
	typedef strategy::distance::xy_point_segment<T[N], T[N], point_distance> point_segment_distance;
};

template <>
struct strategy_traits<test_point, test_point>
{
	typedef strategy::distance::pythagoras<test_point, test_point> point_distance;
	typedef strategy::distance::xy_point_segment<test_point, test_point, point_distance> point_segment_distance;
};

} // namespace geometry


template <typename P>
void test_distance_point()
{
	typedef typename geometry::support::coordinate<P>::type T;

 	P p1;
	geometry::get<0>(p1) = 1;
	geometry::get<1>(p1) = 1;

	P p2;
	geometry::get<0>(p2) = 2;
	geometry::get<1>(p2) = 2;

	double d = geometry::distance(p1, p2);
	BOOST_CHECK_CLOSE(d, 1.4142135, 0.001);
}

template <typename P>
void test_distance_linestring()
{
	typedef typename geometry::support::coordinate<P>::type T;

	boost::array<P, 2> points;
	geometry::get<0>(points[0]) = 1;
	geometry::get<1>(points[0]) = 1;
	geometry::get<0>(points[1]) = 3;
	geometry::get<1>(points[1]) = 3;

	P p;
	geometry::get<0>(p) = 2;
	geometry::get<1>(p) = 1;

	double d = geometry::distance(p, points.begin(), points.end());
	BOOST_CHECK_CLOSE(d, 0.70710678, 0.001);
}


template <typename P>
void test_all()
{
	test_distance_point<P>();
	test_distance_linestring<P>();
}


int test_main(int, char* [])
{
	//test_all<int[2]>();
	test_all<float[2]>();
	test_all<double[2]>();
	test_all<test_point>();
	//test_all<geometry::point_xy<int> >();
	test_all<geometry::point_xy<float> >();
	test_all<geometry::point_xy<double> >();

	return 0;
}


