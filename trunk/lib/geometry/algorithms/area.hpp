// Geometry Library
//
// Copyright Barend Gehrels, Geodan Holding B.V. Amsterdam, the Netherlands.
// Copyright Bruno Lalande 2008
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef _GEOMETRY_AREA_HPP
#define _GEOMETRY_AREA_HPP

#include <boost/concept/requires.hpp>

#include <geometry/concepts/point_concept.hpp>

#include <geometry/geometries/polygon.hpp>
#include <geometry/geometries/box.hpp>
#include <geometry/geometries/circle.hpp>
#include <geometry/geometries/segment.hpp>

#include <geometry/strategies/strategy_traits.hpp>

#include <geometry/algorithms/loop.hpp>

#include <geometry/util/math.hpp>

/*!
\defgroup area area: area calculation algorithms
The area of a geometry calculates the surface area of all geometries having a surface:
box, circle, polygon, multi_polygon. The units are the square of the units used for the points
defining the surface. If the polygon is defined in meters, the area is in square meters.
*/
namespace geometry
{
	namespace impl
	{
		namespace area
		{
			// Currently only works for Cartesian points
			template<typename B>
			inline typename B::coordinate_type area_box(const B& b)
			{
				typename B::coordinate_type dx = get<0>(b.max_corner()) - get<0>(b.min_corner());
				typename B::coordinate_type dy = get<1>(b.max_corner()) - get<1>(b.min_corner());
				return dx * dy;
			}

			template<typename C>
			inline double area_circle(const C& c)
			{
				return geometry::math::pi * c.radius() * c.radius();
			}

			// Area of a linear linear_ring, assuming a closed linear_ring
			template<typename R, typename S>
			inline double area_ring(const R& r, const S& strategy)
			{
				// A closed linear_ring has at least four points, if not there is no area
				if (r.size() >= 4)
				{
					typename S::state_type state;
					if (loop(r, strategy, state))
					{
						return state.area();
					}
				}

				return 0;
			}

			// Area of a polygon, assuing a closed clockwise polygon (with holes counter clockwise)
			template<typename Y, typename S>
			inline double area_polygon(const Y& poly, const S& strategy)
			{
				double a = fabs(area_ring(poly.outer(), strategy));
				for (typename Y::inner_container_type::const_iterator i = poly.inners().begin(); i != poly.inners().end(); i++)
				{
					a -= fabs(area_ring(*i, strategy));
				}
				return a;
			}
		} // namespace area
	} // namespace impl


	/*!
		\brief Calculate area of box
		\ingroup area
	 */
	template<typename P>
	inline
	BOOST_CONCEPT_REQUIRES(((ConstPoint<P>)),
	(double)) area(const box<P> & b)
	{
		return impl::area::area_box(b);
	}

	/*!
		\brief Calculate area of circle
		\ingroup area
	 */
	template<typename P, typename T>
	inline
	BOOST_CONCEPT_REQUIRES(((ConstPoint<P>)),
	(double)) area(const circle<P, T> & c)
	{
		return impl::area::area_circle(c);
	}

	/*!
		\brief Calculate area of linear_ring
		\ingroup area
		\details The function area returns the area of a linear_ring, a strategy is specified
		\param ring a closed linear_ring
		\param strategy strategy to be used for area calculations.
		\return the area
	 */
	template<typename P, template<typename,typename> class V, template<typename> class A, typename S>
	inline
	BOOST_CONCEPT_REQUIRES(((ConstPoint<P>)),
	(double)) area(const linear_ring<P, V, A> & ring, const S& strategy)
	{
		return impl::area::area_ring(ring, strategy);
	}

	/*!
		\brief Calculate area of linear_ring
		\ingroup area
		\details The function area returns the area of a linear_ring, using the default strategy
		\param ring a closed linear_ring
		\return the area
	 */
	template<typename P, template<typename,typename> class V, template<typename> class A>
	inline
	BOOST_CONCEPT_REQUIRES(((ConstPoint<P>)),
	(double)) area(const linear_ring<P, V, A> & ring)
	{
		return impl::area::area_ring(ring, typename strategy_traits<P>::area());
	}

	/*!
		\brief Calculate area of polygon
		\ingroup area
		\details The function area returns the area of a polygon, using the specified strategy
		The polygon should be closed and orientated clockwise, holes, if any, must be orientated
		counter clockwise
		\param poly a closed polygon
		\param strategy strategy to be used for area calculations.
		\return the area
	 */
	template<typename P,
			template<typename,typename> class VP,
			template<typename,typename> class VR,
			template<typename> class AP,
			template<typename> class AR, typename S>
	inline
	BOOST_CONCEPT_REQUIRES(((ConstPoint<P>)),
	(double)) area(const polygon<P, VP, VR, AP, AR>& poly, const S& strategy)
	{
		return impl::area::area_polygon(poly, strategy);
	}

	/*!
		\brief Calculate area of polygon
		\ingroup area
		\details The function area returns the area of a polygon, using the default area-calculation strategy. Default strategies are
		provided for point_xy and for point_ll.
		The polygon should be closed and orientated clockwise, holes, if any, must be orientated
		counter clockwise
		\param poly a closed polygon
		\return the area
		\par Example:
		Example showing area calculation of polygons built of xy-points and of latlong-points
		\dontinclude doxygen_examples.cpp
		\skip example_area_polygon()
		\line {
		\until }
	 */
	template<typename P,
			template<typename,typename> class VP,
			template<typename,typename> class VR,
			template<typename> class AP,
			template<typename> class AR>
	inline
	BOOST_CONCEPT_REQUIRES(((ConstPoint<P>)),
	(double)) area(const polygon<P, VP, VR, AP, AR>& poly)
	{
		return impl::area::area_polygon(poly, typename strategy_traits<P>::area());
	}

} // namespace geometry


#endif // _GEOMETRY_AREA_HPP
