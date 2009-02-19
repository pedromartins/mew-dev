// Geometry Library test file
//
// Copyright Barend Gehrels, Geodan Holding B.V. Amsterdam, the Netherlands.
// Copyright Bruno Lalande 2008
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/test/included/test_exec_monitor.hpp>
#include <geometry/util/grow.hpp>
#include <geometry/concepts/adapted/c_array.hpp>

#include <geometry/geometries/point.hpp>

#include "common.hpp"

using namespace geometry;


template <typename P>
box<P> create_box()
{
	P p1;
	P p2;
	init_point(p1, 1, 2, 5);
	init_point(p2, 3, 4, 6);
	return box<P>(p1, p2);
}

template <typename B, typename T>
void check_box(B& to_check,
               T min_x, T min_y, T min_z,
               T max_x, T max_y, T max_z)
{
	BOOST_CHECK_EQUAL(get<0>(to_check.min_corner()), min_x);
	BOOST_CHECK_EQUAL(get<1>(to_check.min_corner()), min_y);
	BOOST_CHECK_EQUAL(get<2>(to_check.min_corner()), min_z);
	BOOST_CHECK_EQUAL(get<0>(to_check.max_corner()), max_x);
	BOOST_CHECK_EQUAL(get<1>(to_check.max_corner()), max_y);
	BOOST_CHECK_EQUAL(get<2>(to_check.max_corner()), max_z);
}

template <typename P, typename T>
void grow_p_and_check(box<P>& to_grow,
                      T grow_x, T grow_y, T grow_z,
                      T result_min_x, T result_min_y, T result_min_z,
                      T result_max_x, T result_max_y, T result_max_z)
{
	P p;
	init_point(p, grow_x, grow_y, grow_z);
	grow(to_grow, p);

	check_box(to_grow,
	          result_min_x, result_min_y, result_min_z,
	          result_max_x, result_max_y, result_max_z
	);
}

template <typename P, typename T>
void grow_b_and_check(box<P>& to_grow,
                      T grow_min_x, T grow_min_y, T grow_min_z,
                      T grow_max_x, T grow_max_y, T grow_max_z,
                      T result_min_x, T result_min_y, T result_min_z,
                      T result_max_x, T result_max_y, T result_max_z)
{
	P p1, p2;
	init_point(p1, grow_min_x, grow_min_y, grow_min_z);
	init_point(p2, grow_max_x, grow_max_y, grow_max_z);
	box<P> grow_box(p1, p2);
	grow(to_grow, grow_box);

	check_box(to_grow,
	          result_min_x, result_min_y, result_min_z,
	          result_max_x, result_max_y, result_max_z);
}

template <typename P, typename T>
void grow_t_and_check(box<P>& to_grow, T factor,
                      T result_min_x, T result_min_y, T result_min_z,
                      T result_max_x, T result_max_y, T result_max_z)
{
	grow(to_grow, factor);

	check_box(to_grow,
	          result_min_x, result_min_y, result_min_z,
	          result_max_x, result_max_y, result_max_z);
}


template <typename P>
void test_grow_p()
{
	box<P> b(create_box<P>());
	grow_p_and_check(b, 4,4,5,   1,2,5,4,4,6);
	grow_p_and_check(b, 4,5,5,   1,2,5,4,5,6);
	grow_p_and_check(b, 10,10,4, 1,2,4,10,10,6);
	grow_p_and_check(b, 9,9,4,   1,2,4,10,10,6);

	grow_p_and_check(b, 0,2,7,   0,2,4,10,10,7);
	grow_p_and_check(b, 0,0,7,   0,0,4,10,10,7);
	grow_p_and_check(b, -1,-1,5, -1,-1,4,10,10,7);
	grow_p_and_check(b, 0,0,5,   -1,-1,4,10,10,7);

	grow_p_and_check(b, 15,-1,0, -1,-1,0,15,10,7);
	grow_p_and_check(b, -1,15,10, -1,-1,0,15,15,10);
}

template <typename P>
void test_grow_b()
{
	box<P> b(create_box<P>());

	grow_b_and_check(b, 0,2,5,4,4,6,     0,2,5,4,4,6);
	grow_b_and_check(b, 0,1,5,4,6,6,     0,1,5,4,6,6);
	grow_b_and_check(b, -1,-1,6,10,10,5, -1,-1,5,10,10,6);
	grow_b_and_check(b, 3,3,6,3,3,5,     -1,-1,5,10,10,6);

	grow_b_and_check(b, 3,15,7,-1,3,4,   -1,-1,4,10,15,7);
	grow_b_and_check(b, -15,3,7,3,20,4,   -15,-1,4,10,20,7);
	grow_b_and_check(b, 3,-20,8,3,20,3,   -15,-20,3,10,20,8);
	grow_b_and_check(b, -20,3,8,20,3,3,   -20,-20,3,20,20,8);
}

template <typename P>
void test_grow_t()
{
	box<P> b(create_box<P>());

	grow_t_and_check(b, 5, -4,-3,0,8,9,11);
	grow_t_and_check(b, -2, -2,-1,2,6,7,9);
	grow_t_and_check(b, -100, 98,99,102,-94,-93,-91);
}


template <typename P>
void test_all()
{
	test_grow_p<P>();
	test_grow_b<P>();
	test_grow_t<P>();
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
