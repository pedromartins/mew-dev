// Geometry Library
//
// Copyright Barend Gehrels, Geodan Holding B.V. Amsterdam, the Netherlands.
// Copyright Bruno Lalande 2008
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef _GEOMETRY_BOX_HPP
#define _GEOMETRY_BOX_HPP

#include <boost/numeric/conversion/bounds.hpp>

#include <geometry/concepts/point_concept.hpp>

#include <geometry/geometries/init.hpp>

#include <geometry/geometries/geometry_traits.hpp>

#include <geometry/util/assign.hpp>
#include <geometry/util/copy.hpp>

namespace geometry
{

	/*!
		\brief Class box: defines a box made of two describing points
		\ingroup Geometry
		\details Box is always described by a min_corner() and a max_corner() point. If another
		rectangle is used, use linear_ring or polygon.
		\note Boxes are for selections and for calculating the envelope of geometries. Not all algorithms
		are implemented for box. Boxes are also used in Spatial Indexes.
		\par Template parameters:
		- \a P point type. The box takes a point type as template parameter.
		The point type can be any point type.
		It can be 2D but can also be 3D or more dimensional.
		The box can also take a latlong point type
		as template parameters.
	 */

	template<typename P>
	class box : public geometry_traits<P>
	{
		BOOST_CONCEPT_ASSERT((Point<P>));

		public :
			typedef typename support::coordinate<P>::type coordinate_type;

			/*!
				\brief Default constructor, initializing box to the default constructor
			*/
			inline box()
			{
				// Initialize to zero (?), we might change this to nothing, because
				// there is already another constructor which does this.
				assign_value(m_min_corner, coordinate_type());
				assign_value(m_max_corner, coordinate_type());
			}

			/*!
				\brief Constructor taking the minimum corner point and the maximum corner point
			*/
			inline box(const P& min_corner, const P& max_corner)
			{
				copy_coordinates(min_corner, m_min_corner);
				copy_coordinates(max_corner, m_max_corner);
			}

			/*!
				\brief Constructor with an option, constructing to zero, or making an inverse box
				(convenient for calculating envelopes)
			*/
			inline box(init option)
			{
				switch(option)
				{
					case init_inverse :
						assign_value(m_min_corner,
								boost::numeric::bounds<coordinate_type>::highest());
						assign_value(m_max_corner,
								boost::numeric::bounds<coordinate_type>::lowest());
						break;
					case init_zero :
						assign_value(m_min_corner, coordinate_type());
						assign_value(m_max_corner, coordinate_type());
						break;
					default :
						// no construction at all
						break;
				}
			}


			inline const P& min_corner() const { return m_min_corner; }
			inline const P& max_corner() const { return m_max_corner; }

			inline P& min_corner() { return m_min_corner; }
			inline P& max_corner() { return m_max_corner; }

		private :
			P m_min_corner, m_max_corner;
	};


};

#endif // _GEOMETRY_BOX_HPP
