// Geometry Library test file
//
// Copyright Barend Gehrels, Geodan Holding B.V. Amsterdam, the Netherlands.
// Copyright Bruno Lalande 2008
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <sstream>
#include <boost/test/included/test_exec_monitor.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <geometry/io/wkt/streamwkt.hpp>
#include <geometry/concepts/adapted/c_array.hpp>
#include "common.hpp"


using namespace geometry;


namespace geometry {

template <>
struct wkt_traits<test_point>
{
	typedef impl::wkt::stream_point<test_point> stream_type;
};

} // namespace geometry

template <typename CH, typename TR>
inline std::basic_ostream<CH,TR>& operator<<(std::basic_ostream<CH,TR> &os, const test_point &p)
{
	os << geometry::as_wkt<test_point>(p);
	return os;
}


template <typename P>
void test_point_wkt()
{
	P p;
	init_point(p, 1, 23, 456);
	std::ostringstream oss;
	oss << p;
	BOOST_CHECK_EQUAL(oss.str(), "POINT(1 23 456)");

	if (!boost::is_integral<typename support::coordinate<P>::type>::type::value)
	{
		init_point(p, 0.1f, 2.34f, 5.6789f);
		std::ostringstream oss;
		oss << p;
		BOOST_CHECK_EQUAL(oss.str(), "POINT(0.1 2.34 5.6789)");
	}
}

template <typename P>
void test_linestring()
{
	linestring<P> ls;
	P p;

	init_point(p, 1, 2, 3);
	ls.push_back(p);
	init_point(p, 40, 50, 60);
	ls.push_back(p);
	init_point(p, 700, 800, 900);
	ls.push_back(p);

	std::ostringstream oss;
	oss << ls;
	BOOST_CHECK_EQUAL(oss.str(), "LINESTRING(1 2 3,40 50 60,700 800 900)");
}

template <typename P>
void test_polygon_wkt()
{
	polygon<P> p;
	P pt;

	init_point(pt, 100, 200, 300);
	p.outer().push_back(pt);
	init_point(pt, 400, 500, 600);
	p.outer().push_back(pt);
	init_point(pt, 700, 800, 900);
	p.outer().push_back(pt);

	p.inners().resize(2);
	init_point(pt, 10, 20, 30);
	p.inners()[0].push_back(pt);
	init_point(pt, 40, 50, 60);
	p.inners()[0].push_back(pt);
	init_point(pt, 70, 80, 90);
	p.inners()[0].push_back(pt);
	init_point(pt, 1, 2, 3);
	p.inners()[1].push_back(pt);
	init_point(pt, 4, 5, 6);
	p.inners()[1].push_back(pt);
	init_point(pt, 7, 8, 9);
	p.inners()[1].push_back(pt);

	std::ostringstream oss;
	oss << p;
	BOOST_CHECK_EQUAL(oss.str(), "POLYGON((100 200 300,400 500 600,700 800 900),(10 20 30,40 50 60,70 80 90),(1 2 3,4 5 6,7 8 9))");
}


template <typename P>
void test_all()
{
	test_point_wkt<P>();
	test_linestring<P>();
	test_polygon_wkt<P>();
}


int test_main(int, char* [])
{
	test_all<test_point>();
	test_all<point<int, 3> >();
	test_all<point<float, 3> >();
	test_all<point<double, 3> >();

	return 0;
}
