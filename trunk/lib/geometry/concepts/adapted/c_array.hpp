// Geometry Library
//
// Copyright Bruno Lalande 2008
// Copyright Barend Gehrels, Geodan Holding B.V. Amsterdam, the Netherlands.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef _GEOMETRY_C_ARRAY_HPP
#define _GEOMETRY_C_ARRAY_HPP


#include <geometry/concepts/coordinate.hpp>
#include <geometry/concepts/dimension.hpp>
#include <geometry/concepts/access.hpp>


namespace geometry
{
	namespace traits
	{
		template <typename T, int N>
		struct coordinate<T[N]>
		{ typedef T type; };

		template <typename T, int N>
		struct dimension<T[N]>: boost::mpl::int_<N>
		{};

		template <typename T, int N>
		struct access<T[N]>
		{
			template <int I, typename TT>
			static TT& get(TT p[N])
			{ return p[I]; }
		};
	}
}


#endif
