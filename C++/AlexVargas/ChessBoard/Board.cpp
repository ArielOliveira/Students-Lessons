#include <iostream>
#include <utility>
#include <map>
#include "Terminal.h"
#include "Board.h"
#include "Game.h"
#include "CreatePiece.h"

using std::cout;
using std::endl;

namespace Chess
{

  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  Board::Board(){}

  Board::Board(const Board& board) {
      for (std::map<std::pair<char, char>, Piece*>::const_iterator it = board.occ.begin(); it != board.occ.end(); it++) {
        add_piece(it->first, it->second->to_ascii());
      }
  }

  const Piece* Board::operator()(std::pair<char, char> position) const {
		//iterating through the occ map
    std::map<std::pair<char, char>, Piece*>::const_iterator it = occ.find(position);
	//if we don't reach the end of the map, that means we found the piece
    if (it != occ.end())
      return it->second;
    
	//otherwise, no piece exists at that position so we return NULL
    return NULL;
  }
  bool Board::add_piece(std::pair<char, char> position, char piece_designator) {
    Piece* newPiece = create_piece(piece_designator);
  //if the piece_designator is not a valid piece 
    if (!newPiece) {
      std::cout << "invalid piece designator" << std::endl;
      return false;
    }
  // if the position is not in bounds
    if (!isInBounds(position)) {
      std::cout << "piece is out of bounds" << std::endl;
      return false;
    }
  //if this location is occupied
    if (this->operator()(position)) {
      std::cout << "tried to overlap a piece" << std::endl;
      return false;
    }
  //if the call passes all of these tests, we place the created piece in the specified position
    occ[position] = newPiece;
    
    return true;
  }

  bool Board::move_piece(std::pair<char, char> start, std::pair<char, char> end) {
		//checking that the start and end positions are in bounds
    if (!isInBounds(start) || !isInBounds(end))
      return false;

	//if a piece exists at the end position, then we return false (because we canoot move a piece there =)
    if (this->operator()(end))
      return false;

	//accessing a pointer to the piece we are moving
    std::map<std::pair<char, char>, Piece*>::iterator it = occ.find(start);

    
//if no piece exists, then we return false
    if (it == occ.end())
      return false;

	// we erase the key that points to the piece in the start position 
    occ.erase(start);

//we set the piece position to be at the end position
    occ[end] = it->second;

    return true;
  }

  bool Board::switch_pieces(std::pair<char, char> start, std::pair<char, char> end) {
      if (!isInBounds(start) || !isInBounds(end))
        return false;

      if (!this->operator()(start) || !this->operator()(end))
        return false;

      Piece* atStart = occ[start];
      Piece* atEnd = occ[end];

      occ[start] = atEnd;
      occ[end] = atStart;

      return true;
  }

  bool Board::remove_piece(std::pair<char, char> position) {
	  //if the position from which we are trying to remove a piece is not in bounds
    if (!isInBounds(position))
      return false;
	  
    //retrieves a piece at the position we are trying to remove from
    std::map<std::pair<char, char>, Piece*>::iterator it = occ.find(position);

//if no piece exists, (meaning piece = NULL) then we return false
    if (it == occ.end())
      return false;

  //map->erase doesn't call the destructor if it is a pointer, deleting the piece but not the object
    delete it->second;

    occ.erase(position);

    return true;
  }

  //checks if given position is inside the chess board
  bool Board::isInBounds(std::pair<char, char> position) {
    if (position.first < 'A' || position.first > 'H' || position.second < '1' || position.second > '8')
      return false;
    else 
      return true;
  }

  void Board::clear() { 
    for (std::map<std::pair<char, char>, Piece*>::iterator it = occ.begin(); it != occ.end(); it++) {
        delete it->second;
    }

    occ.clear();
  }


bool Board::has_valid_kings() const {

  //Declare Variables, intialize to 0
  int BlackKings = 0, WhiteKings = 0;
  //Iterate through map
  for(std::map<std::pair<char, char>, Piece*>::const_iterator it = occ.cbegin(); 
	it != occ.cend(); it++) {
  	if(((it->second)->is_white()) && ((it->second)->to_ascii()== 'K')) {
    	WhiteKings++;
  }
  	if(!((it->second)->is_white()) && ((it->second)->to_ascii()== 'k')) {
    	BlackKings++;
  	}
	}
  //Number of Kings per player should be 1
  if((BlackKings != 1) && (WhiteKings != 1)) {
    return false;
        }
	return true;
    /////////////////////////
}


//board is trying to access a private member of Game in line 126, the call "Game.board". 

void Board::display() const {
    //Terminal terminal;
    Chess::Game game;
    const int squareHeight = 3;
    const int squareWidth = 4;
      
    for (int row = 0; row < 8 * squareHeight; ++row)
    {
      int squareRow = row / squareHeight;
      // print side border with numbering
      if (row % 3 == 1)
      {
        cout <<(char)('1' + 7 - squareRow);
      }
      // print the chess board
      for (int col = 0; col < 8 * squareWidth; ++col)
      {
        int squareCol = col / squareWidth;
        if (((row % 3) == 1) && ((col % 4) == 1 || (col % 4) == 2))
        {
          if ((col % 4) == 1)
          {
            Terminal::color_fg(true, Terminal::MAGENTA);
            Terminal::color_bg(Terminal::WHITE);
          }
          else
          {
						cout << this->operator()(std::pair<char, char>( 7 - squareRow , squareCol))->to_ascii();
            //cout << game.board(std::pair<char, char>( 7 - squareRow , squareCol))->to_ascii();
          }
        }
        else
        {
          if ((squareRow + squareCol) % 2 == 1)
          {
            cout << ' ';
          }
        }
      }
      cout << endl;
    }
    // print the bottom border with numbers
    for (int row = 0; row < squareHeight; ++row)
    {
      if (row % 3 == 1)
      {
        
        for (int col = 0; col < 8 * squareWidth; ++col)
        {
          int squareCol = col / squareWidth;
          if ((col % 4) == 1)
          {
            cout << "  "<< char(squareCol + 'A');
          }
          else
          {
            cout << "  ";
          }
        }
        cout << endl;
      }
    }
  }

  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  std::ostream& operator<<(std::ostream& os, const Board& board) {
    for(char r = '8'; r >= '1'; r--) {
      for(char c = 'A'; c <= 'H'; c++) {
        const Piece* piece = board(std::pair<char, char>(c, r));
        if (piece) {
          os << piece->to_ascii();
        } else {
          os << '-';
        }
      }
      os << std::endl;
    }
    return os;
  }

}
