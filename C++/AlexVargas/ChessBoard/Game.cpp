#include <cassert>
#include <cmath>
#include <string>
#include "Game.h"


using std::string;

namespace Chess
{

  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  Game::Game() : is_white_turn(true) {
    // Add the pawns
    for (int i = 0; i < 8; i++) {
      board.add_piece(std::pair<char, char>('A' + i, '1' + 1), 'P');
      board.add_piece(std::pair<char, char>('A' + i, '1' + 6), 'p');
    }

    // Add the rooks
    board.add_piece(std::pair<char, char>( 'A'+0 , '1'+0 ) , 'R' );
    board.add_piece(std::pair<char, char>( 'A'+7 , '1'+0 ) , 'R' );
    board.add_piece(std::pair<char, char>( 'A'+0 , '1'+7 ) , 'r' );
    board.add_piece(std::pair<char, char>( 'A'+7 , '1'+7 ) , 'r' );

    // Add the knights
    board.add_piece(std::pair<char, char>( 'A'+1 , '1'+0 ) , 'N' );
    board.add_piece(std::pair<char, char>( 'A'+6 , '1'+0 ) , 'N' );
    board.add_piece(std::pair<char, char>( 'A'+1 , '1'+7 ) , 'n' );
    board.add_piece(std::pair<char, char>( 'A'+6 , '1'+7 ) , 'n' );

    // Add the bishops
    board.add_piece(std::pair<char, char>( 'A'+2 , '1'+0 ) , 'B' );
    board.add_piece(std::pair<char, char>( 'A'+5 , '1'+0 ) , 'B' );
    board.add_piece(std::pair<char, char>( 'A'+2 , '1'+7 ) , 'b' );
    board.add_piece(std::pair<char, char>( 'A'+5 , '1'+7 ) , 'b' );

    // Add the kings and queens
    board.add_piece(std::pair<char, char>( 'A'+3 , '1'+0 ) , 'Q' );
    board.add_piece(std::pair<char, char>( 'A'+4 , '1'+0 ) , 'K' );
    board.add_piece(std::pair<char, char>( 'A'+3 , '1'+7 ) , 'q' );
    board.add_piece(std::pair<char, char>( 'A'+4 , '1'+7 ) , 'k' );
  }

  Game::Game(const Game& game) {
    is_white_turn = game.is_white_turn;
    board = Board(game.board);
  }

  Game::Game(const Board& board, bool white) {
    this->is_white_turn = white;
    this->board = Board(board);
  }

  void Game::make_move(std::pair<char, char> start, std::pair<char, char> end) {
  //checking that the start position and end postiions are in the bounds of the grid
      if (!board.isInBounds(start)) {
          throw Chess::Exception("start position is not on the board");
      } else if (!board.isInBounds(end)) {
          throw Chess::Exception("end position is not on the board");
      }
                //check if the end position is in bounds       
  
    // retrieves a piece from start position
    const Piece* piece = board(start); 
    // retrieves a piece from end position
    const Piece* opponent = board(end);

    if (!piece) {
      throw Chess::Exception("no piece at start position");
    }

    if (piece->is_white() != is_white_turn) {
        throw Chess::Exception("piece color and turn do not match");
    }
    
    bool madeMove = false;
    if (piece && opponent) {
      if (captureMove(start, end, piece, opponent)) {
        board.remove_piece(end);
        board.move_piece(start, end);
        madeMove = true;
      }
    }
	//otherwise, it is a normal move
    else if (piece && !opponent) {
      if (validMove(start, end, piece)) {
        board.move_piece(start, end);
        madeMove = true;
      }
    }
     
    if (madeMove) {
      if (is_white_turn){
        is_white_turn = false;
      } else {
        is_white_turn = true;
      }
    } 
  }


// in_check
bool Game::in_check(bool white) const {
    int kingRow = 0;
    int kingCol = 0;

    for (int row = 0; row < 8; ++row)
    {
      for (int col = 0; col < 8; ++col)
      {
        if (board(std::pair<char, char>( row , col)) != 0)
        {
          if (white)
          {
            if (board(std::pair<char, char>( row , col))->to_ascii() == 'K')
            {
              kingRow = row;
              kingCol = col;
            }
          }
        }
      }
    }
      
    // run through the opponent's pieces and see if any can take the king
    for (int row = 0; row < 8; ++row)
    {
      for (int col = 0; col < 8; ++col)
      {
        if (board(std::pair<char, char>( row , col)) != 0)
        {
          if (white)
          {

              if (captureMove({row, col}, {kingRow, kingCol}, board(std::pair<char, char>( row , col)), board(std::pair<char, char>( kingRow , kingCol)))){
                throw Chess::Exception("move exposes check");
                return true;
            }
						
          }
        }
      }
    }
    
    return false;
  }

bool Game::in_mate(bool white) const {
    // run through all pieces
    for (int row = 0; row < 8; ++row)
    {
      for (int col = 0; col < 8; ++col)
      {
        if (board(std::pair<char, char>( row , col)) != 0)
        {
          // if it is a piece of the current player, see if it has a legal move
          if (white)
          {
            for (int moveRow = 0; moveRow < 8; ++moveRow)
            {
              for (int moveCol = 0; moveCol < 8; ++moveCol)
              {

                if (captureMove({row, col}, {moveRow, moveCol}, board(std::pair<char, char>( row , col)), board(std::pair<char, char>( moveRow , moveCol))))
                {
								//creating a copy of the current game
                  Game game(*this);
								//exectuing the move in our alternative board
                  game.make_move({row, col}, {moveRow, moveCol});
								//checks if the king is in check. if the king is not in check, that means that the move can be made
                  bool boolCanMove = !game.in_check(game.is_white_turn);
                                  
                  if (boolCanMove)

                  {
                    return true;
                  }
                }
              }
            }
          }
        }
      }
    }
    return false;
  }



