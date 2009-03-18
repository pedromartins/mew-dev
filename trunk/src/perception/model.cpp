/*
 * model.cpp
 *
 *  Created on: 16-Feb-2009
 *      Author: Hok Shun Poon
 */


#include "include/model.h"


GridModel::GridModel(int width, int height)
: width(width), height(height){
	map = new MapElement[width][height];
}

GridModel::~GridModel(){
	delete map;
}
