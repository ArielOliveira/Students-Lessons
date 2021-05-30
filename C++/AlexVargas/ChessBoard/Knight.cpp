#include "Piece.h"
#include "Knight.h"
#include <cmath>

namespace Chess {

bool Knight::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {

  int columnMovement = abs(start.first - end.first), rowMovement = abs(start.second - end.second);

  if ((columnMovement == 1 && rowMovement == 2) || (columnMovement == 2 && rowMovement == 1)) {
     return true;
  } else {
    return false;
  }

}

}