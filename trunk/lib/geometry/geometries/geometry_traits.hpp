// Geometry Library
//
// Copyright Barend Gehrels, Geodan Holding B.V. Amsterdam, the Netherlands.
// Copyright Bruno Lalande 2008
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef _GEOMETRY_GEOMETRY_TRAITS_HPP
#define _GEOMETRY_GEOMETRY_TRAITS_HPP

#include <boost/concept/requires.hpp>


#include <geometry/concepts/point_concept.hpp>


namespace geometry
{

	/*!
	\defgroup Geometry Geometry: geometric objects
	*/






	/*!
		\brief Helper class for derived classes or algorithms to conveniently define member characteristics
		\details Defines the following:
		- point_type
		- coordinate_type
		- coordinate_count (size_t)
		Linestring, polygon, etc can be derived from this class and, hence, define these characteristics
		\par Template parameters:
		- \a P point type
	*/
	template<typename P>
	class geometry_traits
	{
		// TODO Here we only need to ensure that coordinate type and dimension
		//      are accessible. Divide the concepts into more fine-grained ones.
		BOOST_CONCEPT_ASSERT((ConstPoint<P>));

		public :
			typedef P point_type;
			typedef typename support::coordinate<P>::type coordinate_type;
			static const size_t coordinate_count = support::dimension<P>::value;
	};





} // namespace geometry


#endif // _GEOMETRY_GEOMETRY_TRAITS_HPP
