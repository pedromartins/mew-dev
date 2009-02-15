/*
 * HeightMap.h
 *
 *  Created on: 15-Feb-2009
 *      Author: Hok Shun Poon
 */

#ifndef HEIGHT_MAP_H_
#define HEIGHT_MAP_H_

/*
 *
 */
namespace mew {
namespace perception {


/**
 * HeightMap
 *
 * A HeightMap represents a particular channel of information about a 2D surface, at some
 * particular resolution.
 *
 *
 * HeightMap models are completely additive.
 */
template <typename T>
class HeightMap {
public:
	HeightMap();
	virtual ~HeightMap();
};


} /// END of namespace perception
} /// END of namespace mew

#endif /* HEIGHT_MAP_H_ */
