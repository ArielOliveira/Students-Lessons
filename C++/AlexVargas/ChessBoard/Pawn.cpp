#include <iostream>
#include <cmath>
#include "Pawn.h"

namespace Chess {

    bool Pawn:: legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
      bool isForward = false;
      bool isColumnMove = false;

      std::pair<char, char> direction = {start.first+end.first, end.first+end.second};
      
      if ((direction.second == 1 && !is_white()) || (direction.second == -1 && is_white()))
        return false;
      //there is a special move for this scenario
      if ((start.second == '2' && is_white()) || (start.second == '7' && !is_white())) {
	//determines whether we are moving within the same column
	if (start.first == end.first) {
	  isColumnMove = true;
	}
	//can move forward 1 or 2 spaces
	if ((abs(end.second - start.second) == 1) || (abs(end.second - start.second) == 2)) {
	  isForward = true;
	}
      }

      //no special moves for any other scenario
      else {
	if (start.first == end.first) {
	  isColumnMove = true;
	}

	if (abs(end.second - start.second) == 1) {
	  isForward = true;
	}
      }
      
      return isForward && isColumnMove;
    }

  bool Pawn::legal_capture_shape(std::pair<char, char> start, std::pair<char, char> end) const {
    std::pair<int, int> direction = {0, 0};  

    direction.first = start.first + end.first;
    direction.second = start.second + end.second;
    if (abs(direction.first) > 1 || abs(direction.second) > 1)
      return false;

    if ((is_white() && direction.second == -1) || (!is_white() && direction.second == 1))
      return false;

    if (direction.first == 0 || direction.second == 0)
      return false;

	  return true;
  }
}
	
	