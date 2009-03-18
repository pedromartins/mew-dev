////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// STL A* Search implementation
// (C)2001 Justin Heyes-Jones
//
// Finding a path on a simple grid maze
// This shows how to do shortest path finding using A*

//adapted by Michiel to use Pedro's simulator for mew

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "stlastar.h" // See header for copyright and usage information
#include "simulator.h"

#include <list>
#include <string>
#include <iostream>
#include <stdio.h>

#define DEBUG_LISTS 0
#define DEBUG_LIST_LENGTHS_ONLY 0

using namespace std;








/**
 * This generates the successors to the given Node.
 * It uses a helper function called
 * AddSuccessor to give the successors to the AStar class.
 * The A* specific initialisation
 * is done for each node internally, so here you just set the state information that
 * is specific to the application
 */
bool GridSquareNode::GetSuccessors( AStarSearch<GridSquareNode> *astarsearch, GridSquareNode *parent_node )
{

	int parent_x = -1;
	int parent_y = -1;

	if( parent_node )
	{
		parent_x = parent_node->x;
		parent_y = parent_node->y;
	}


	GridSquareNode NewNode;

	// push each possible move except allowing the search to go backwards

	if( (GetMap( x-1, y ) < 9)
			&& !((parent_x == x-1) && (parent_y == y))
	)
	{
		NewNode = GridSquareNode( x-1, y );
		astarsearch->AddSuccessor( NewNode );
	}

	if( (GetMap( x, y-1 ) < 9)
			&& !((parent_x == x) && (parent_y == y-1))
	)
	{
		NewNode = GridSquareNode( x, y-1 );
		astarsearch->AddSuccessor( NewNode );
	}

	if( (GetMap( x+1, y ) < 9)
			&& !((parent_x == x+1) && (parent_y == y))
	)
	{
		NewNode = GridSquareNode( x+1, y );
		astarsearch->AddSuccessor( NewNode );
	}


	if( (GetMap( x, y+1 ) < 9)
			&& !((parent_x == x) && (parent_y == y+1))
	)
	{
		NewNode = GridSquareNode( x, y+1 );
		astarsearch->AddSuccessor( NewNode );
	}

	return true;
}


/**
 *
 */
bool goTo(Vector2df end)
{
	//set start to current location of our robot
	Vector2df start;
	start = getVector2df();

	//this will contain the path from start to goal
	list<Vector2df> path;

	try
	{
		path = findPath(start, end);
	}
	catch(int& int_exception)
	{
		if(int_exception == -1)
		{
			//failed finding path
			cout << "no path";
			return -1;
		}
	}
	catch(exception& e)
	{
		//other exception, shouldn't really happen...
		cout << e.what();
	}

	//print solution.

	list<Vector2df>::iterator i;

	for(i=path.begin(); i != path.end(); ++i)
	{
		PrintVector2df(*i);
	}
	cout << endl;

	VisualiseMap(path);		//show what's going on

	//try moving robot
	cout << endl << "Try moving robot from start to goal (press [ENTER] to start)..." << endl;

	getchar();

	//the orientation gives the relative direction of the next field the robot is facing
	Vector2df orientation[4];	//north = 0, 1=west, 2=south, 3=east (counter clockwise)
	orientation[0].x = 0;
	orientation[0].y = 1;

	orientation[1].x = -1;
	orientation[1].y = 0;

	orientation[2].x = 0;
	orientation[2].y = -1;

	orientation[3].x = 1;
	orientation[3].y = 0;

	Vector2df currentVector2df;
	Vector2df Vector2dfDifference;	//where is the next Vector2df relatvive to the current one?
	int currentOrientation = 0;		//which way do we face now? works similar to above.

	int turnCounter;	//dummy variable.

	for(i=path.begin(); i != path.end(); ++i)
	{
		//figure out where the next field is compared to the current one.
		currentVector2df = getVector2df();
		if((*i).x == currentVector2df.x && (*i).y == currentVector2df.y)
		{
			//do nothing, we're already there
			continue;
		}
		//ok, so which direction do we need to face to get to the next square? compute
		//difference in Vector2dfs
		Vector2dfDifference.x = (*i).x - currentVector2df.x;
		Vector2dfDifference.y = (*i).y - currentVector2df.y;
		if(Vector2dfDifference.x > 1 || Vector2dfDifference.x < -1 || Vector2dfDifference.y > 1 || Vector2dfDifference.y < -1)
		{
			cout << "PANICK";
			break;
		}

		cout << "DIFF: ";
		PrintVector2df(Vector2dfDifference);

		//turn until we face the correct way. todo: optimise to turn left/right
		while(!(orientation[currentOrientation].x == Vector2dfDifference.x && orientation[currentOrientation].y == Vector2dfDifference.y))
		{
			//turn!
			currentOrientation++;
			turn(1);
			if(currentOrientation == 4)
				currentOrientation = 0;
		}
		switch(currentOrientation)
		{
		case 0:
			cout << "facing north, moving!";
			break;
		case 1:
			cout << "facing west, moving!";
			break;
		case 2:
			cout << "facing south, moving!";
			break;
		case 3:
			cout << "facing east, moving!";
			break;
		default:
			cout << "looking confused, moving...";
			break;
		}
		cout << endl;

		//move forward!
		moveForward();
		VisualiseMap(path);
		getchar();

		cout << endl;

	}
}

// Main

int main( int argc, char *argv[] )
{
	cout << "Experimental pathfinder v. 0.1 alpha" << endl;
	cout << "initialising..." << endl;
	loadMap(1);
	restart();	//board & robot.

	Vector2df goal;
	cout << endl << "finished." << endl;
	cout << "Plase enter the target x coordinate: ";
	cin >> goal.x;
	cout << endl << "Please enter the target y coordinate: ";
	cin >> goal.y;

	goTo(goal);

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
