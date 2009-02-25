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
using namespace mew::core;

// Definitions
class MapSearchNode
{
public:
	unsigned int x;	 // the (x,y) positions of the node
	unsigned int y;

	MapSearchNode() { x = y = 0; }
	MapSearchNode( unsigned int px, unsigned int py ) { x=px; y=py; }

	float GoalDistanceEstimate( MapSearchNode &nodeGoal );
	bool IsGoal( MapSearchNode &nodeGoal );
	bool GetSuccessors( AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node );
	float GetCost( MapSearchNode &successor );
	bool IsSameState( MapSearchNode &rhs );

	void PrintNodeInfo();
};

bool MapSearchNode::IsSameState( MapSearchNode &rhs )
{

	// same state in a maze search is simply when (x,y) are the same
	if( (x == rhs.x) &&
			(y == rhs.y) )
	{
		return true;
	}
	else
	{
		return false;
	}

}

void MapSearchNode::PrintNodeInfo()
{
	char str[100];
	sprintf( str, "Node position : (%d,%d)\n", x,y );

	cout << str;
}

// Here's the heuristic function that estimates the distance from a Node
// to the Goal.

float MapSearchNode::GoalDistanceEstimate( MapSearchNode &nodeGoal )
{
	float xd = float( ( (float)x - (float)nodeGoal.x ) );
	float yd = float( ( (float)y - (float)nodeGoal.y) );

	return xd + yd;

}

bool MapSearchNode::IsGoal( MapSearchNode &nodeGoal )
{

	if( (x == nodeGoal.x) &&
			(y == nodeGoal.y) )
	{
		return true;
	}

	return false;
}

// This generates the successors to the given Node. It uses a helper function called
// AddSuccessor to give the successors to the AStar class. The A* specific initialisation
// is done for each node internally, so here you just set the state information that
// is specific to the application
bool MapSearchNode::GetSuccessors( AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node )
{

	int parent_x = -1;
	int parent_y = -1;

	if( parent_node )
	{
		parent_x = parent_node->x;
		parent_y = parent_node->y;
	}


	MapSearchNode NewNode;

	// push each possible move except allowing the search to go backwards

	if( (GetMap( x-1, y ) < 9)
			&& !((parent_x == x-1) && (parent_y == y))
	)
	{
		NewNode = MapSearchNode( x-1, y );
		astarsearch->AddSuccessor( NewNode );
	}

	if( (GetMap( x, y-1 ) < 9)
			&& !((parent_x == x) && (parent_y == y-1))
	)
	{
		NewNode = MapSearchNode( x, y-1 );
		astarsearch->AddSuccessor( NewNode );
	}

	if( (GetMap( x+1, y ) < 9)
			&& !((parent_x == x+1) && (parent_y == y))
	)
	{
		NewNode = MapSearchNode( x+1, y );
		astarsearch->AddSuccessor( NewNode );
	}


	if( (GetMap( x, y+1 ) < 9)
			&& !((parent_x == x) && (parent_y == y+1))
	)
	{
		NewNode = MapSearchNode( x, y+1 );
		astarsearch->AddSuccessor( NewNode );
	}

	return true;
}

// given this node, what does it cost to move to successor. In the case
// of our map_ the answer is the map_ terrain value at this node since that is
// conceptually where we're moving

float MapSearchNode::GetCost( MapSearchNode &successor )
{
	return (float) GetMap( x, y );
}

