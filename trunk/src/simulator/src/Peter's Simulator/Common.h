#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include "Point.h"

//change to enum
#define GREEN 0
#define RED 0

#define SCALING_FACTOR 0.4




SDL_Surface *load_image( std::string filename );

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL);

