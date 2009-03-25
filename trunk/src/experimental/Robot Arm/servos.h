int servos_init(char serialPort[]);
void servos_close(int port);

void servos_dropLintel(int port, int servoNum);
void servos_resetLintel(int port, int servoNum);

int servos_setPos(int port, char servoNum, int inAngle);
int servos_setMax(int port, int servoNum, int inNum);
int servos_setMin(int port, int servoNum, int inNum);

char *servos_intToStr(int inNum, int numChars);


