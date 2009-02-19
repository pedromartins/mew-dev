// Geometry Library
//
// Copyright Barend Gehrels, Geodan Holding B.V. paris, the Netherlands.
// Copyright Bruno Lalande 2008
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

#include <geometry/geometries/point_ll.hpp>
#include <geometry/algorithms/distance.hpp>
#include <geometry/io/wkt/streamwkt.hpp>


int main()
{
	// Declare a latlong point, using degrees and doubles
	geometry::point_ll<geometry::degree, double> paris;

	// Assign coordinates to the latlong point, using the methods lat and lon
	// Paris 48° 52' 0" N, 2° 19' 59" E
	paris.lat(geometry::dms<geometry::north>(48, 52, 0));
	paris.lon(geometry::dms<geometry::east>(2, 19, 59));

	std::cout << "Paris: " << paris << std::endl;

	// Convert a latlong point to radians
	geometry::point_ll<geometry::radian, double> ra;
	geometry::convert_dr(paris, ra);
	std::cout << "Paris in radians: " << ra << std::endl;

	// Constructor using explicit latitude/longitude
	// Lima 12° 2' 36" S, 77° 1' 42" W
	geometry::point_ll<geometry::degree, double> lima(
			geometry::latitude<>(geometry::dms<geometry::south>(12, 2, 36)),
			geometry::longitude<>(geometry::dms<geometry::west>(77, 1, 42)));

	std::cout << "Lima: " << lima << std::endl;


	// Calculate the distance using the default strategy, and Vincenty, Andoyer
	std::cout << "Distance Paris-Lima "
		<< 0.001 * geometry::distance(paris, lima)
		<< " km" << std::endl;

	std::cout << "Distance Paris-Lima, Vincenty "
		<< 0.001 * geometry::distance(paris, lima,
				geometry::strategy::distance::vincenty<geometry::point_ll<geometry::degree> >())
		<< " km" << std::endl;

	std::cout << "Distance Paris-Lima, Andoyer "
		<< 0.001 * geometry::distance(paris, lima,
				geometry::strategy::distance::andoyer<geometry::point_ll<geometry::degree> >())
		<< " km" << std::endl;

	return 0;
}
