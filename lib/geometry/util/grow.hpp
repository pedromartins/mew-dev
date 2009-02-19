// Geometry Library
//
// Copyright Barend Gehrels, Geodan Holding B.V. Amsterdam, the Netherlands.
// Copyright Bruno Lalande 2008
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef _GEOMETRY_GROW_HPP
#define _GEOMETRY_GROW_HPP

// Grow functions for boxes

#include <boost/concept/requires.hpp>

#include <geometry/concepts/point_concept.hpp>
#include <geometry/arithmetic/arithmetic.hpp>
#include <geometry/geometries/box.hpp>

namespace geometry
{
	namespace impl
	{
		namespace grow
		{

			template <typename PS, typename PD, int I, int N>
			struct check_minmax
			{
				static void check(const PS& source, PD& min_corner, PD& max_corner)
				{
					typedef typename support::coordinate<PS>::type T;
					const T& coordinate = get<I>(source);

					if (coordinate < get<I>(min_corner))
					{
						get<I>(min_corner) = coordinate;
					}
					if (coordinate > get<I>(max_corner))
					{
						get<I>(max_corner) = coordinate;
					}

					check_minmax<PS, PD, I+1, N>::check(source, min_corner, max_corner);
				}
			};

			template <typename PS, typename PD, int N>
			struct check_minmax<PS, PD, N, N>
			{
				static void check(const PS& , PD& , PD& )
				{}
			};

			// Changes a box b such that it also contains point p
			template<typename B, typename P>
			inline void grow_p(B& b, const P& p)
			{
				check_minmax<P, typename B::point_type, 0,
						support::dimension<P>::value>::check(p, b.min_corner(), b.max_corner());
			}

			// Changes a box such that box is also contained by the box
			template<typename B1, typename B2>
			inline void grow_b(B1& b, const B2& other)
			{
				grow_p(b, other.min_corner());
				grow_p(b, other.max_corner());
			}

			// Extends a box with the same amount in all directions
			template<typename B, typename T>
			inline void grow_t(B& b, const T& value)
			{
				typedef typename support::coordinate<typename B::point_type>::type ctype;
				add_value(b.min_corner(), static_cast<ctype>(-value));
				add_value(b.max_corner(), static_cast<ctype>(+value));
			}

		} // namespace grow
	} // namespace impl

	// Changes an box such that point p is also contained by the box
	template<typename P>
	inline
	BOOST_CONCEPT_REQUIRES(((Point<P>)),
	(void)) grow(box<P>& b, const P& p)
	{
		impl::grow::grow_p(b, p);
	}

	// Changes an box such that box is also contained by the box
	template<typename P>
	inline
	BOOST_CONCEPT_REQUIRES(((Point<P>)),
	(void)) grow(box<P>& b, const box<P>& other)
	{
		impl::grow::grow_b(b, other);
	}

	// Extends an box with the same amout in all directions
	template<typename P, typename T>
	inline
	BOOST_CONCEPT_REQUIRES(((Point<P>)),
	(void)) grow(box<P>& b, const T& value)
	{
		impl::grow::grow_t(b, value);
	}

};

#endif // _GEOMETRY_GROW_HPP
