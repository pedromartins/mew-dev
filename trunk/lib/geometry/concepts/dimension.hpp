// Geometry Library Point traits
//
// Copyright Bruno Lalande 2008
// Copyright Barend Gehrels, Geodan Holding B.V. Amsterdam, the Netherlands.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef _GEOMETRY_DIMENSION_HPP
#define _GEOMETRY_DIMENSION_HPP


#include <boost/mpl/int.hpp>
#include <boost/type_traits/remove_const.hpp>


namespace geometry
{
	namespace traits
	{
		/*!
			\brief dimension metafunction, used by concept Point to check if pointtype has an enumeration which defines
			the number of dimensions
			\ingroup Concepts
			\details
			- This is one of the metafunctions defining a Point concept
			- Metafunctions normally have a primary definition, in namespace traits, and a const agnostic version, in namespace support
			- It is usually not used by the library user. If legacy points or other points are used it might be necessary to override these functions
		*/
		template <typename P>
		struct dimension: boost::mpl::int_<P::coordinate_count>
		{};
	}

	namespace support
	{
		/*!
			\brief dimension metafunction, used by concept Point to check if pointtype has an enumeration which defines
			the number of dimensions
			\ingroup Concepts
			\details
			@copydetails traits::dimension
		*/  
		template <typename P>
		struct dimension: traits::dimension<typename boost::remove_const<P>::type>
		{};
	}
}


#endif
