// Geometry Library
//
// Copyright Barend Gehrels, Geodan Holding B.V. Amsterdam, the Netherlands.
// Copyright Bruno Lalande 2008
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef _GEOMETRY_POINT_XY_HPP
#define _GEOMETRY_POINT_XY_HPP

#include <geometry/geometries/point.hpp>

namespace geometry
{


	/*!
		\brief 2D point in Cartesian coordinate system
		\ingroup Geometry
		\par Template parameters:
		- \a T numeric type, arguments can be, for example, double, float, int
	*/
	template<typename T>
	class point_xy : public point<T, 2>
	{
		public :
			/// Default constructor, does not initialize anything
			inline point_xy() : point<T, 2>() {}
			/// Constructor with x/y values
			inline point_xy(const T& x, const T& y) : point<T, 2>(x, y) {}
			/// Constructor with an option
			inline point_xy(init option) : point<T, 2>(option) {}

			/// Get x-value
			inline const T& x() const
			{ return this->template get<0>(); }

			/// Get y-value
			inline const T& y() const
			{ return this->template get<1>(); }

			/// Set x-value
			inline void x(const T& v)
			{ this->template get<0>() = v; }

			/// Set y-value
			inline void y(const T& v)
			{ this->template get<1>() = v; }

			/// Compare two points
			inline bool operator<(const point_xy& other) const
			{
				return equals(x(), other.x()) ? y() < other.y() : x() < other.x();
			}
	};



} // namespace geometry


#endif // _GEOMETRY_POINT_XY_HPP