  bool Game::in_stalemate(bool white) const {
    // run through all pieces
    for (int row = 0; row < 8; ++row)
    {
      for (int col = 0; col < 8; ++col)
      {
        if (board(std::pair<char, char>( row , col)) != 0)
        {
          // if it is a piece of the current player, see if it has a legal move
          if (white)
          {
            for (int moveRow = 0; moveRow < 8; ++moveRow)
            {
              for (int moveCol = 0; moveCol < 8; ++moveCol)
              {

                 if (captureMove({row, col}, {moveRow, moveCol}, board(std::pair<char,char>( row , col)), board(std::pair<char,char>( moveRow , moveCol))))
                {
                  // make move and check whether king is in check
                  //const Piece* temp = board(std::pair<char, char>( row , col));
									
                  	//creating a copy of the current game
                  Game game(*this);
								  //exectuing the move in our alternative board
                  game.make_move({row, col}, {moveRow, moveCol});
								  //checks if the king is in check. if the king is not in check, that means that the move can be made
                  bool boolCanMove = !game.in_check(game.is_white_turn);

                                  
                  if (boolCanMove)
                  {
                    return true;
                  }
                }
              }
            }
          }
        }
      }
    }
    return false;
  }

  /*
  @ Params 
  */
  bool Game::captureMove(std::pair<char, char> start, std::pair<char, char> end, const Piece* playPiece, const Piece* opponent) const {
	//if the piece we are moving is the same color as the piece we are attempting to capture, then this is not a valid capture move and we return false
    if (playPiece->is_white() == opponent->is_white()) {
      throw Chess::Exception("cannot capture own piece");
      return false;
    }

  //if the piece we are playing is not moving in a legal capture shape, then this is not a valid capture move
    if (!playPiece->legal_capture_shape(start, end))
       throw Chess::Exception("illegal capture shape");
	//if the piece is not moving in a valid path, then this is not a valid move.
    if (!validMove(start, end, playPiece)) {
      std::cout << "invalid move" << std::endl;
      return false;
    }
  //if the piece passes all of the checks, then it is a valid move and we return true
    return true; 
  }

  std::pair<int, int> Game::straightMove(std::pair<char, char> start, std::pair<char, char> end, int& distance) const {
		//direction = {x, y}
    std::pair<int, int> direction = {0, 0};  
    if (start.first == end.first) { //if the piece is moving vertically
      distance = abs(end.second - start.second);
      if (start.second < end.second) //this means we are moving up
        direction.second = 1;
      else //this means we are moving down
        direction.second = -1;
    } else if (start.second == end.second) { //if the piece is moving horizontally
      distance = abs(end.first - start.first);
      if (start.first < end.first) //this means we are moving to the right
        direction.first = 1;
      else //this means we are moving to the left
        direction.first = -1;
    }
	//if direction is {0, 0, that means the move is not in a vertical or horzontal direction
    return direction;
  }

//checking if the move is a diagonal move
  std::pair<int, int> Game::diagonalMove(std::pair<char, char> start, std::pair<char, char> end, int& distance) const {
    std::pair<int, int> direction = {0, 0};
    
    int distance1 = abs(end.first - start.first);
    int distance2 = abs(end.second - start.second);

//if the distances are equal, we know we have a diagonal
    if (distance1 == distance2 && distance1 != 0 && distance2 != 0) {
      distance = distance1;

//this means the direction is to the right
      if (end.first > start.first)
        direction.first = 1;
      else
		//this means the direction is to the left
        direction.first = -1;

// this means the direction is up
      if (end.second > start.second)
        direction.second = 1;
      else
		// this means the direction is down
        direction.second = -1;
    }  
// direction is a pair indicating the direction of the path
    return direction;
  }

