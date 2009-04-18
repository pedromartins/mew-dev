/*
 * virtualworld.cpp
 *
 *  Created on: 04-Mar-2009
 *      Author: fushunpoon
 */

#include "virtualworld.h"

#include <iostream>

using namespace std;

/*
 * STATIC INITIALIZATION
 */
Vector2di VirtualWorld::dOffsets[] = {
		Vector2di(0,-1), // NORTH
		Vector2di(-1,0), // WEST
		Vector2di(0,1), // SOUTH
		Vector2di(1,0)	 // EAST
};


VirtualWorld::VirtualWorld(const int width, const int height)
: width(width), height(height), entmap() {
	arr = new_2DArr<MapElement>(width, height);
	clear();
}

VirtualWorld::~VirtualWorld() {
	delete_2DArr(arr,width);
}

//print a layout of the map in ASCII ART, so that you can see what's going on.
ostream& operator << (ostream& os, const VirtualWorld& world) {
	/// XXX Do we need this?!
	Vector2di pos;
	MapElement me;
	string content;

	// for every row
	for(pos.y = world.height-1; pos.y >= 0; --pos.y) {
		os << right << pos.y << " ";

		// for every column
		for(pos.x = 0; pos.x < world.width; ++pos.x) {
			content = "";
			me = world.getElementAt(pos);
			switch(me)
			{
			case EMPTY:
				// Content can stay empty.
				break;
			case PIECE:
				content += "O";
				break;
			case DROPZONE:
				content += "_";
				break;
			case FORBIDDEN:
				content += "X";
				break;
			default:
				content += "?";
			}

			os << "[";
			os.fill(' '); os.width(2);
			os << right << content;
			os << "]";
		}
		os << endl;
	}

	os << "Registered entities: " << endl;

	/*
	 * Output all the entities.
	 */
	for(EntStatMap::const_iterator i = world.entmap.begin(); i!=world.entmap.end(); ++i ) {
		os << i->first->toString() << "  " << i->second << endl;
	}
}
