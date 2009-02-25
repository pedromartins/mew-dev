#pragma once
#include "Common.h"


class Dispensor
{
private:
	SDL_Surface *pic;
public:
	Point *realSize;
	bool color;
	int cylinders;
	Dispensor(bool color, int cylinders = 5);
	~Dispensor(void);
};
