#pragma once
#include "Common.h"


class Board{
private:

public:
	Point *realSize;
	int bpp;
	SDL_Surface *screen;
	SDL_Surface *pic;
	void handle_input(SDL_Event *event, bool *quit);
	void createImage();
	Board(int bpp = 32);
	~Board();
};