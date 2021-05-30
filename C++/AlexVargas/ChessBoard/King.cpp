#include <cmath>
#include "King.h"

namespace Chess {

  bool King::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
    bool isHorizontal = false;
    bool isVertical = false;
    bool isDiagonal = false;

    int horizontalLength = abs(start.first - end.first);
    int verticalLength = abs(start.second - end.second);

    //check for horizontal move of 1 space
    if (horizontalLength == 1 && verticalLength == 0) {
      isHorizontal = true;
    }

    //check for verical move of 1 space
    if (verticalLength == 1 && horizontalLength == 0) {
	isVertical = true;
    }

    //check for diagonal move of 1 space
    if (horizontalLength == 1 && verticalLength == 1) {
      isDiagonal = true;
    }

      return isHorizontal || isVertical || isDiagonal;
    }
}
