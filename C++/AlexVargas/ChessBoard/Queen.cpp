#include "Queen.h"
#include <cmath>
namespace Chess {
  bool Queen::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
      bool isStraight = false;
      bool isDiagonal = false;

      //checking if the piece is moving vertically or horizontally
      if (start.first == end.first || start.second == end.second)
        isStraight = true;	

      // checking if the piece is moving diagonally
      int distance1 = abs(end.first - start.first);
      int distance2 = abs(end.second - start.second);

      //if the distances are equal, we know we have a diagonal
      if (distance1 == distance2 && distance1 != 0 && distance2 != 0) 
        isDiagonal = true;

	//if the piece moves in a straight line, or a diagonal, then we know that the piece is moving in a legal shape. Otherwise, it is not, and we return false
      return (isStraight || isDiagonal);
  }
}
