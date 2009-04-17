
std::list<Movement> pointsToMovements(std::list<Vector2d<int>> path, Orientation o) {
    std::list<Movement> ms;
    for(std::list<Vector2D<int>>::iterator i = path.begin(); i != path.end(); i++) {
	if(i+1) {
	  Vector2d<int> diff = (*i).distance(*(i+1));
	  if(diff == Vector2d<int>(1,0)) {
	    ms.merge(turn(o, EAST));
	  } else if(diff == Vector2d<int>(-1,0)) {
	    ms.merge(turn(o, WEST));
	  } else if(diff == Vector2d<int>(0,1)) {
	    ms.merge(turn(o, NORTH));
	  } else if(diff == Vector2d<int>(0,-1)) {
	    ms.merge(turn(o, SOUTH));
	  }
	  ms.push_back(FWD);
	}
      }
}

std::list<Movement> turn(Orientation orig, Orientation dest) {

    std::list<Movement> ms;
    
    switch(orig){
    case NORTH:
      switch(dest){
      case NORTH:
	break;
      case EAST:
	ms.push_back(TURN_RIGHT);
	break;
      case WEST:
	ms.push_back(TURN_LEFT);
	break;
      case SOUTH:
	ms.push_back(TURN_LEFT);
	ms.push_back(TURN_LEFT);
	break;
      }
      break;
    case EAST:
      switch(dest){
      case NORTH:
	ms.push_back(TURN_LEFT);
	break;
      case EAST:
	break;
      case WEST:
	ms.push_back(TURN_RIGHT);
	ms.push_back(TURN_RIGHT);
	break;
      case SOUTH:
	ms.push_back(TURN_RIGHT);
	break;
      }
      break;
    case WEST:
      switch(dest){
      case NORTH:
	ms.push_back(TURN_RIGHT);
	break;
      case EAST:
	ms.push_back(TURN_LEFT);
	ms.push_back(TURN_LEFT);
	break;
      case WEST:
	break;
      case SOUTH:
	ms.push_back(TURN_LEFT);
	break;
      }
      break;
    case SOUTH:
      switch(dest){
      case NORTH:
	ms.push_back(TURN_LEFT);
	ms.push_back(TURN_LEFT);
	break;
      case EAST:
	ms.push_back(TURN_LEFT);
	break;
      case WEST
	ms.push_back(TURN_RIGHT);
	break;
      case SOUTH:
	break;
      }
      break;
    default:
      // ERROR
    }
    return ms;
}
