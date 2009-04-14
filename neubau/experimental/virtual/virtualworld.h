/*
 * virtualworld.h
 *
 *  Created on: 04-Mar-2009
 *      Author: fushunpoon
 */

#ifndef VIRTUAL_WORLD_H
#define VIRTUAL_WORLD_H

#define DEFAULT_SIZE 10

#include <iostream>
#include <string.h>
#include <map>
#include <vector>
#include <core/core.h>
#include "entity.h"

/**
 * Enum type for representing a drop zone.
 */
typedef enum MapElement {
  EMPTY, PIECE, DROPZONE, FORBIDDEN
} MapElement;

/**
 * Enum type for representing the four directions
 */
typedef enum Orientation {
	NORTH=0, WEST, SOUTH, EAST
} Orientation;

/**
 * A type for holding the entities.
 * There are no constraints or requirements as to what an Entity
 * maybe.
 */
typedef map<IEntity *, Static<int,Orientation> *> EntityMap;

using namespace std;

/**
 * VirtualWorld
 *
 * In a simple grid model, the robot and anything IN the grid is
 * simply represented by some enum value in a 2D array.
 *
 * NOTE: this is a wrapper around the old simulator model.
 */
class VirtualWorld {
public:
	/**
	 * Creates a custom sized Virtual world.
	 * @param width
	 * @param height
	 * @return
	 */
	VirtualWorld(const int width = DEFAULT_SIZE, const int height = DEFAULT_SIZE);
	virtual ~VirtualWorld();

	/**
	 * Returns the map element at a particular position.
	 * @param pos the position
	 */
	MapElement getElementAt(const Vector2di& pos) const
	{
		return arr[pos.x][pos.y];
	}

	MapElement getElementAt(int posx, int posy) const
	{
		return arr[posx][posy];
	}

	/**
	 * Puts a piece onto the map.
	 * @param posx The x coordinate
	 * @param posy The y coordinate
	 */
	void putPiece(int posx, int posy) {
		arr[posx][posy] = PIECE;
	}

	/**
	 * Removes a piece from the map.
	 * @param posx
	 * @param posy
	 */
	void removePiece(int posx, int posy){
		arr[posx][posy] = EMPTY;
	}

	/**
	 * Returns the 'actual' location of the entity.
	 * @param entity  The entity
	 */
	Vector2di getPositionOf(IEntity *entity) {
		return entmap[entity]->position;
	}

	/**
	 * Sets the location of the entity pointed to by entity.
	 * @param entity   An entity reference
	 * @param location The entity's location
	 */
	void setLocationOf(IEntity *entity, Vector2di location) {
		if (!valid(location)) {
			cerr << "VirtualWorld: OH DEAR! tried to move "
					"entity to invalid place" << endl;
			return;
		}

		entmap[entity]->position = location;
	}

	/**
	 * Returns the 'actual' location of the entity.
	 * @param entity
	 * @param orientation
	 */
	void setOrientationOf(IEntity *entity,Orientation orientation) {
		entmap[entity]->orientation = orientation;
	}

	/**
	 * Returns the 'actual' location of the entity.
	 */
	Orientation getOrientationOf(IEntity *entity) {
		return entmap[entity]->orientation;
	}

	/**
	 * Returns whether are particular location is empty or not.
	 * @param location the location to be checked for emptiness.
	 */
	bool isEmpty(Vector2di location) const {
		return arr[location.x][location.y] == EMPTY;
	}

	/**
	 * Registers an entity with this world, with a given state.
	 * @param entity
	 * @param location
	 */
	void putEntity(IEntity *entity, Static<int,Orientation> * state){
		entmap[entity] = state;
	}

	/**
	 * Unregisters an entity with this world.
	 * @param entity
	 */
	void removeEntity(IEntity *entity) {
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
	 * Returns true iff the position is a valid coordinate in this world.
	 * @param newPos
	 * @return
	 */
	bool valid(Vector2di newPos) {
		return (newPos.x >= 0 && newPos.x < width &&
				newPos.y >= 0 && newPos.y < height);
	}

	/**
	 * Returns the square 'in front' of the entity in question.
	 * @return
	 */
	Vector2di inFront(IEntity *ent) {
		return getPositionOf(ent) + dOffsets[getOrientationOf(ent)];
	}

	/**
	 * Prints this Virtual world out onto the given output stream.
	 * Cannot accurately represent entities, sadly.
	 * @param os	The output stream.
	 * @param world The world.
	 * @return
	 */
	friend ostream& operator << (ostream& os, const VirtualWorld& world);

	static Vector2di dOffsets[4];
private:

	int width; /// the width of the virtual world
	int height; /// the height of the virtual world
	MapElement **arr; // multi-dimensional array.

	EntityMap entmap;
};


#endif // VIRTUALWORLD_H