//get the path from A to B
list<Vector2df> GetPath(Vector2df start, Vector2df end)
{
	list<Vector2df> path;

	// Our sample problem defines the world as a 2d array representing a terrain
	// Each element contains an integer from 0 to 5 which indicates the cost
	// of travel across the terrain. Zero means the least possible difficulty
	// in travelling (think ice rink if you can skate) whilst 5 represents the
	// most difficult. 9 indicates that we cannot pass.

	// Create an instance of the search class...

	AStarSearch<MapSearchNode> astarsearch;

	unsigned int SearchCount = 0;

	const unsigned int NumSearches = 1;

	while(SearchCount < NumSearches)
	{
		// Create a start state
		MapSearchNode nodeStart;
		nodeStart.x = start.x;
		nodeStart.y = start.y;

		// Define the goal state
		MapSearchNode nodeEnd;
		nodeEnd.x = end.x;
		nodeEnd.y = end.y;

		// Set Start and goal states

		astarsearch.SetStartAndGoalStates( nodeStart, nodeEnd );

		unsigned int SearchState;
		unsigned int SearchSteps = 0;

		do
		{
			SearchState = astarsearch.SearchStep();

			SearchSteps++;

#if DEBUG_LISTS

			cout << "Steps:" << SearchSteps << "\n";

			int len = 0;

			cout << "Open:\n";
			MapSearchNode *p = astarsearch.GetOpenListStart();
			while( p )
			{
				len++;
#if !DEBUG_LIST_LENGTHS_ONLY
				((MapSearchNode *)p)->PrintNodeInfo();
#endif
				p = astarsearch.GetOpenListNext();

			}

			cout << "Open list has " << len << " nodes\n";

			len = 0;

			cout << "Closed:\n";
			p = astarsearch.GetClosedListStart();
			while( p )
			{
				len++;
#if !DEBUG_LIST_LENGTHS_ONLY
				p->PrintNodeInfo();
#endif
				p = astarsearch.GetClosedListNext();
			}

			cout << "Closed list has " << len << " nodes\n";
#endif

		}
		while( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SEARCHING );

		Vector2df postemp;

		if( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SUCCEEDED )
		{
			cout << "Search found goal state\n";

			MapSearchNode *node = astarsearch.GetSolutionStart();

#if DISPLAY_SOLUTION
			cout << "Displaying solution\n";
#endif
			int steps = 0;

			node->PrintNodeInfo();
			//add the node to our path
			postemp.x = node->x;
			postemp.y = node->y;

			path.push_back(postemp);
			for( ;; )
			{
				node = astarsearch.GetSolutionNext();

				if( !node )
				{
					break;
				}
				node->PrintNodeInfo();
				//add node to path
				postemp.x = node->x;
				postemp.y = node->y;

				path.push_back(postemp);

				steps ++;

			};

			cout << "Solution steps " << steps << endl;

			// Once you're done with the solution you can free the nodes up
			astarsearch.FreeSolutionNodes();


		}
		else if( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_FAILED )
		{
			cout << "Search terminated. Did not find goal state\n";
			throw -1;
		}

		// Display the number of loops the search went through
		cout << "SearchSteps : " << SearchSteps << "\n";

		SearchCount ++;

		astarsearch.EnsureMemoryFreed();
	}

	return path;
}



//for debugging..
void PrintVector2df(Vector2df pos)
{
	cout << "Pos(" << pos.x << ", " << pos.y << ")" << endl;
}

bool InPath(Vector2df pos, list<Vector2df> path)
{
	list<Vector2df>::iterator i;
	for(i=path.begin(); i != path.end(); ++i)
	{
		if(pos.x == (*i).x && pos.y == (*i).y)
		{
			return true;
		}
	}
	return false;
}

//print a layout of the map in ASCII ART, so that you can see what's going on.

void VisualiseMap(list<Vector2df> path) {
	Vector2df robotVector2df = getVector2df();

	Vector2df Vector2dfcounter;
	MapElement me;
	string content;

	for(Vector2dfcounter.y = 0; Vector2dfcounter.y < 15; Vector2dfcounter.y++) {
		//rows
		printf("%.2d:", Vector2dfcounter.y);

		for(Vector2dfcounter.x = 0; Vector2dfcounter.x < 15; Vector2dfcounter.x++) {
			//cols
			//get map
			content = "";
			if(robotVector2df.x == Vector2dfcounter.x && robotVector2df.y == Vector2dfcounter.y)
			{
				content = "R";
			}
			else
			{
				me = getElementAt(Vector2dfcounter);
				switch(me)
				{
				case EMPTY:
					//
					break;
				case PIECE:
					content += "O";
					break;
				case DROPZONE:
					content += "_";
					break;
				case FORBIDDEN:
					content += "X";
					break;
				default:
					content += "?";
				}
			}

			cout << "[";

			//include path
			if(InPath(Vector2dfcounter, path))
			{
				content += "*";
			}
			printf("%*s", 2, content.c_str());

			cout << "]";
		}
		cout << endl;
	}
}

bool goTo(Vector2df end)
{
	//set start to current location of our robot
	Vector2df start;
	start = getVector2df();

	//this will contain the path from start to goal
	list<Vector2df> path;

	try
	{
		path = GetPath(start, end);
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
