/*
 * entity.h
 *
 *  Created on: 14-Apr-2009
 *      Author: fushunpoon
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include <sstream>
#include <boost/shared_ptr.hpp>

// TODO mock class for representing *some* entity.
class IEntity {
public:

	// outputs this entity as a string. Uses toString;
	friend std::ostream& operator << (std::ostream & os, const IEntity& rhs);

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

typedef boost::shared_ptr<IEntity> EntityPtr;

#endif /* ENTITY_H_ */