  bool Game::putsInCheck(std::pair<char, char> start, std::pair<char, char> end) const {
    	//creating a copy of the current game
      Game game(*this);
      //exectuing the move in our alternative board
      game.make_move(start, end);
      
      //checks if the king is in check. if the king is not in check, that means that the move can be made
      return game.in_check(game.is_white_turn);
  }

	// a valid move cannot collide with a piece and has to be either a straight line or a diagonal with exception of the Knights
  bool Game::validMove(std::pair<char, char> start, std::pair<char, char> end, const Piece* playPiece) const {
    int distance;

     if (!playPiece->legal_move_shape(start, end)) {
        throw Chess::Exception("illegal move shape");
        return false;
     }
    

     if (playPiece->to_ascii() == 'n' || playPiece->to_ascii() == 'N')
       return true;

    std::pair<char, char> currentPos = start;
    std::pair<int, int> direction = straightMove(start, end, distance);
    if (direction.first == 0 && direction.second == 0) {
			//this means the path is not vertical/horizontal, so we check for diagonal
      direction = diagonalMove(start, end, distance);
    }
    
    //this means that the path is not horizontal, veritcal, or diagonal
    if (direction.first == 0 && direction.second == 0) {
      throw Chess::Exception( "no direction was set, invalid move");
      return false;
    }
	
	//this for loop checks if there is a collision for each postion in the path to the end
    for (int i = 0; i < distance; i++) {
      currentPos.first += direction.first;
      currentPos.second += direction.second;
//this checks if there is a piece at the current position. If there is, return false as this is not a valid move
      if (board(currentPos) != NULL) {
        throw Chess::Exception("path is not clear");
        return false;
      }
    }
	//this means that there was no collision; return true because this is a validMove
    return true;    
  }


  std::istream& operator>> (std::istream& is, Game& game) {
    std::string line; // variable to store each line as we go through the file
    char row = '8'; // keeps track of the current row

    game.board.clear();

    bool invalidBoard = false; // will be set to true if any invalid input is found

    // checks for three conditions: first that we have not reached the end of the file, second that the row variable is less than 9, and third that the board does not read in any invalid input
    while (getline(is, line) && (row >= '1') && (!invalidBoard)) {
      // if line has more/less than 8 characters, then we have invalid input
      if (line.size() != 8) {
        invalidBoard = true;
        break;
      }

      char col = 'H'; // variable to keep track of the columns
      // for loops to iterate through all the characters in the current line
      for (std::string::const_reverse_iterator it = line.crbegin() ; it != line.crend(); ++it) {
				//checking that the column/line intersection contains a character
        if (*it != '-') {
					//if add_piece cannot find an associated piece for the character that was read in, the function will return  NULL, meaining we have invalid input
          if (!game.board.add_piece({col, row}, *it)) {
            invalidBoard = true;
            break;
          }
        }
        col--;
      }
      row--;
    }
// reading in line 9 which contains a character depicting whose turn it is 
    if (!invalidBoard) {
			//if the size of the line isn't 1 this means the line contains invalid input
      if (line.size() != 1) {
        invalidBoard = true;
      } else {
				//if the character is b, then it is black's turn
        if (line[0] == 'b') 
          game.is_white_turn = false;
				//if the character is w, then it is white's turn. if it isn't either, then the character is invalid input
        else if (line[0] == 'w')
          game.is_white_turn = true;
        else
          invalidBoard = true;
      }
    } 

    assert(invalidBoard == false);

    return is;
  }


  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  std::ostream& operator<< (std::ostream& os, const Game& game) {
    // Write the board out and then either the character 'w' or the character 'b',
    // depending on whose turn it is
    return os << game.get_board() << (game.turn_white() ? 'w' : 'b');
  }
} 


 /*
  bool Game::normalMove(std::pair<char, char> start, std::pair<char, char> end, const Piece* playPiece) const {
	//if the piece is not moving in a legal direction(s) for the piece, then this is not a valid move so we return false

	//if the piece is not moving a valid way, then we return false
		if (!validMove(start, end, playPiece)) {
      std::cout << "invalid move" << std::endl;
			return false;
    }

		return true;
  }
  */


/*
		//Exceptions                                                                          
                  //check if the first piece is the current player's piece                                                                                                                                
                  //check if the specified piece can move in that shape                                                                                           
                  //check if the specified end space is occupied by another piece of the same color                                                                                                       
                if ((piece->is_white() && opponent->is_white()) || (!piece->is_white() && !opponent->is_white())) {
                  
                }
                  //check if the specified piece can capture in that shape                                                                                                                                
                if (!piece->legal_capture_shape(start, end)) {
                 
                }
		  //check if the path is clear                                                                                                                                                            
		if (!validMove(start, end, piece)) {
                  
                }
                if (game.in_stalemate(piece->is_white())) {
                  
                }
				*/
				



//if there exists a piece at the start and end positions, we know this is a captureMove

    /*if (in_check(is_white_turn)) {
      std::cout << "this movement is putting player in check" << std::endl;
      return;
    }*/