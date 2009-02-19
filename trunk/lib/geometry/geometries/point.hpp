// Geometry Library
//
// Copyright Barend Gehrels, Geodan Holding B.V. Amsterdam, the Netherlands.
// Copyright Bruno Lalande 2008
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef _GEOMETRY_POINT_HPP
#define _GEOMETRY_POINT_HPP

#include <stdexcept>


#include <boost/numeric/conversion/bounds.hpp>
#include <boost/static_assert.hpp>
#include <boost/assert.hpp>
#include <boost/concept/requires.hpp>


#include <geometry/concepts/point_concept.hpp>

#include <geometry/geometries/init.hpp>

#include <geometry/util/math.hpp>


namespace geometry
{



	/*!
		\brief Basic point class, having coordinates dfined in a neutral way
		\ingroup Geometry
		\par Template parameters:
		- \a T numeric type, for example double, float, int
		- \a D number of coordinates, for example 2
	*/
	template<typename T, size_t D>
	class point
	{
		public :
			// Member type/const
			typedef T coordinate_type;
			static const size_t coordinate_count = D;


			/// Default constructor, no initialization at all
			inline point()
			{}

			/// Constructs with one, or optionally two or three values
			inline point(const T& v0, const T& v1 = 0, const T& v2 = 0)
			{
				if (D >= 1) m_values[0] = v0;
				if (D >= 2) m_values[1] = v1;
				if (D >= 3) m_values[2] = v2;
			}

			/// Constructs with an option
			inline point(init option)
			{
				switch(option)
				{
					case init_zero :
						{
							for (register size_t i = 0; i < D; i++)
							{
								// Use the template-init-zero-construction to init at zero
								m_values[i] = T();
							}
						}
						break;
					case init_min_infinite :
						{
							for (register size_t i = 0; i < D; i++)
							{
								m_values[i] = boost::numeric::bounds<T>::lowest();
							}
						}
						break;
					case init_max_infinite :
						{
							for (register size_t i = 0; i < D; i++)
							{
								m_values[i] = boost::numeric::bounds<T>::highest();
							}
						}
						break;
					case init_inverse :
							throw std::invalid_argument("The init_reverse option cannot be used here");
						break;
				}
			}

			/// Compile time access to coordinate values
			template <size_t K>
			inline T& get()
			{
				BOOST_STATIC_ASSERT(K < D);
				return m_values[K];
			}

			template <size_t K>
			inline const T& get() const
			{
				BOOST_STATIC_ASSERT(K < D);
				return m_values[K];
			}


			/// Examine if point is equal to other point
			inline bool operator==(const point& other) const
			{
				for (register size_t i = 0; i < D; i++)
				{
					if (! equals(m_values[i], other.m_values[i]))
					{
						return false;
					}
				}
				return true;
			}

			/// Examine if points are NOT equal
			inline bool operator!=(const point& other) const
			{
				return ! operator==(other);
			}

		private :
			T m_values[D];
	};




} // namespace geometry


#endif // _GEOMETRY_POINT_HPP
