// Geometry Library
//
// Copyright Barend Gehrels, Geodan Holding B.V. Amsterdam, the Netherlands.
// Copyright Bruno Lalande 2008
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef _GEOMETRY_POLYGON_HPP
#define _GEOMETRY_POLYGON_HPP

#include <vector>

#include <boost/concept/assert.hpp>

#include <geometry/concepts/point_concept.hpp>

#include <geometry/geometries/geometry_traits.hpp>

namespace geometry
{



	/*!
		\brief A linear_ring (linear linear_ring) is a closed line which should not be selfintersecting
		\ingroup Geometry
		\par Template parameters:
		- \a P point type
		- \a V optional container type, for example std::vector, std::list, std::deque
		- \a A optional container-allocator-type
	*/
	template<typename P,
			template<typename,typename> class V = std::vector,
			template<typename> class A = std::allocator>
	class linear_ring : public V<P, A<P> >, public geometry_traits<P>
	{
		BOOST_CONCEPT_ASSERT((Point<P>));
	};


	/*!
		\brief The \b polygon contains an outer ring and zero or more inner rings.
		\ingroup Geometry
		\par Template parameters:
		- \a P point type
		- \a VR optional container type for inner rings, for example std::vector, std::list, std::deque
		- \a VP optional container type for points, for example std::vector, std::list, std::deque
		- \a AR container-allocator-type
		- \a AP container-allocator-type
		\note The container collecting the points in the rings can be different from the
		container collecting the inner rings. They all default to vector.
	*/
	template<typename P,
			template<typename,typename> class VP = std::vector,
			template<typename,typename> class VR = std::vector,
			template<typename> class AP = std::allocator,
			template<typename> class AR = std::allocator>
	class polygon : public geometry_traits<P>
	{
		BOOST_CONCEPT_ASSERT((Point<P>));

		public :
			// Member types
			typedef linear_ring<P, VP, AP> ring_type;
			typedef VR<ring_type , AR<ring_type > > inner_container_type;

			inline const ring_type& outer() const { return m_outer; }
			inline const inner_container_type & inners() const { return m_inners; }

			inline ring_type& outer() { return m_outer; }
			inline inner_container_type & inners() { return m_inners; }

			/// Utility method, clears outer and inner rings
			inline void clear()
			{
				m_outer.clear();
				m_inners.clear();
			}

		private :
			ring_type m_outer;
			inner_container_type m_inners;
	};


} // namespace geometry


#endif //_GEOMETRY_POLYGON_HPP
