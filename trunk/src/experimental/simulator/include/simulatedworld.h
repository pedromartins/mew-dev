#ifndef SIMULATEDWORLD_H
#define SIMULATEDWORLD_H

#include <map>
#include <core.h>

#define DEFAULT_SIZE 10

#define OUT_OF_BOARD "The robot went outside of the board!\n"
#define COLLISION "The robot collided with something!\n"
#define SUCCESS "Congratulations, task successful!\n Now go play with the simulator code :)\n"

using namespace mew;
using namespace core;


/**
 * SimulatedWorld
 *
 * In a simple grid model, the robot and anything IN the grid is
 * simply represented by some enum value in a 2D array.
 *
 * NOTE: this is a wrapper around the old simulator model.
 */
class SimulatedWorld {

	/**
	 * Creates a default pre-made Simulated world configuration.
	 */
	SimulatedWorld(int map = 0);
	SimulatedWorld(int width, int height);
	virtual ~SimulatedWorld();

	/**
	 * Returns the map element at a particular position.
	 * @param pos the position
	 */
	MapElement getElementAt(Vector2di pos)
	{
		return map[pos.x][pos.y];
	}

	MapElement getElementAt(int posx, int posy)
	{
		return map[posx][posy];
	}

	/**
	 * Puts a piece onto the map.
	 * @param posx The x coordinate
	 * @param posy The y coordinate
	 */
	void putPiece(int posx, int posy) {
		map[posx][posy] = PIECE;
	}

	/**
	 * Removes a piece from the map.
	 * @param posx
	 * @param posy
	 */
	void removePiece(int posx, int posy){
		map[posx][posy] = EMPTY;
	}

	/**
	 * Returns the 'actual' location of the entity.
	 */
	Vector2di getLocationOf(Entity *entity) {
		return entmap[entity].position;
	}

	/**
	 * Sets the location of the entity pointed to by entity.
	 */
	void setLocationOf(Entity *entity, Vector2di location){
		entmap[entity].position = location;
	}

	/**
	 * Returns the 'actual' location of the entity.
	 */
	Vector2di getOrientationOf(Entity *entity) {
		return entmap[entity].orientation;
	}

	/**
	 * Sets the location of the entity pointed to by entity.
	 */
	void setLocationOf(Entity *entity, Vector2di location){
		entmap[entity].position = location;
	}

	/**
	 * Registers an entity with this simulated world.
	 */
	void putEntity(Entity *entity, Vector2di location){
		entmap[entity] = location;
	}

	void removeEntity(Entity *entity) {
		entmap.erase(entity);
	}

	/**
	 * Removes all the pieces.
	 */
	void clear() {
		memset(map,EMPTY,width*height*sizeof(MapElement));
	}

private:
	int width;
	int height;
	MapElement map[][];

	map<Entity *, mew::core::Static> entmap;
};



#endif //MAP_H
