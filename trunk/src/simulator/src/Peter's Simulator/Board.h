#ifndef  _MEW_SIMULATOR_BOARD_H
#define  _MEW_SIMULATOR_BOARD_H

#include "Common.h"


/**
 * Board
 *
 * A class that draws and manages the playing field graphics.
 *
 *
 * Sorry!! I just had to change a lot of things!! Hope you don't mind, Peter! - Hok
 */
class Board{
public:
	Board(int bpp = 32);
	virtual ~Board();

	// Handles SDL input
	void handle_input(SDL_Event *event, bool *quit);
	void createBackground();

private:
	/**
	 * Size of the board, in millimetres.
	 */
	Vector2di *realSize;

	SDL_Surface *screen;
	SDL_Surface *pic;

	int bpp;
};


#endif
