/*
 * model.cpp
 *
 *  Created on: 16-Feb-2009
 *      Author: Hok Shun Poon
 */


#include "include/model.h"


GridModel::GridModel(int width, int height)
: width(width), height(height){
	map = new MapElement[width][height];
}

GridModel::~GridModel(){
	delete map;
}




/**
 * findPath()
 *
 * Finds a path from A to B.
 */
Vector2diList* GridModel::findPath(Vector2di start, Vector2di end) {
	Vector2diList path;

	// Our sample problem defines the world as a 2d array representing a terrain
	// Each element contains an integer from 0 to 5 which indicates the cost
	// of travel across the terrain. Zero means the least possible difficulty
	// in travelling (think ice rink if you can skate) whilst 5 represents the
	// most difficult. 9 indicates that we cannot pass.

	// Create an instance of the search class...

	AStarSearch<GridSquareNode> astarsearch;

	unsigned int SearchCount = 0;

	const unsigned int NumSearches = 1;

	while(SearchCount < NumSearches)
	{
		// Create a start state
		GridSquareNode nodeStart;
		nodeStart.x = start.x;
		nodeStart.y = start.y;

		// Define the goal state
		GridSquareNode nodeEnd;
		nodeEnd.x = end.x;
		nodeEnd.y = end.y;

		// Set Start and goal states

		astarsearch.SetStartAndGoalStates( nodeStart, nodeEnd );

		unsigned int SearchState;
		unsigned int SearchSteps = 0;

		do {
			SearchState = astarsearch.SearchStep();
			SearchSteps++;

#if DEBUG_LISTS

			cout << "Steps:" << SearchSteps << "\n";

			int len = 0;

			cout << "Open:\n";
			GridSquareNode *p = astarsearch.GetOpenListStart();
			while( p )
			{
				len++;
#if !DEBUG_LIST_LENGTHS_ONLY
				((GridSquareNode *)p)->PrintNodeInfo();
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
		while( SearchState == AStarSearch<GridSquareNode>::SEARCH_STATE_SEARCHING );

		Vector2di postemp;

		if( SearchState == AStarSearch<GridSquareNode>::SEARCH_STATE_SUCCEEDED )
		{
			cout << "Search found goal state\n";
			GridSquareNode *node = astarsearch.GetSolutionStart();

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
		else if( SearchState == AStarSearch<GridSquareNode>::SEARCH_STATE_FAILED )
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



/**
 * Prints a layout of the map in ASCII, so that you can see what's going on.
 */
void GridModel::visualize(Vector2diList path) {
	Vector2di robotVector2di = getVector2di();

	Vector2di Vector2dicounter;
	MapElement me;
	string content; // what....

	for(Vector2dicounter.y = 0; Vector2dicounter.y < 15; Vector2dicounter.y++) {
		//rows
		printf("%.2d:", Vector2dicounter.y);

		for(Vector2dicounter.x = 0; Vector2dicounter.x < 15; Vector2dicounter.x++) {
			//cols
			//get map
			content = "";
			if(robotVector2di.x == Vector2dicounter.x && robotVector2di.y == Vector2dicounter.y)
			{
				content = "R";
			}
			else
			{
				me = getElementAt(Vector2dicounter);
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
			if(InPath(Vector2dicounter, path))
			{
				content += "*";
			}
			printf("%*s", 2, content.c_str());

			cout << "]";
		}
		cout << endl;
	}
}


float GridModel::GridSquareNode::getCost( AStarNode &successor ) {
	// TODO
}

float GridModel::GridSquareNode::heuristic( AStartNode &nodeGoal ) {
	// TODO
}

bool GridModel::GridSquareNode::isGoal( AStarNode &nodeGoal ){
	// TODO
}

bool GridModel::GridSquareNode::equals( AStarNode &rhs ){
	// TODO
}

bool GridModel::GridSquareNode::getSuccessors( AStarSearch<IAStarNode> *astarsearch, AStarNode *parent_node ){
	// TODO
}

