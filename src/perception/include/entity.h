/*
 * entity.h
 *
 *  Created on: 16-Feb-2009
 *      Author: Hok Shun Poon
 */

#ifndef ENTITY_H_
#define ENTITY_H_

/*
 * UnknownEntity
 *
 * An unknown entity can be used to update the model.
 * An unknown entity may have ANY
 *
 */
class UnknownEntity : public StaticEntity {
public:
	entity();
	virtual ~entity();
};

#endif /* ENTITY_H_ */
