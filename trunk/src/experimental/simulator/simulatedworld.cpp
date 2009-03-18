#include "include/simulatedworld.h"

#include <iostream>

using namespace std;


SimulatedWorld::SimulatedWorld(int map)
{
	map = new MapElement[DEFAULT_SIZE][DEFAULT_SIZE];

	clear();

	switch(mapNum) {
	case 0:
		cout << "World: Blank world created. " << endl;
		break;
	case 1:
		cout << "World: Preset world 1 created. " << endl;

		for(int i = 3; i != 6; i++) {
			for(int j = 0; j != SIZE_Y - 1 ; j++) {
				map[i][j] = FORBIDDEN;
			}
		}

		putPiece(9,0);
		break;
	default:
		cout << "ERROR: No such world available!" << endl;
		exit(0);
	}
}

SimulatedWorld::SimulatedWorld(int width, int height){
	map = new MapElement[width][height];

	clear();
}

void SimulatedWorld::show() {

	cout << printline("*", width);
	for( int j = 0; j<height; ++j ) {
		cout << "*";
		for (int i = 0; i<width; ++i){
			switch ( map[j][i] ) {
			case EMPTY:
				cout << " ";
			case PIECE:
				cout << "O";
			case DROPZONE:
				cout << "x";
			case FORBIDDEN:
				cout << "F";
			}
		}
		cout << "*" << endl;
	}
	cout << printline("*", width) << endl;
}

void SimulatedWorld::printline(const char *string, int numtimes ) const {
	for(int i =0; i<width; ++i){
		cout<<"*" ;
	}
}
