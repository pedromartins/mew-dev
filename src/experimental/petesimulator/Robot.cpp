#include "Robot.h"

Robot::Robot(){
	realSize = new Point(75,75);
	pos = new Point(500,500);
	xVel=yVel=0;
	pic = load_image( "robot.png" );
	//need to initialise the rest of em.
}

Robot::~Robot(){

}

void Robot::handle_input(SDL_Event *event){ 
	int height = realSize->sdl_y();
	int width = realSize->sdl_x();
	//If a key was pressed
    if( event->type == SDL_KEYDOWN )
    {
        //Adjust the velocity
        switch( event->key.keysym.sym )
        {
            case SDLK_UP: yVel -= height / 2; break;
            case SDLK_DOWN: yVel += height / 2; break;
            case SDLK_LEFT: xVel -= width / 2; break;
            case SDLK_RIGHT: xVel += width / 2; break;
        }
    }
    //If a key was released
    else if( event->type == SDL_KEYUP )
    {
        //Adjust the velocity
        switch( event->key.keysym.sym )
        {
            case SDLK_UP: yVel += height / 2; break;
            case SDLK_DOWN: yVel -= height / 2; break;
            case SDLK_LEFT: xVel += width/ 2; break;
            case SDLK_RIGHT: xVel -= width / 2; break;
        }
    }
}

void Robot::move(Board *field)
{
	int xPos = pos->sdl_x();
	int yPos = pos->sdl_y();
	int height = realSize->sdl_y();
	int width = realSize->sdl_x();
    //Move the dot left or right
    //xPos += xVel;
	pos->move(xVel,0);

    //If the dot went too far to the left or right
    if( ( xPos < 0 ) || ( xPos + width > field->realSize->sdl_x() ) )
    {
        //move back
       pos->move(-xVel + 1,0);
    }

    //Move the dot up or down
    //yPos += yVel;
	pos->move(0,yVel);

    //If the dot went too far up or down
	if( ( yPos < 0 ) || ( yPos + height > field->realSize->sdl_y()) )
    {
        //move back
        pos->move(0,-yVel + 1);
    }
}

void Robot::rotate(double angle){
	direction = abs((abs(angle + direction) <= 360)?angle + direction: angle + direction - 360);
	//update points & pic round centre of rotation
}
