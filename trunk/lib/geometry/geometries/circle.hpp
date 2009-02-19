// Geometry Library
//
// Copyright Barend Gehrels, Geodan Holding B.V. Amsterdam, the Netherlands.
// Copyright Bruno Lalande 2008
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef _GEOMETRY_CIRCLE_HPP
#define _GEOMETRY_CIRCLE_HPP

#include <geometry/concepts/point_concept.hpp>

#include <geometry/geometries/geometry_traits.hpp>

#include <geometry/util/assign.hpp>
#include <geometry/util/copy.hpp>

namespace geometry
{
	/*!
		\brief Class circle: defines point with radius
		\ingroup Geometry
		\details Although this class is currently called "circle" it might have more than 2 dimenions.
		It is possible to create a three-dimensional circle, which is obviously a sphere.
		\note Circle is currently used for selections, for example polygon_in_circle. Currently not all
		algorithms are implemented for circles.
		\par Template parameters:
		- \a P point type of the circle center
		- \a T number type of the radius
	 */
	template <typename P, typename T>
	class circle : public geometry_traits<P>
	{
		BOOST_CONCEPT_ASSERT((Point<P>));

		public :
			typedef T radius_type;
			typedef typename support::coordinate<P>::type coordinate_type;

			circle()
				: m_radius(0)
			{
				assign_value(m_center, coordinate_type(0));
			}

			circle(const P& center, const T& radius)
				: m_radius(radius)
			{
				copy_coordinates(center, m_center);
			}

			inline const P& center() const { return m_center; }
			inline const T radius() const { return m_radius; }

			inline void radius(const T& r) { m_radius = r; }
			inline P& center() { return m_center; }

		private :
			P m_center;
			T m_radius;
	};

}

#endif // _GEOMETRY_CIRCLE_HPP
