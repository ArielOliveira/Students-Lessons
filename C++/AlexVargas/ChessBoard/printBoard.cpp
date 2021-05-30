#include <iostream>

using std::endl;
using std::cout;



int main() {
    for(char r = '1'; r <= '8'; r++) {
        cout << r;
    }

    cout << endl;
    for(char r = '8'; r >= '1'; r--) {
      
      for(char c = 'A'; c <= 'H'; c++) {
        //const Piece* piece = board(std::pair<char, char>(c, r));
        //if (piece) {
          //os << piece->to_ascii();
        //} else {
          cout << '-';
        //}
      }
      cout << std::endl;
    }

return 0;
}