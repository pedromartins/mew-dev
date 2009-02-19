// Geometry Library
//
// Copyright Barend Gehrels, Geodan Holding B.V. Amsterdam, the Netherlands.
// Copyright Bruno Lalande 2008
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef _GEOMETRY_SEGMENT_HPP
#define _GEOMETRY_SEGMENT_HPP

#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/concept/assert.hpp>

#include <geometry/concepts/point_concept.hpp>

#include <geometry/geometries/geometry_traits.hpp>

namespace geometry
{

	/*!
		\brief Class segment: small containing two (templatized) point references
		\ingroup Geometry
		\details From Wikipedia: In geometry, a line segment is a part of a line that is bounded
		by two distinct end points, and contains every point on the line between its end points
		\note The structure is like std::pair, and can often be used interchangeable.
		So points are public available. We cannot derive from std::pair<P&, P&> because of reference
		assignments. Points are not const and might be changed by the algorithm
		(used in intersection_linestring)
		\par Template parameters:
		- \a P point type of the segment
	 */
	template<typename P>
	struct segment : public geometry_traits<P>
	{
		private :
			BOOST_CONCEPT_ASSERT((typename boost::mpl::if_<
									  boost::is_const<P>,
									  ConstPoint<P>,
									  Point<P>
								  >
			));

		public :
			P& first;
			P& second;
			inline segment(P& p1, P& p2)
				: first(p1), second(p2)
			{}
	};

} // namespace geometry


#endif //_GEOMETRY_SEGMENT_HPP
