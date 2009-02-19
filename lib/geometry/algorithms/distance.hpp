// Geometry Library
//
// Copyright Barend Gehrels, Geodan Holding B.V. Amsterdam, the Netherlands.
// Copyright Bruno Lalande 2008
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef _GEOMETRY_DISTANCE_HPP
#define _GEOMETRY_DISTANCE_HPP

#include <cmath>
#include <iterator>

#include <geometry/geometries/segment.hpp>

#include <geometry/strategies/strategy_traits.hpp>

#include <geometry/util/promotion_traits.hpp>


/*!
\defgroup distance distance: distance calculation algorithms
The distance algorithm returns the distance between two geometries. The distance is always returned
as a double type, regardless of the input type, because the distance between integer coordinates is
a square root and might be a double.
\note
All primary distance functions return a std::pair<double, bool> with (distance, squared)
if squared=true, it is the squared distance, otherwise it is the distance.
This is for efficiency, often distance is used for comparisons only and then squared is OK.
However, some algorithms such as great circle do NOT use sqrt in their formula and then
it is not necessary to first calculate the sqr and lateron take the sqrt
*/

namespace geometry
{
	/*!
		\brief Utility selecting the most appropriate coordinate type.
		\ingroup utility
		\note Still to be moved to another file
	 */
	template <typename PC1, typename PC2>
	struct select_coordinate_type
	{
		typedef typename select_type_traits<
			typename support::coordinate<PC1>::type,
			typename support::coordinate<PC2>::type
		>::type type;
	};


	namespace impl
	{
		namespace distance
		{
			template <typename P1, typename P2, typename S>
			inline
			BOOST_CONCEPT_REQUIRES(((ConstPoint<P1>)) ((ConstPoint<P2>)),
			(distance_result))
			point_to_point(const P1& p1, const P2& p2, const S& strategy)
			{
				return strategy(p1, p2);
			}

			template<typename P, typename IT, typename S>
			inline
			BOOST_CONCEPT_REQUIRES(((ConstPoint<P>)) ((ConstPoint<typename std::iterator_traits<IT>::value_type>)),
			(distance_result))
			point_to_iterator_pair(const P& p, IT begin, IT end, const S& strategy)
			{
				typedef typename select_coordinate_type<P, typename std::iterator_traits<IT>::value_type>::type T;
				if (begin == end)
				{
					return distance_result(0, false);
				}

				// line of one point: return point square_distance
				IT it = begin;
				IT prev = it++;
				if (it == end)
				{
					typename S::distance_strategy_type pp;
					return pp(p, *begin);
				}

				typedef segment<const typename std::iterator_traits<IT>::value_type> CS;

				// start with first segment distance
				typename strategy_traits<P>::point_segment_distance f2;
				distance_result d = f2(p, CS(*prev, *it));

				// check if other segments are closer
				prev = it++;
				while(it != end)
				{
					distance_result ds = f2(p, CS(*prev, *it));
					if (ds.first <= std::numeric_limits<double>::epsilon())
					{
						return distance_result(0, false);
					}
					else if (ds.first < d.first)
					{
						d = ds;
					}
					prev = it++;
				}
				return d;
			}

		} // namespace distance

	} // namespace impl



	/*!
		\brief Calculate distance between two points
		\ingroup distance
		\details This version of distance calculates the distance between two points, using the specified strategy
		\param p1 first point
		\param p2 second point
		\param strategy strategy to calculate distance between two points
		\return the distance
		\par Example:
		Example showing distance calculation of two lat long points, using the accurate Vincenty approximation
		\dontinclude doxygen_examples.cpp
		\skip example_distance_point_point_strategy
		\line {
		\until }
	 */
	template <typename P1, typename P2, typename S>
	inline double distance(const P1& p1, const P2& p2, const S& strategy)
	{
		distance_result result = impl::distance::point_to_point(p1, p2, strategy);
		return result.value();
	}

	/*!
		\brief Calculate distance between two points
		\ingroup distance
		\details This version of distance calculates the distance between two points, using the default distance-calculation-strategy
		\param p1 first point
		\param p2 second point
		\return the distance
		\note The two point may be of different types, if there is a strategy_traits specialization for this type combination
		\par Example:
		Example showing distance calculation of two points, in xy and in latlong coordinates
		\dontinclude doxygen_examples.cpp
		\skip example_distance_point_point
		\line {
		\until }
	 */
	template <typename P1, typename P2>
	inline double distance(const P1& p1, const P2& p2)
	{
		return distance(p1, p2, typename strategy_traits<P1, P2>::point_distance());
	}


	/*!
		\brief Calculate distance between a point and a linestring (iterator pair)
		\ingroup distance
		\details This version of distance calculates the distance between a point and a line-string, using the specified strategy
		\param p point
		\param begin start of the linestring
		\param end end of the linestring
		\param strategy strategy to calculate distance of point to segment
		\return the distance
		\note The point might be of another type the points in the iterator pair (if the specified strategy allows this)
		\note The strategy might implement an enclosed point-point distance strategy
	 */
	template<typename P, typename IT, typename S>
	inline double distance(const P& p, IT begin, IT end, const S& strategy)
	{
		distance_result result = impl::distance::point_to_iterator_pair(p, begin, end, strategy);
		return result.value();
	}

	/*!
		\brief Calculate distance between a point and a linestring (iterator pair)
		\ingroup distance
		\details This version of distance calculates the distance between a point and a line-string, using the default strategy
		\param p point
		\param begin start of the linestring
		\param end end of the linestring
		\return the distance
		\note The point might be of another type the points in the iterator pair (if there is a strategy_traits
		specialization for this type combination)
	 */
	template<typename P, typename IT>
	inline double distance(const P& p, IT begin, IT end)
	{
		return distance(p, begin, end,
			typename strategy_traits<P, typename std::iterator_traits<IT>::value_type>::point_segment_distance());
	}


} // namespace geometry


#endif // _GEOMETRY_DISTANCE_HPP
