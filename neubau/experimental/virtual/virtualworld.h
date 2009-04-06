#ifndef SIMULATEDWORLD_H
#define VIRTUALWORLD_H

#include <map>
#include <core/core.h>

#define DEFAULT_SIZE 10

#define OUT_OF_BOARD "The robot went outside of the board!\n"
#define COLLISION "The robot collided with something!\n"
#define SUCCESS "Congratulations, task successful!\n Now go play with the simulator code :)\n"


// the area to drop the block.
int dropArea[] = {4,0};

/**
 * VirtualWorld
 *
 * In a simple grid model, the robot and anything IN the grid is
 * simply represented by some enum value in a 2D array.
 *
 * NOTE: this is a wrapper around the old simulator model.
 */
class VirtualWorld {

	/**
	 * Creates a default pre-made Simulated world configuration.
	 */
	VirtualWorld(int map = 0);
	VirtualWorld(int width = DEFAULT_SIZE, int height = DEFAULT_SIZE);
	virtual ~VirtualWorld();

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
	 * @param entity  The entity
	 */
	Vector2di getLocationOf(Entity *entity) {
		return entmap[entity].position;
	}

	/**
	 * Sets the location of the entity pointed to by entity.
	 * @param entity   An entity reference
	 * @param location The entity's location
	 */
	void setLocationOf(Entity *entity, Vector2di location) {
		if (!inBounds(location)) {
			std::cerr << "SimulatedWorld: OH DEAR! tried to move "
					"entity to invalid place" << std::endl;
			return;
		}

		entmap[entity].position = location;
	}

	/**
	 * Returns whether are particular location is empty or not.
	 * @param location the location to be checked for emptiness.
	 */
	bool isEmpty(Vector2di location) const {
		return map[location.X][location.Y] == EMPTY;
	}

	/**
	 * Returns the 'actual' location of the entity.
	 */
	Orientation getOrientationOf(Entity *entity) {
		return entmap[entity].orientation;
	}

	/**
	 * Returns the 'actual' location of the entity.
	 */
	void setOrientationOf(Entity *entity,Orientation orientation) {
		entmap[entity].orientation = orientation;
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

	// prints the current world to screen
	void show();

	int getWidth() const { return width; }
	int getHeight() const { return height; }

	/**
	 * Returns true iff the position is a valid coordinate in this world.
	 */
	bool valid(Vector2di newPos) {
		return (newPos.x >= 0 && newPos.x < width &&
				newPos.y >= 0 && newPos.y < height);
	}

private:
	void printline(const char *string, int numtimes ) const;

	int width;
	int height;
	MapElement map[][];

	map<Entity *, Static> entmap;
};



#endif //MAP_H
