#include "Rook.h"

namespace Chess {
   bool Rook::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
		 //checking that the piece is moving vertically or horizontally
      if (start.first == end.first || start.second == end.second)
        return true;
      
      return false;
    }
}

