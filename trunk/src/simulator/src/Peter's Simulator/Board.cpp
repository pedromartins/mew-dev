#include "Board.h"

Board::Board(int b){
	realSize = new Point(3000,2100);
	bpp = b;
	screen = SDL_SetVideoMode( realSize->sdl_x(),realSize->sdl_y(),b, SDL_SWSURFACE );
	createBackground();
	apply_surface( 0, 0, pic, screen );
	SDL_Flip( screen );
	SDL_WM_SetCaption( "Robot Simulator ALPHA ALPHA v0.00001", NULL );
}

Board::~Board(){
	SDL_FreeSurface(screen);
	SDL_FreeSurface(pic);
}

void Board::handle_input(SDL_Event *event, bool *quit){
	if( event->type == SDL_QUIT )
            {
                //Quit the program
                *quit = true;
            }
	else if(event->type == SDL_KEYDOWN){
		switch( event->key.keysym.sym )
        {
            case SDLK_ESCAPE: *quit = true; break;
			default: break;
        }
	}
}

void Board::createBackground(){
	//need to make these independent of image size, create objects for dispensors etc..
	SDL_Surface *background = load_image( "BoardResized.png" );
	SDL_Surface *circle = load_image( "MiddleCircleResized.png" );
	SDL_Surface *topsides = load_image("TopSideResized.png");
	SDL_Surface *middle = load_image("TopMiddleResized.png");
	SDL_Surface *greenDisp = load_image("GreenDispensor.png");
	apply_surface( 540, 360, circle, background );
	apply_surface( 240, 0 , topsides, background );
	apply_surface( 720, 0 , topsides, background );
	apply_surface( 480, 0, middle, background);
	apply_surface( 720 + 240 + (int) (0.4 * 289) , 0, greenDisp, background);


	pic = background;
}
