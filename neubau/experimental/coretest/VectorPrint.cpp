#include <iostream>

#include "core.h"
#include "control.h"

using namespace std;


bool closeEnough(Static *s, Vector2df *target);
void updateState(Kinematic *state, SteeringOutput *output, float dt);

int main()
{
	// Let us trace the movements of a Kinematic point towards 0,0.
	// Let us start at 9,9, with a strong acceleration downwards.

	Kinematic *state = new Kinematic(Vector2df(9,9), Vector2df(0,-2) ); // the current robot state.
	Vector2df *target = new Vector2df(0,0);

	// seek behaviour to the target
	Seek behaviour(state, target);
	behaviour.maxAcceleration = 0.1; // give this thing some acceleration

	SteeringOutput *output = new SteeringOutput();

	while ( !closeEnough(state, target) ) {
		behaviour.getSteering(output);
		updateState(state, output, 0.1);
		cout << "The position is: " << state->position << endl;
	} // complete!!

	delete target;
	delete state;

	return 0;
}

/**
 * Returns true iff the static s is considered 'close enough'.
 */
bool closeEnough(Static *s, Vector2df *target){
	return (s->position - *target).magnitude() < 0.2;
}

/**
 * Updates the state of the object... should implement beeman here.
 */
void updateState(Kinematic *state, SteeringOutput *output, float dt) {
	// suppose the unit of time was really tiny...
	// the steering output

	state->position += state->velocity*dt; // change of position
	state->velocity += output->linear; // the linear output.

}
