// Geometry Library
//
// Copyright Barend Gehrels, Geodan Holding B.V. Amsterdam, the Netherlands.
// Copyright Bruno Lalande 2008
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef _GEOMETRY_LENGTH_HPP
#define _GEOMETRY_LENGTH_HPP

#include <iterator>

#include <geometry/concepts/point_concept.hpp>
#include <geometry/strategies/strategy_traits.hpp>

/*!
\defgroup length length: length calculation algorithms
The length algorithm is implemented for the linestring and the multi_linestring geometry and results
in the length of the linestring. If the points of a linestring have coordinates expressed in kilometers,
the length of the line is expressed in kilometers as well.
*/

namespace geometry
{
	namespace impl
	{
		namespace length
		{

			/*!
				\brief Internal, calculates length of a linestring using iterator pairs and specified strategy
				\note for_each is not used here, then it will stop it working for std::vector<P> because of ::point_type
			*/
			template<typename IT, typename S>
			inline double length_iterator_pair(IT const& begin, IT const& end, S const& strategy)
			{
				double sum = 0.0;
				IT it = begin;
				if (it != end)
				{
					IT previous = it++;
					while(it != end)
					{
						sum += geometry::distance(*previous, *it, strategy);
						previous = it++;
					}
				}
				return sum;
			}
		}
	}


	/*!
		\brief Calculate length of a series of points, specified by an iterator pair
		\ingroup length
		\details The function length returns the length of a point container, using the default distance-calculation-strategy
		\param begin iterator positioned at first point
		\param end iterator positioned after last point
		\return the length
		\par Example:
		Example showing length calculation using iterators
		\dontinclude doxygen_examples.cpp
		\skip example_length_linestring_iterators1
		\line {
		\until }
		Example showing length calculation on a vector
		\dontinclude doxygen_examples.cpp
		\skip example_length_linestring_iterators2
		\line {
		\until }
	 */
	template<typename IT>
	inline
	BOOST_CONCEPT_REQUIRES(
		((ConstPoint<typename std::iterator_traits<IT>::value_type>))
		, (double)
		)
	length(IT begin, IT end)
	{
		return impl::length::length_iterator_pair(begin, end,
			typename strategy_traits<typename std::iterator_traits<IT>::value_type>::point_distance());
	}

	/*!
		\brief Calculate length of a series of points, specified by an iterator pair and a strategy
		\ingroup length
		\details The function length returns the length of a point container between specified iterators, using specified strategy
		\param begin iterator positioned at first point
		\param end iterator positioned after last point
		\param strategy strategy to be used for distance calculations.
		\return the length
		\par Example:
		Example showing length calculation using iterators and the Vincenty strategy
		\dontinclude doxygen_examples.cpp
		\skip example_length_linestring_iterators3
		\line {
		\until }
	 */
	template<typename IT, typename S>
	inline
	BOOST_CONCEPT_REQUIRES(
		((ConstPoint<typename std::iterator_traits<IT>::value_type>))
		, (double)
		)
	length(IT begin, IT end, S const& strategy)
	{
		return impl::length::length_iterator_pair(begin, end, strategy);
	}


} // namespace geometry


#endif // _GEOMETRY_LENGTH_HPP
