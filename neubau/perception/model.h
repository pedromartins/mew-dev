/*
 * virtualworld.h
 *
 *  Created on: 04-Mar-2009
 *      Author: fushunpoon
 */

#ifndef MODEL_H
#define MODEL_H

#define DEFAULT_SIZE 10

#include <iostream>
#include <string.h>
#include <map>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <core/core.h>
#include "entity.h"

#define VWORLD_NO_SUCH_ENTITY -426
#define VWORLD_INVALID_SQUARE -427

/**
 * Enum type for representing a drop zone.
 */
typedef enum MapElement {
  EMPTY, PIECE, DROPZONE, FORBIDDEN
} MapElement;

using namespace std;


/**
 * A type for holding the entities.
 * There are no constraints or requirements as to what an Entity
 * maybe.
 */
typedef Static<int, Orientation> Staticio;
typedef map<EntityPtr, Staticio> EntStatMap;

/**
 * SimpleModel
 *
 * Imitates the real world in software.
 *
 * The simple model provides a basis with which virtual sensors, and virtual actuators interact.
 *
 */
class SimpleModel {
public:
	/**
	 * Creates a custom sized Virtual world.
	 * @param width
	 * @param height
	 * @return
	 */
	SimpleModel(const int width = DEFAULT_SIZE, const int height = DEFAULT_SIZE);
	virtual ~SimpleModel();

	/**
	 * Returns the map element at a particular position.
	 * @param pos the position
	 * @throw -427 VWORLD_INVALID_SQUARE If the given position is invalid
	 */
	MapElement getElementAt(const Vector2di& pos) const
	{
		if (valid(pos)) {
			return arr[pos.x][pos.y];
		} else throw VWORLD_INVALID_SQUARE;
	}

	/**
	 * Returns the map element at a particular position.
	 * @param posx
	 * @param posy
	 * @throw -427 VWORLD_INVALID_SQUARE If the given position is invalid
	 */
	MapElement getElementAt(int posx, int posy) const
	{
		if (valid(posx,posy)) {
			return arr[posx][posy];
		} else throw VWORLD_INVALID_SQUARE;
	}

	/**
	 * Puts a piece onto the map.
	 * @param posx The x coordinate
	 * @param posy The y coordinate
	 */
	void putPiece(int posx, int posy) {
		if (valid(posx, posy)) {
			arr[posx][posy] = PIECE;
		}
	}

	/**
	 * Removes a piece from the map.
	 * @param posx
	 * @param posy
	 */
	void removePiece(int posx, int posy){
		if (valid(posx, posy)) {
			arr[posx][posy] = EMPTY;
		}
	}

	/**
	 * Returns the 'actual' location of the entity.
	 * @param entity
	 * @throw -426 VWORLD_NO_SUCH_ENTITY when no entity by the given pointer is found.
	 */
	Vector2di getPositionOf(EntityPtr entity) const {
		EntStatMap::const_iterator i;
		if ((i = entmap.find(entity))!=entmap.end()) {
			return i->second.position;
		} else {
			throw VWORLD_NO_SUCH_ENTITY;
		}
	}

	/**
	 * Sets the location of the entity pointed to by entity.
	 * @param entity   An entity reference
	 * @param location The entity's location
	 */
	void setLocationOf(EntityPtr entity, Vector2di location) {
		if (!valid(location)) {
			cerr << "SimpleModel: OH DEAR! tried to move "
					"entity to invalid place" << endl;
			return;
		}

		entmap[entity].position = location;
	}

	/**
	 * Returns the 'actual' location of the entity.
	 * @param entity
	 * @throw -426 NO_SUCH_ENTITY When the given entity does not exist.
	 */
	Orientation getOrientationOf(EntityPtr entity) const {
		EntStatMap::const_iterator i;
		if ((i=entmap.find(entity))!=entmap.end()){
			return i->second.orientation;
		} else throw VWORLD_NO_SUCH_ENTITY;
	}

	/**
	 * Returns the 'actual' location of the entity.
	 * @param entity
	 * @param orientation
	 * @throw -426 VWORLD_NO_SUCH_ENTITY
	 */
	void setOrientationOf(EntityPtr entity,Orientation orientation) {
		if (entmap.find(entity)!=entmap.end()) {
			entmap[entity].orientation = orientation;
		} else throw VWORLD_NO_SUCH_ENTITY;
	}

	/**
	 * Returns whether are particular location is empty or not.
	 * @param location the location to be checked for emptiness.
	 */
	bool isEmpty(Vector2di location) const {
		if (valid(location)) {
			return arr[location.x][location.y] == EMPTY;
		} else throw VWORLD_INVALID_SQUARE;
	}

	/**
	 * Registers an entity with this world, with a given state.
	 * @param entity
	 * @param state
	 * @throw -427 VWORLD_INVALID_SQUARE when the actual state of the robot
	 * is invalid (i.e., outside bounds of world.
	 */
	void putEntity(EntityPtr entity, Staticio& state){
		if (valid(state.position)) {
			entmap[entity] = state;
		} else throw VWORLD_INVALID_SQUARE;
	}

	/**
	 * Unregisters an entity with this world.
	 * @param entity
	 */
	void removeEntity(EntityPtr entity) {
		entmap.erase(entity);
	}

	/**
	 * Removes all the pieces.
	 */
	void clear() {
		for(int i = 0 ; i < width; ++i) {
			for (int j= 0; j < height; ++j) {
				arr[i][j] = EMPTY;
			}
		}
	}

	int getWidth() const { return width; }
	int getHeight() const { return height; }

	/**
	 * Returns true iff the coordinates given by x and y are fully contained within
	 * this SimpleModel.
	 * @param x
	 * @param y
	 * @return
	 */
	bool valid(int x, int y) const {
		return (x >= 0 && x < width &&
				y >= 0 && y < height);
	}

	/**
	 * Returns true iff the position is a valid coordinate in this world.
	 * @param newPos
	 * @return
	 */
	bool valid(Vector2di newPos) const {
		return (newPos.x >= 0 && newPos.x < width &&
				newPos.y >= 0 && newPos.y < height);
	}

	/**
	 * Returns the square 'in front' of the entity in question.
	 * May return invalid squares.
	 * @param entity The entity
	 * @return
	 */
	Vector2di inFront(EntityPtr entity) const {
		Vector2di pos = getPositionOf(entity);

		return  pos + dOffsets[getOrientationOf(entity)];
	}

	/**
	 * Prints this Virtual world out onto the given output stream.
	 * Cannot accurately represent entities, sadly.
	 * @param os	The output stream.
	 * @param world The world.
	 * @return
	 */
	friend ostream& operator << (ostream& os, const SimpleModel& world);


	/** Directional offsets array of vectors, for ease of offsetting a square in some direction. */
	static Vector2di dOffsets[4];
private:

	int width; /// the width of the simple model
	int height; /// the height of the simple model
	MapElement **arr; // multi-dimensional array.

	EntStatMap entmap;
};


#endif // MODEL_H
