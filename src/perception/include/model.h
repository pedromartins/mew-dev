/*
 * model.h
 *
 * Holds some basic interfacing classes with which more complicated models can be drawn.
 *
 *  Created on: 16-Feb-2009
 *      Author: Hok Shun Poon
 */

#ifndef MODEL_H_
#define MODEL_H_

#include <core.h>
#include <vector>
#include <boost/shared_ptr.hpp>

using namespace std;
using namespace boost;
using namespace mew;
using namespace core;

/**
 * MapElement
 *
 * A simple enumeration for a SimpleGridModel.
 */
enum MapElement {
	EMPTY, PIECE, DROPZONE, FORBIDDEN
};

// Offsets to squares for each direction.
Vector2di frontDir[4] = {
	Vector2di(0,1), // north
	Vector2di(-1,0),// east
	Vector2di(0,-1),// south
	Vector2di(1,0) // west
};

// A list of Vectors2dis
typedef boost::shared_ptr<std::list<Vector2di>> Vector2diList;

/**
 * Orientation
 *
 * A simple enumeratoin for a SimpleGridModel
 */
enum Orientation {
	NORTH, WEST, SOUTH, EAST
};


/**
 * RectangularRoomModel
 *
 * The simplest model that can be conceived:
 * The robot is placed within a rectangular room.
 *
 */
class RectangularRoomModel {
public:
	RectangularRoomModel(float widthmm, float breadthmm)
	: width(widthmm), breadth(breadthmm) {}

private:
	float width;
	float breadth;
};


/**
 * Model
 *
 * A model is the representation of the world with respect to the
 * currently running program.
 *
 * Entities are REGISTERED with the model, and this registration process
 * initiates a relationship between the model and entity in this way:
 *
 *   ALL registered entities may modify the model in any way it likes.
 *
 * The model could well be static, or dynamic. Static models require no
 * updating over time, whereas more dynamic model do require updating
 * over time, because entities don't generally update the model.
 */


/**
 * GridModel
 *
 * In a simple grid model, the robot and anything IN the grid is
 * simply represented by some enum value in a 2D array.
 *
 * NOTE: this is a wrapper around the old simulator model.
 */
class GridModel {

	/**
	 * GridSquareNode
	 *
	 * An A* wrapper node for a GridModel
	 */
	class GridSquareNode : public AStarNode {
	public:
		GridSquareNode() : pos() {}
		GridSquareNode( int px, int py ): pos(px,py) {}

		float getCost( IAStarNode &successor );
		float heuristic( IAStartNode &nodeGoal );
		bool isGoal( IAStarNode &nodeGoal );
		inline bool equals( IAStarNode &rhs );
		bool getSuccessors( AStarSearch<IAStarNode> *astarsearch, IAStarNode *parent_node );

		Vector2di pos;
	};


	// START of Grid model code.

	GridModel( int width, int height );

	virtual ~GridModel();

	/**
	 * Returns the map element at a particular position.
	 * @param pos the position
	 */
	MapElement getElementAt(Vector2di pos){
		return map[pos.x][pos.y];
	}
	MapElement getElementAt(int posx, int posy){
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
	void removePiece(int posx, int posy) {
		map[posx][posy] = EMPTY;
	}

	/**
	 * Returns the logical square in front of the given coordinate,
	 * and orientation
	 */
	Vector2di inFront(const Vector2di &vec, Orientation orientation) {
		return vec.x + frontDir[orientation];
	}

	/**
	 * Removes all the pieces.
	 */
	void clear() {
		for(int i = 0; i<width; ++i){
			for (j = 0; j < height; ++j) {
				map[i][j] = EMPTY;
			}
		}
	}

	void visualize();

private:
	MapElement map[][];
};

















/**
 * GridEntityModel
 *
 * An interface to the most basic of World representation models:
 * A GridEntityModel keeps:
 *
 * A 2d array of a particular size, with cells of type G
 * ... and stores a container of
 * 'Entities'
 */
template <typename C, typename E>
class GridEntityModel {
	GridEntityModel(int cols, int rows){
		map = new G[cols][rows];
	}

	virtual ~GridEntityModel(){}

	virtual C get(int x, int y) const {
		return map[x][y];
	}

	void put(C cell, int x, int y) {
		map[x][y] = cell;
	}


	virtual void registerEnt(boost::shared_ptr<E> entity) {
		// TODO register an entity.
	}
	virtual void removeEnt(boost::shared_ptr<E> entity) {
		// TODO remove entity.
	}

private:
	C map[][];
	// vector<boost::shared_ptr<E>> entities;
};

#endif /* MODEL_H_ */
