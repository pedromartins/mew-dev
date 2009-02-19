// Geometry Library
//
// Copyright Barend Gehrels, Geodan Holding B.V. Amsterdam, the Netherlands.
// Copyright Bruno Lalande 2008
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef _GEOMETRY_ENVELOPE_HPP
#define _GEOMETRY_ENVELOPE_HPP


#include <iterator>

#include <geometry/geometries/circle.hpp>
#include <geometry/geometries/box.hpp>
#include <geometry/util/grow.hpp>
#include <geometry/util/copy.hpp>

#include <geometry/geometries/polygon.hpp>


#include <geometry/strategies/strategy_traits.hpp>


/*!
\defgroup envelope envelope: envelope calculation algorithms
The envelope algorithm calculates the bounding box, or envelope, of a geometry.
It is defined for all geometries.
- The envelope of a point is a box with zero area, the maximum and the minimum point of the box are
set to the point itself.
- The envelope of a linestring is the smalles box that contains all points of the specified linestring.
If the linestring is empty, the envelope is the inverse infinite box, that is, the minimum point is very
large (max infinite) and the maximum point is very small (min infinite).
- The envelope for polygon, and for all multi geometries, are defined as the envelope of the linestring
described above.

According to OGC: Envelope (): Geometry - The minimum bounding box for this Geometry,
returned as a Geometry. The polygon is defined by the corner points of the bounding
box [(MINX, MINY), (MAXX, MINY), (MAXX, MAXY), (MINX, MAXY), (MINX, MINY)].

Implemented in the Geometry library: The minimum bounding box, always as a box, having min <= max

Todo:
- concept checks
- add strategy as an option in most algorithms
*/

namespace geometry
{

	namespace impl
	{
		namespace envelope
		{
			// Calculate envelope of a point. It is coordinate-neutral, should work
			// for both point_xy and point_ll
			template<typename B, typename P>
			inline void envelope_point(const P& p, B& mbr)
			{
				copy_coordinates(p, mbr.min_corner());
				copy_coordinates(p, mbr.max_corner());
			}

			// Calculate envelope of a circle, currently only for point_xy
			template<typename B, typename C>
			inline void envelope_circle(const C& c, B& mbr)
			{
				get<0>(mbr.min_corner()) = get<0>(c.center()) - c.radius();
				get<1>(mbr.min_corner()) = get<1>(c.center()) - c.radius();
				get<0>(mbr.max_corner()) = get<0>(c.center()) + c.radius();
				get<1>(mbr.max_corner()) = get<1>(c.center()) + c.radius();
			}

			// Generic vector/container versions, working for linear_ring/line
			template<typename IT, typename S>
			inline void envelope_container_state(IT begin, IT end, const S& strategy, typename S::state_type& state)
			{
				for (IT it = begin; it != end; it++)
				{
					strategy(*it, state);
				}
			}
			template<typename B, typename IT, typename S>
			inline void envelope_container(IT begin, IT end, const S& strategy, B& mbr)
			{
				typename S::state_type state;
				for (IT it = begin; it != end; it++)
				{
					strategy(*it, state);
				}
				state.envelope(mbr);
			}

			// For polygon inspecting outer linear_ring is sufficient
			template<typename B, typename Y, typename S>
			inline void envelope_polygon(const Y& poly, B& mbr, const S& strategy)
			{
				typename S::state_type state;
				envelope_container_state(poly.outer().begin(), poly.outer().end(), strategy, state);
				state.envelope(mbr);
			}

		} // namespace envelope
	} // namespace impl



	/*!
		\brief Calculate envelope of a point
		\ingroup envelope
		\details The envelope of a point is a box containing just the point itself. It is provided
		for consistence, on itself it is not useful.
		\param p the point
		\param b the box receiving the envelope
		\note It does not RETURN the envelope. The type of the envelope-points might be different
		from the type of the specified point.
	 */

	template<typename PB, typename P>
	inline void envelope(const P& p, box<PB>& b)
	{
		impl::envelope::envelope_point(p, b);
	}


	/*!
		\brief Calculate envelope of a circle
		\ingroup envelope
		\details The envelope of a circle is a box containing enclosing the circle
		\param c the circle
		\param b the box receiving the envelope
		\note Currently only implemented for point_xy
	 */
	template<typename PB, typename C, typename T>
	inline void envelope(const circle<C, T>& c, box<PB>& b)
	{
		impl::envelope::envelope_circle(c, b);
	}

	/*!
		\brief Calculate envelope of an iterator-pair or linestring
		\ingroup envelope
		\details The envelope of an iterator-pair just contains all points,
		using the default strategy
		\param begin begin-iterator
		\param end end-iterator
		\param b the box receiving the envelope
		\par Example:
		Example showing envelope calculation
		\dontinclude doxygen_examples.cpp
		\skip example_envelope_linestring
		\line {
		\until }
	 */
	template<typename PB, typename IT>
	inline void envelope(IT begin, IT end, box<PB>& b)
	{
		impl::envelope::envelope_container(begin, end,
					typename strategy_traits<PB, typename std::iterator_traits<IT>::value_type>::envelope(),
					b);
	}


	/*!
		\brief Calculate envelope of a linear ring
		\ingroup envelope
		\details The envelope of a linear ring just contains all points of the ring,
		using the default strategy
		\param ring the linear_ring
		\param b the box receiving the envelope
	 */
	template<typename PB, typename P, template<typename,typename> class V, template<typename> class A>
	inline void envelope(const linear_ring<P, V, A>& ring, box<PB>& b)
	{
		impl::envelope::envelope_container(ring.begin(), ring.end()
				, typename strategy_traits<PB, P>::envelope(), b);
	}

	/*!
		\brief Calculate envelope of a polygon
		\ingroup envelope
		\details The envelope of a linestring just contains all points of the polygon,
		using the default strategy
		\param poly the polygon
		\param b the box receiving the envelope
		\par Example:
		Example showing envelope calculation, using point_ll latlong points
		\dontinclude doxygen_examples.cpp
		\skip example_envelope_polygon
		\line {
		\until }
	 */
	template<typename PB, typename PP,
			template<typename,typename> class VP,
			template<typename,typename> class VR,
			template<typename> class AP,
			template<typename> class AR>
	inline void envelope(const polygon<PP, VP, VR, AP, AR>& poly, box<PB>& b)
	{
		impl::envelope::envelope_polygon(poly, b, typename strategy_traits<PB, PP>::envelope());
	}

	template<typename PB, typename PP,
			template<typename,typename> class VP,
			template<typename,typename> class VR,
			template<typename> class AP,
			template<typename> class AR,
			typename S>
	inline void envelope(const polygon<PP, VP, VR, AP, AR>& poly, box<PB>& b, const S& strategy)
	{
		impl::envelope::envelope_polygon(poly, b, strategy);
	}


} // namespace geometry


#endif // _GEOMETRY_ENVELOPE_HPP
