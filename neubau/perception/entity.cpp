/*
 * entity.cpp
 *
 *  Created on: 18-Apr-2009
 *      Author: fushunpoon
 */

#include "entity.h"

ostream& operator << (ostream& os, const IEntity& rhs) {
	os << rhs.toString();
}
