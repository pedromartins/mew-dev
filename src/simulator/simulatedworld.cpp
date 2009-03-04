#include <stdio.h>
#include <stdlib.h>

#include "simulatedworld.h"


/*
World::World(int mapNum) {
	for(int i = 0; i != SIZE_X; i++) {
		for(j = 0; j != SIZE_Y; j++) {
			map[i][j] = EMPTY;
		}
	}
	cout << "initMap: Map 0 chosen!" << endl;
	switch(mapNum) {
	case 1:
		printf("initMap: Map 1 chosen!");
		int i, j;
		for(i = 3; i != 6; i++) {
			for(j = 0; j != SIZE_Y - 1 ; j++) {
				map[i][j] = FORBIDDEN;
			}
		}
		putPiece(9,0);
		break;
	default:
		printf("initMap: No such map available!\n");
		exit(0);
	}
}
*/
