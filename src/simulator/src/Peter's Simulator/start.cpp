/*This source code copyrighted by Lazy Foo' Productions (2004-2009) and may not
be redestributed without written permission.*/

//The headers


#include "Robot.h"
#include "Common.h"
#include "Timer.h"


Board *field;
Robot *rob;

const int FRAMES_PER_SECOND = 2000;

bool init(){

	//Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
	//FIX Warning
    field = new Board();

	rob = new Robot();
	apply_surface( rob->pos->sdl_x(), rob->pos->sdl_y(), rob->pic, field->screen );
	SDL_Flip( field->screen );
    //If everything initialized fine
    return true;
}

void clean_up(){
	delete field;
	//delete Robot;
	//Quit SDL
    SDL_Quit();
}

int main( int argc, char* args[] ) {
	init();
	//The frame rate regulator
	Timer fps;
	bool quit = false;
	

	while(quit == false){
		//The frame rate regulator
		Timer fps;
		
		//The event structure
		SDL_Event event;



		//While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            //Handle events for the robot
            rob->handle_input(&event);
			//Handle events for the board
			field->handle_input(&event, &quit);
        }

		rob->move(field);
		apply_surface( 0, 0, field->pic, field->screen );
		apply_surface( rob->pos->sdl_x(),rob->pos->sdl_y(), rob->pic, field->screen );

		//Update the screen
        if( SDL_Flip( field->screen ) == -1 )
        {
            return 1;
        }

		//Cap the frame rate
		if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
		{
			SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
		}
	}

	
	clean_up();
	return 0;
}