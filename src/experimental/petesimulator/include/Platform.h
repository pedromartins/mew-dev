#pragma once
#include "Common.h"


//Base class for the platforms
class Platform
{
private:
	SDL_Surface *pic;
public:
    Point *realSize;
	Platform(void);
	virtual ~Platform(void);
};
