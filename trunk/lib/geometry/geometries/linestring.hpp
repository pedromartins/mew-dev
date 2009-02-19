// Geometry Library
//
// Copyright Barend Gehrels, Geodan Holding B.V. Amsterdam, the Netherlands.
// Copyright Bruno Lalande 2008
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef _GEOMETRY_LINESTRING_HPP
#define _GEOMETRY_LINESTRING_HPP

#include <vector>

#include <boost/concept/assert.hpp>

#include <geometry/concepts/point_concept.hpp>

#include <geometry/geometries/geometry_traits.hpp>

namespace geometry
{


	/*!
		\brief A linestring (named so by OGC) is a collection (default a vector) of points.
		\ingroup Geometry
		\par Template parameters:
		- \a P point type
		- \a V optional container type, for example std::vector, std::list, std::deque
		- \a A optional container-allocator-type
		(see http://accu.org/index.php/journals/427#ftn.d0e249 )
		\par Concepts:
		All algorithms work on iterator pairs, based on a container with point types fulfilling
		the point concepts. They will take linestring.begin(), linestring.end()
		but they will also take std::vector begin()/end(), or other containers.
	*/
	template<typename P,
			template<typename,typename> class V = std::vector,
			template<typename> class A = std::allocator>
	class linestring : public V<P, A<P> >, public geometry_traits<P>
	{
		BOOST_CONCEPT_ASSERT((Point<P>));

		public :
			// Default constructor
			linestring()
			{}

			// Construct from vector
			linestring(std::vector<P>& v)
			{
				for (typename std::vector<P>::const_iterator it = v.begin(); it != v.end(); it++)
				{
					this->push_back(*it);
				}
			}
	};


} // namespace geometry


#endif //_GEOMETRY_LINESTRING_HPP
