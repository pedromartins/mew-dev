// Geometry Library Point traits
//
// Copyright Bruno Lalande 2008
// Copyright Barend Gehrels, Geodan Holding B.V. Amsterdam, the Netherlands.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef _GEOMETRY_COORDINATE_HPP
#define _GEOMETRY_COORDINATE_HPP



#include <boost/type_traits/remove_const.hpp>


namespace geometry
{
	namespace traits
	{
		/*!
			\brief coordinate metafunction, makes coordinate_type of templatized pointtype known as "type"
			\ingroup Concepts
			\details
			@copydetails traits::dimension
		*/
		template <typename P>
		struct coordinate
		{ typedef typename P::coordinate_type type; };
	}

	namespace support
	{
		/*!
			\brief coordinate metafunction, used by concept Point to check if pointtype defines coordinate type
			\ingroup Concepts
			\details
			@copydetails traits::dimension
		*/  
		template <typename P>
		struct coordinate: traits::coordinate<typename boost::remove_const<P>::type>
		{};
	}
}


#endif
