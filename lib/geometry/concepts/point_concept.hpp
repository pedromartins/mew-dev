// Geometry Library Point concept
//
// Copyright Bruno Lalande 2008
// Copyright Barend Gehrels, Geodan Holding B.V. Amsterdam, the Netherlands.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef _GEOMETRY_POINT_CONCEPT_HPP
#define _GEOMETRY_POINT_CONCEPT_HPP


#include <boost/concept_check.hpp>

#include <geometry/concepts/coordinate.hpp>
#include <geometry/concepts/dimension.hpp>
#include <geometry/concepts/access.hpp>

/*!
\defgroup Concepts Concepts: concept definitions
Concepts are used to check if pointtypes provide required implementation. Concept checking
is done using BCCL (Boost Concept Check Library) and MPL (Meta Programming Library)
*/


namespace geometry
{


	/*!
		\brief Defines point concept, using Boost Concept Check Library and metafunctions
		\ingroup Concepts
		\details The concept is separated into 3 metafunctions:
		- \ref geometry::traits::coordinate "coordinate": provides the type of the coordinates of a point
		- \ref geometry::traits::dimension "dimension": provides the number of coordinates of a point
		- \ref geometry::traits::access "access": provides access to the coordinates of a point

		In MPL, a metafunction that provides a type must expose is as "type"
		and a metafunction that provides a value must expose it as "value", so
		here the same convention are used: coordinate<P>::type and
		dimension<P>::value provide the type and number of coordinates. This
		makes them compatible with any MPL and Fusion algorithm and
		metafunction.
		
		\par Example:
		First example, using an own pointtype, for example a legacy point, defining the necessary
		properties outside the pointtype in a traits class
		\dontinclude doxygen_examples.cpp
		\skip example_point_1
		\until //:\\
		\par Example:
		Second example, deriving a pointtype from boost::tuple. It defines the necessary properties
		itself, so a separate traits class is not necessary.
		\dontinclude doxygen_examples.cpp
		\skip example_own_point2
		\line {
		\until //:\\
	*/
	template <typename X>
	struct Point
	{
		private :
			typedef typename support::coordinate<X>::type ctype;
			enum { ccount = support::dimension<X>::value };

			/// Internal structure to check if access is OK for all dimensions
			template <typename P, int I, int Count>
			struct dimension_checker
			{
				static void check()
				{
					P* p;
					geometry::get<I>(*p) = ctype();
					dimension_checker<P, I+1, Count>::check();
				}
			};

			/// Internal structure to check if access is OK for all dimensions
			template <typename P, int Count>
			struct dimension_checker<P, Count, Count>
			{
				static void check() {}
			};

		public :
			/// BCCL macro to check the Point concept
			BOOST_CONCEPT_USAGE(Point)
			{
				dimension_checker<X, 0, ccount>::check();
			}
	};


	/*!
		\brief Defines Point concept (const version)
		\ingroup Concepts
		\details The ConstPoint concept check the same as the Point concept, 
		but does not check write access.
	*/
	template <typename X>
	struct ConstPoint
	{
		private :
			typedef typename support::coordinate<X>::type ctype;
			enum { ccount = support::dimension<X>::value };

			/// Internal structure to check if access is OK for all dimensions
			template <typename P, int I, int Count>
			struct dimension_checker
			{
				static void check()
				{
					const P* p = 0;
					ctype coord(geometry::get<I>(*p));
					(void)sizeof(coord); // To avoid "unused variable" warnings
					dimension_checker<P, I+1, Count>::check();
				}
			};

			/// Internal structure to check if access is OK for all dimensions
			template <typename P, int Count>
			struct dimension_checker<P, Count, Count>
			{
				static void check() {}
			};

		public :
			/// BCCL macro to check the ConstPoint concept
			BOOST_CONCEPT_USAGE(ConstPoint)
			{
				dimension_checker<X, 0, ccount>::check();
			}
	};
}


#endif
