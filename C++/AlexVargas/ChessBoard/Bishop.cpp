#include "Piece.h"
#include "Bishop.h"
#include <cmath>

namespace Chess {

bool Bishop::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
//
  int columnMovement = abs(start.first - end.first), rowMovement = abs(start.second - end.second);

  if ( (columnMovement == rowMovement) && ((columnMovement != 0) && (rowMovement != 0)) ) {
    return true;
  } else {
    return false;
  }

}

}

