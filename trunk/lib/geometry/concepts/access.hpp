// Geometry Library Point traits
//
// Copyright Bruno Lalande 2008
// Copyright Barend Gehrels, Geodan Holding B.V. Amsterdam, the Netherlands.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef _GEOMETRY_ACCESS_HPP
#define _GEOMETRY_ACCESS_HPP


#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/remove_const.hpp>

#include <geometry/concepts/coordinate.hpp>


namespace geometry
{
	/*!
		\brief helper metafunction to forward constness 
		\ingroup Concepts
	*/
	template <typename S, typename D>
	struct forward_const: boost::mpl::if_<boost::is_const<S>, const D, D>
	{};


	namespace traits
	{
		/*!
			\brief access metafunction, primary definition (forwards to the nested get() function)
			\ingroup Concepts
			\details
			@copydetails traits::dimension
		*/
		template <typename P>
		struct access
		{
			template <int I, typename PP>
			static typename forward_const<PP, typename support::coordinate<P>::type>::type&
			get(PP& p)
			{ return p.template get<I>(); }
		};
	}



	namespace impl
	{
		/*!
			\brief helper metafunction for implementation of standalone get<>(P) function
			\ingroup Concepts
			\details Only used by get function
		*/
		template <typename P>
		struct access: traits::access<typename boost::remove_const<P>::type>
		{};
	}


	/*!
		\brief Standalone get<>(P) function
		\ingroup Concepts
		\details This useful function calls the access metafunction of the pointtype to get access
		to the coordinates of the specified point argument. It works for all pointtypes which fulfil to
		the Point concept requirements.
	*/
	template <int I, typename P>
	typename forward_const<P, typename support::coordinate<P>::type>::type&
	get(P& p)
	{
		return impl::access<P>::template get<I>(p);
	};
}


#endif
