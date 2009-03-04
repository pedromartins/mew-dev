#pragma once
#include "Common.h"

class Lintel
{
private:
	SDL_Surface *pic;
public:
	Point *realSize;
	Lintel(void);
	~Lintel(void);
};
