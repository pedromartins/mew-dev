// Geometry Library
//
// Copyright Barend Gehrels, Geodan Holding B.V. Amsterdam, the Netherlands.
// Copyright Bruno Lalande 2008
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef _GEOMETRY_CORRECT_HPP
#define _GEOMETRY_CORRECT_HPP

#include <algorithm>

#include <boost/concept/requires.hpp>

#include <geometry/concepts/point_concept.hpp>
#include <geometry/geometries/box.hpp>
#include <geometry/geometries/polygon.hpp>


namespace geometry
{
	namespace impl
	{
		namespace correct
		{
			// correct an box: make min/max are correct
			template <typename B>
			inline void correct_box(B& b)
			{
				// Currently only for Cartesian coordinates
				// TODO: adapt using strategies
				// TODO: adapt using traits
				typedef typename B::coordinate_type T;
				if (get<0>(b.min_corner()) > get<0>(b.max_corner()))
				{
					T max_value = get<0>(b.min_corner());
					T min_value = get<0>(b.max_corner());
					get<0>(b.min_corner()) = min_value;
					get<0>(b.max_corner()) = max_value;
				}
				if (get<1>(b.min_corner()) > get<1>(b.max_corner()))
				{
					T max_value = get<1>(b.min_corner());
					T min_value = get<1>(b.max_corner());
					get<1>(b.min_corner()) = min_value;
					get<1>(b.max_corner()) = max_value;
				}
			}

			// close a linear_ring, if not closed
			template <typename R>
			inline void ensure_closed_ring(R& r)
			{
				if (r.size() > 2)
				{
					// check if closed, if not, close it
					if (r.front() != r.back())
					{
						r.push_back(r.front());
					}
				}
			}


			// correct a polygon: normalizes all rings, sets outer linear_ring clockwise, sets all
			// inner rings counter clockwise
			template <typename Y>
			inline void correct_polygon(Y& poly)
			{
				typename Y::ring_type& outer = poly.outer();
				ensure_closed_ring(outer);

				typename strategy_traits<typename Y::point_type>::area strategy;

				if (impl::area::area_ring(outer, strategy) < 0)
				{
					std::reverse(outer.begin(), outer.end());
				}

				for (typename Y::inner_container_type::iterator it = poly.inners().begin();
							it != poly.inners().end(); it++)
				{
					ensure_closed_ring(*it);
					if (impl::area::area_ring(*it, strategy) > 0)
					{
						std::reverse(it->begin(), it->end());
					}
				}
			}

		}
	}


	//---------------------------------------------------------------------------------------------
	template <typename P>
	inline
	BOOST_CONCEPT_REQUIRES(
		((ConstPoint<P>))
		, (void)
		)
	correct(box<P>& b)
	{
		impl::correct::correct_box(b);
	}


	template <typename P, template <typename,typename> class V, template<typename> class A>
	inline
	BOOST_CONCEPT_REQUIRES(((Point<P>)),
	(void)) correct(linear_ring<P, V, A>& r)
	{
		impl::correct::ensure_closed_ring(r);
	}


	template <typename P,
			template<typename,typename> class VP,
			template<typename,typename> class VR,
			template<typename> class AP,
			template<typename> class AR>
	inline
	BOOST_CONCEPT_REQUIRES(
		((ConstPoint<P>))
		, (void)
		)
	correct(polygon<P, VP, VR, AP, AR>& poly)
	{
		impl::correct::correct_polygon(poly);
	}


} // namespace geometry


#endif // _GEOMETRY_CORRECT_HPP
