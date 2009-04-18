/*
 * entity.h
 *
 *  Created on: 14-Apr-2009
 *      Author: fushunpoon
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include <sstream>
#include <ostream>

using namespace std;

/*
 * TODO expand this class:
 * currently a mock class for representing *some* entity in the
 * SimpleVirtualWorld.
 */
class IEntity {
public:

	// outputs this entity as a string. Uses toString;
	friend ostream& operator << (ostream& os, const IEntity& rhs);

	/**
	 * Returns the string representation of the entity.
	 * @return string
	 */
	virtual std::string toString() const {
		std::stringstream ss;
		ss << this;
		return ss.str();
	}
};

// Reverting to plain pointer type.
typedef IEntity * EntityPtr;

#endif /* ENTITY_H_ */
