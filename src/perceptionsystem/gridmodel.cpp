/*
 * gridmodel.cpp
 *
 *  Created on: 04-Mar-2009
 *      Author: fushunpoon
 */

#include "include/gridmodel.h"

GridModel::GridModel() {
	srand(time(0));
	initPredefMap(mapNum);
	placePiece(SIZE_X-1, 0);
}

GridModel::~GridModel() {
	// TODO Auto-generated destructor stub
}
