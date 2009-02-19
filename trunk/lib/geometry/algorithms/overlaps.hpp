// Geometry Library
//
// Copyright Barend Gehrels, Geodan Holding B.V. Amsterdam, the Netherlands.
// Copyright Bruno Lalande 2008
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef _GEOMETRY_OVERLAPS_HPP
#define _GEOMETRY_OVERLAPS_HPP

#include <geometry/geometries/box.hpp>

namespace geometry
{
	template <typename P>
	bool overlaps(const box<P>& r1, const box<P>& r2)
	{
		return !(
				get<0>(r1.max_corner()) <= get<0>(r2.min_corner()) ||
				get<0>(r1.min_corner()) >= get<0>(r2.max_corner()) ||
				get<1>(r1.max_corner()) <= get<1>(r2.min_corner()) ||
				get<1>(r1.min_corner()) >= get<1>(r2.max_corner())
				);

	}


} // namespace geometry


#endif // _GEOMETRY_OVERLAPS_HPP
