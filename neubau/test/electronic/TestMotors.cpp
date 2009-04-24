#include <electronic/arduino.cpp>
#include <iostream>
#include <unistd.h>
#include <GL/glut.h>

char leftMotorSpeed=0, rightMotorSpeed=0;
ArduinoManager arduinos;	

void renderScene(void)
{
	glFlush();
}
void keyboardUpCallBack (int key, int x, int y) 
{
	switch (key) 
	{
		case GLUT_KEY_UP:
			rightMotorSpeed -= 100;
			leftMotorSpeed -= 100;
			break;
		case GLUT_KEY_DOWN:
			rightMotorSpeed += 100;
			leftMotorSpeed += 100;
			break;
		case GLUT_KEY_RIGHT:
			rightMotorSpeed += 50;
			leftMotorSpeed -= 50;
			break;
		case GLUT_KEY_LEFT:
			rightMotorSpeed -= 50;
			leftMotorSpeed += 50;
			break;
	}
	
	if(leftMotorSpeed > 0) {
		arduinos.setMotorPWM(0,leftMotorSpeed);	
		arduinos.setMotorDir(0,0);
	} else {
		arduinos.setMotorPWM(0,(-1)*leftMotorSpeed);
		arduinos.setMotorDir(0,1);
	}
	if(rightMotorSpeed > 0) {
		arduinos.setMotorPWM(1,rightMotorSpeed);	
		arduinos.setMotorDir(1,0);
	} else {
		arduinos.setMotorPWM(1,(-1)*rightMotorSpeed);
		arduinos.setMotorDir(1,1);
	}
}

void keyboardCallBack(int key, int x, int y) 
{
	switch (key) 
	{
		case GLUT_KEY_UP:
			rightMotorSpeed += 100;
			leftMotorSpeed += 100;
			break;
		case GLUT_KEY_DOWN:
			rightMotorSpeed -= 100;
			leftMotorSpeed -= 100;
			break;
		case GLUT_KEY_RIGHT:
			rightMotorSpeed -= 50;
			leftMotorSpeed += 50;
			break;
		case GLUT_KEY_LEFT:
			rightMotorSpeed += 50;
			leftMotorSpeed -= 50;
			break;
		case GLUT_KEY_END:
			rightMotorSpeed = 0;
			leftMotorSpeed = 0;
			break;
	}
	if(leftMotorSpeed > 0) {
		arduinos.setMotorPWM(0,leftMotorSpeed);	
		arduinos.setMotorDir(0,0);
	} else {
		arduinos.setMotorPWM(0,(-1)*leftMotorSpeed);
		arduinos.setMotorDir(0,1);
	}
	if(rightMotorSpeed > 0) {
		arduinos.setMotorPWM(1,rightMotorSpeed);	
		arduinos.setMotorDir(1,0);
	} else {
		arduinos.setMotorPWM(1,(-1)*rightMotorSpeed);
		arduinos.setMotorDir(1,1);
	}
	
}
	
int main (int argc, char **argv) 
{
	arduinos.open(MOTORS);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("Robot Control");
	
	glutIgnoreKeyRepeat(true);

	glutDisplayFunc(renderScene);
	glutSpecialFunc(keyboardCallBack);
	glutSpecialUpFunc(keyboardUpCallBack);
	glutMainLoop();
	
	/*arduinos.open(MOTORS);

	
	arduinos.setMotorPWM(0,100);
	arduinos.setMotorPWM(1,100);

	usleep(1000000);
	
	arduinos.setMotorPWM(0,0);
	arduinos.setMotorPWM(1,0);*/

	return 0;
}


