#include <GL/glut.h>
#include "robotArm.h"
#include "servos.h"
#include <stdlib.h>
#include <iostream>
#include <unistd.h>

using namespace std;

#define SCREENWIDTH 900
#define SCREENHEIGHT 600

robotArm theArm;
float offsetX = SCREENWIDTH/2, offsetY = SCREENHEIGHT/4;
int port;
float deltaAngle = 0.0f;



void display() 
{
	//Clear display
	glColor3f(0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	//Plot lines
	glBegin(GL_LINE_STRIP);
	glVertex2f(theArm.position[BASE].x + offsetX, theArm.position[BASE].y + offsetY);
	glVertex2f(theArm.position[ELBOW].x + offsetX, theArm.position[ELBOW].y + offsetY);
	glVertex2f(theArm.position[HAND].x + offsetX, theArm.position[HAND].y + offsetY);
	glEnd();
	//Switch buffers
	glutSwapBuffers();
}

void onMouseClick(int x, int y) 
{
	float desiredX, desiredY;
	//Convert coordinates
	desiredX = x-offsetX;
	desiredY = SCREENHEIGHT-y-offsetY;
	//Update robot arm object
	theArm.setPosition(desiredX, desiredY);
	//Sent data to robot arm
	servos_setPos(port,1, theArm.angle[SHOULDER]);
	servos_setPos(port,0, theArm.angle[ELBOW]);
	//Refresh display
	display();
}

void keyboardDownFunc (int key, int x, int y)
{
	cout << "Key down!" << endl;
	switch(key) {
		case GLUT_KEY_LEFT:
			cout << "LEFT" << endl;
			deltaAngle = -1;
			break;
		case GLUT_KEY_RIGHT:
			deltaAngle = 1;
			break;
		case 27: //escape key
			exit(0);
			break;
	}
}

void keyboardUpFunc (int key, int x, int y)
{
	cout << "Key up!" << endl;
	switch(key) {
		case GLUT_KEY_LEFT:
		case GLUT_KEY_RIGHT:
			deltaAngle = 0;
			break;
	}
}

void idleFunc()
{
	theArm.angle[BASE] += deltaAngle;

	if(theArm.angle[BASE] < 0)
		theArm.angle[BASE] = 0;
	if (theArm.angle[BASE] > 180) 
		theArm.angle[BASE] = 180;

	servos_setPos(port,2, theArm.angle[BASE]);;
	usleep(10000);
}



int main(int argc, char **argv) 
{
	//Set up GLUT and create a window
	glutInit(&argc, argv);
	glutInitWindowSize(SCREENWIDTH,SCREENHEIGHT);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("Robot Arm Controller");
	glClearColor(0.0, 0.0, 0.0, 1.0);
	gluOrtho2D(0, SCREENWIDTH, 0,SCREENHEIGHT);
	glutDisplayFunc(display);
	glutMotionFunc(onMouseClick);
	glutSpecialFunc(keyboardDownFunc);
	glutSpecialUpFunc(keyboardUpFunc);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glutIdleFunc(idleFunc);


	//Set up servos
	port = servos_init("/dev/ttyUSB0");

	glutMainLoop(); 

	glutSetKeyRepeat(GLUT_KEY_REPEAT_DEFAULT);

	return 0;
}
