// Geometry Library test file
//
// Copyright Barend Gehrels, Geodan Holding B.V. Amsterdam, the Netherlands.
// Copyright Bruno Lalande 2008
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/test/included/test_exec_monitor.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include <geometry/algorithms/envelope.hpp>
#include <geometry/geometries/linestring.hpp>

#include "common.hpp"


namespace geometry {
template <>
struct strategy_traits<test_point, test_point>
{
	typedef strategy::envelope::grow_xy<test_point, test_point> envelope;

};
} // namespace geometry


template <typename T, typename B>
void check_result(const B& b, const T& x1, const T& y1, const T& x2, const T& y2)
{
	BOOST_CHECK_CLOSE((double)geometry::get<0>(b.min_corner()), (double)x1, 0.001);
	BOOST_CHECK_CLOSE((double)geometry::get<1>(b.min_corner()), (double)y1, 0.001);

	BOOST_CHECK_CLOSE((double)geometry::get<0>(b.max_corner()), (double)x2, 0.001);
	BOOST_CHECK_CLOSE((double)geometry::get<1>(b.max_corner()), (double)y2, 0.001);
}


template <typename P>
void test_envelope_point()
{
	typedef typename geometry::support::coordinate<P>::type T;

 	P p;
	geometry::get<0>(p) = 1;
	geometry::get<1>(p) = 1;

	geometry::box<P> b;

	geometry::envelope(p, b);
	check_result<T>(b, 1, 1, 1, 1);
}


template <typename P>
void test_envelope_linestring()
{
	typedef typename geometry::support::coordinate<P>::type T;

 	geometry::linestring<P> line;

	P p;
	geometry::get<0>(p) = 1;
	geometry::get<1>(p) = 1;
	line.push_back(p);

	geometry::get<0>(p) = 2;
	geometry::get<1>(p) = 2;
	line.push_back(p);

	geometry::box<P> b;

	// Check envelope detection using linestring
	//geometry::envelope(line.begin(), line.end(), b);
	//check_result<T>(b, 1, 1, 2, 2);


	// Check envelope detection using iterator pair
	geometry::envelope(line.begin(), line.end(), b);
	check_result<T>(b, 1, 1, 2, 2);
}


template <typename P>
void test_envelope_polygon()
{
	typedef typename geometry::support::coordinate<P>::type T;

 	geometry::polygon<P> poly;

	P p;
	geometry::get<0>(p) = 1; geometry::get<1>(p) = 1; poly.outer().push_back(p);
	geometry::get<0>(p) = 1; geometry::get<1>(p) = 3; poly.outer().push_back(p);
	geometry::get<0>(p) = 3; geometry::get<1>(p) = 3; poly.outer().push_back(p);
	geometry::get<0>(p) = 3; geometry::get<1>(p) = 1; poly.outer().push_back(p);
	geometry::get<0>(p) = 1; geometry::get<1>(p) = 1; poly.outer().push_back(p);

	geometry::box<P> b;

	// Check called by polygon, by ring, by iterator pairs
	geometry::envelope(poly, b);
	check_result<T>(b, 1, 1, 3, 3);

	// Check if other things compile
	geometry::envelope(poly.outer(), b);
	check_result<T>(b, 1, 1, 3, 3);

	geometry::envelope(poly.outer().begin(), poly.outer().end(), b);
	check_result<T>(b, 1, 1, 3, 3);
}



template <typename P>
void test_all()
{
	test_envelope_point<P>();
	test_envelope_linestring<P>();
	test_envelope_polygon<P>();
}


int test_main(int, char* [])
{
	//test_all<int[2]>();
	//test_all<float[2]>();
	//test_all<double[2]>();
	test_all<test_point >();
	test_all<geometry::point_xy<int> >();
	test_all<geometry::point_xy<float> >();
	test_all<geometry::point_xy<double> >();

	return 0;
}


