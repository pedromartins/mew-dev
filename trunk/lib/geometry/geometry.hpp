// Geometry Library
//
// Copyright Barend Gehrels, Geodan Holding B.V. Amsterdam, the Netherlands.
// Copyright Bruno Lalande 2008
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef _GEOMETRY_GEOMETRY_HPP
#define _GEOMETRY_GEOMETRY_HPP

// Shortcut to include all header files

#include <geometry/concepts/access.hpp>
#include <geometry/concepts/coordinate.hpp>
#include <geometry/concepts/dimension.hpp>
#include <geometry/concepts/point_concept.hpp>
#include <geometry/concepts/adapted/c_array.hpp>

#include <geometry/geometries/box.hpp>
#include <geometry/geometries/circle.hpp>
#include <geometry/geometries/geometry_traits.hpp>
#include <geometry/geometries/init.hpp>
#include <geometry/geometries/linestring.hpp>
#include <geometry/geometries/point.hpp>
#include <geometry/geometries/point_ll.hpp>
#include <geometry/geometries/point_xy.hpp>
#include <geometry/geometries/polygon.hpp>
#include <geometry/geometries/segment.hpp>

#include <geometry/arithmetic/arithmetic.hpp>
#include <geometry/arithmetic/dot_product.hpp>

#include <geometry/strategies/strategies_point_ll.hpp>
#include <geometry/strategies/strategies_point_xy.hpp>
#include <geometry/strategies/strategy_traits.hpp>

#include <geometry/util/for_each_coordinate.hpp>
#include <geometry/util/assign.hpp>
#include <geometry/util/copy.hpp>
#include <geometry/util/grow.hpp>
#include <geometry/util/promotion_traits.hpp>
#include <geometry/util/math.hpp>
#include <geometry/util/return_types.hpp>
#include <geometry/util/side.hpp>

#include <geometry/algorithms/area.hpp>
#include <geometry/algorithms/centroid.hpp>
#include <geometry/algorithms/distance.hpp>
#include <geometry/algorithms/envelope.hpp>
#include <geometry/algorithms/foreach.hpp>
#include <geometry/algorithms/intersection.hpp>
#include <geometry/algorithms/length.hpp>
#include <geometry/algorithms/loop.hpp>
#include <geometry/algorithms/simplify.hpp>
#include <geometry/algorithms/within.hpp>

#include <geometry/util/correct.hpp>

#include <geometry/io/wkt/aswkt.hpp>
#include <geometry/io/wkt/fromwkt.hpp>
#include <geometry/io/wkt/streamwkt.hpp>



#endif // _GEOMETRY_GEOMETRY_HPP
