#define BASE 0
#define SHOULDER 1
#define ELBOW 2
#define HAND 1

struct coordinate {
	float x,y,z;
};

class robotArm {
	public:
	float angle[3]; //Base, shoulder and elbow angles in degrees
	coordinate position[3]; //Base elbow and hand positions.
	int length[2]; //0 upper arm, 1 forearm

	robotArm();
	void changeAngle(int angleNum, int inAngle);
	void setPosition(float x, float y);
};
