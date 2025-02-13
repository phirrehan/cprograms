#include <iostream>
#include <string>

using namespace std;

// Function Declarations
void nameInit(char, int, int, int, int);
void boardInit();
void returnBuffer();
void alternateBuffer();
void clrscr();
void printBoard();
void render();
char pawnPromotion();

// Structures
struct piecePos {
  char name;
  int row;
  int col;
};

// Global Variables
char board[8][8];
piecePos white_pieces[16];
piecePos black_pieces[16];

// Classes
class Piece {
public:
  void setRow(int r) { row = r; }
  void setCol(int c) { col = c; }
  int getRow() { return row; }
  int getCol() { return col; }
  int getIndex() { return index; }

  /* bool return type indicates if move() was successfull
   * or not depending on its parameters */
  bool move(int x, int y); // Move piece to (x,y) position
  bool take(int x, int y); // Take piece to (x,y) position
  void show();             // Show available moves with *
protected:
  int index;    // Index for struct array
  int row;      // Horizontal position in 8x8 board
  int col;      // Vertical position in 8x8 board
  string color; // Can be black or white
  void setBoard(int r, int c, char pieceInitial) {
    board[row][col] = ' ';      // Change initial position to space
    board[r][c] = pieceInitial; // Add pieceInitial at final position
    if (color == "white") {
      white_pieces[index].row = r;
      white_pieces[index].col = c;
    } else {
      black_pieces[index].row = r;
      black_pieces[index].col = c;
    }
  }
};

// To add: En Passant
class Pawn : public Piece {
private:
  void setBoard(int r, int c, char pieceInitial) {
    board[row][col] = ' ';      // Change initial position to space
    board[r][c] = pieceInitial; // Add pieceInitial at final position
    if (color == "white") {
      white_pieces[index].row = r;
      white_pieces[index].col = c;
      if (r == 0) {
        white_pieces[index].name = pawnPromotion();
      }
    } else {
      black_pieces[index].row = r;
      black_pieces[index].col = c;
      if (r == 7) {
        black_pieces[index].name = pawnPromotion();
      }
    }
  }

public:
  // Constructor
  Pawn(char colorInitial, int r, int c, int ind) {
    if (colorInitial == 'w')
      color = "white";
    else if (colorInitial == 'b')
      color = "black";
    row = r;
    col = c;
    index = ind;
  }

  bool move(int r, int c) {
    if (color == "white") {
      if (row == 6 && r == 4 && col == c && board[r][c] == ' ') {
        setBoard(r, c, 'P');
        return true;
      } else if (row == 6 && r == 5 && col == c && board[r][c] == ' ') {
        setBoard(r, c, 'P');
        return true;
      } else if (row != 6 && r == row - 1 && col == c && board[r][c] == ' ') {
        setBoard(r, c, 'P');
        return true;
      } else
        return false;
    } else {
      if (row == 1 && r == 3 && col == c && board[r][c] == ' ') {
        setBoard(r, c, 'P');
        return true;
      } else if (row == 1 && r == 2 && col == c && board[r][c] == ' ') {
        setBoard(r, c, 'P');
        return true;
      } else if (row != 1 && r == row + 1 && col == c && board[r][c] == ' ') {
        setBoard(r, c, 'P');
        return true;
      } else
        return false;
    }
  }
  // Ensure r and c are positive
  bool take(int r, int c) {
    bool check;
    if (color == "white") {
      if (((c == col - 1 || c == col + 1) && r == row - 1) &&
          board[r][c] != ' ') {
        for (int i = 0; i < 8; i++) {
          if (black_pieces[i].row == r && black_pieces[i].col == c) {
            setBoard(r, c, 'P');
            check = true;
            break;
          }
        }
      }
      if (check != true)
        check = false;
      return check;
    } else {
      if (((c == col - 1 || c == col + 1) && r == row + 1) &&
          board[r][c] != ' ') {
        for (int i = 0; i < 8; i++) {
          if (white_pieces[i].row == r && white_pieces[i].col == c) {
            setBoard(r, c, 'P');
            check = true;
            break;
          }
        }
      }
      if (check != true)
        check = false;
      return check;
    }
  }
  void show() {
    if (color == "white") {
      if (row == 6 && board[row - 1][col] == ' ') {
        board[row - 1][col] = '*';
        if (board[row - 2][col] == ' ')
          board[row - 2][col] = '*';
        render();
        board[row - 1][col] = ' ';
        if (board[row - 2][col] == '*')
          board[row - 2][col] = ' ';
      } else if (board[row - 1][col - 1] != ' ' ||
                 board[row - 1][col + 1] != ' ') {
        for (int i = 0; i < 8; i++) {
          if (black_pieces[i].row == row - 1 &&
              black_pieces[i].col == col - 1) {
            board[row - 1][col - 1] = '*';
            render();
          } else if (black_pieces[i].row == row - 1 &&
                     black_pieces[i].col == col + 1) {
            board[row - 1][col + 1] = '*';
            render();
            board[row - 1][col + 1] = ' ';
            if (board[row - 1][col - 1] == '*')
              board[row - 1][col - 1] = ' ';
          }
        }
      }
    } else {
      if (row == 1 && board[row + 1][col] == ' ') {
        board[row + 1][col] = '*';
        if (board[row + 2][col] == ' ')
          board[row + 2][col] = '*';
        render();
        board[row + 1][col] = ' ';
        if (board[row + 2][col] == '*')
          board[row + 2][col] = ' ';
      } else if (board[row + 1][col - 1] != ' ' ||
                 board[row + 1][col + 1] != ' ') {
        for (int i = 0; i < 8; i++) {
          if (white_pieces[i].row == row + 1 &&
              white_pieces[i].col == col - 1) {
            board[row + 1][col - 1] = '*';
            render();
          } else if (white_pieces[i].row == row + 1 &&
                     white_pieces[i].col == col + 1) {
            board[row + 1][col + 1] = '*';
            render();
            board[row + 1][col + 1] = ' ';
            if (board[row + 1][col - 1] == '*')
              board[row + 1][col - 1] = ' ';
          }
        }
      }
    }
  }
};

class Rook : public Piece {
public:
  // Constructor
  Rook(char colorInitial, int r, int c, int ind) {
    if (colorInitial == 'w')
      color = "white";
    else if (colorInitial == 'b')
      color = "black";
    row = r;
    col = c;
    index = ind;
  }
  bool move(int r, int c) {
    int count = 0; /* count keeps track of how many
                      pieces lie along the rook's path */
    if (r == row) {
      if (c == col)
        return false;
      else if (c < col) {
        for (int i = col; i >= c; i--) {
          if (board[r][i] != ' ') {
            count++;
          }
        }
        if (count == 0) {
          setBoard(r, c, 'R');
          return true;
        } else
          return false;
      } else {
        for (int i = col; i <= c; i++) {
          if (board[r][i] != ' ') {
            count++;
          }
        }
        if (count == 0) {
          setBoard(r, c, 'R');
          return true;
        } else
          return false;
      }
    } else if (c == col) {
      if (r == row)
        return false;
      else if (r < row) {
        for (int i = row; i >= r; i--) {
          if (board[r][i] != ' ') {
            count++;
          }
        }
        if (count == 0) {
          setBoard(r, c, 'R');
          return true;
        } else
          return false;
      } else {
        for (int i = row; i <= r; i++) {
          if (board[r][i] != ' ') {
            count++;
          }
        }
        if (count == 0) {
          setBoard(r, c, 'R');
          return true;
        } else
          return false;
      }

    } else
      return false;
  }
  bool take(int r, int c) {
    int count = 0; /* count keeps track of how many
                      pieces lie along the rook's path */
    if (r == row) {
      if (c == col)
        return false;
      else if (c < col) {
        for (int i = col; i >= c; i--) {
          if (board[r][i] != ' ') {
            count++;
          }
        }
        if (count == 0) {
          setBoard(r, c, 'R');
          return true;
        } else
          return false;
      } else {
        for (int i = col; i <= c; i++) {
          if (board[r][i] != ' ') {
            count++;
          }
        }
        if (count == 0) {
          setBoard(r, c, 'R');
          return true;
        } else
          return false;
      }
    } else if (c == col) {
      if (r == row)
        return false;
      else if (r < row) {
        for (int i = row; i >= r; i--) {
          if (board[r][i] != ' ') {
            count++;
          }
        }
        if (count == 0) {
          setBoard(r, c, 'R');
          return true;
        } else
          return false;
      } else {
        for (int i = row; i <= r; i++) {
          if (board[r][i] != ' ') {
            count++;
          }
        }
        if (count == 0) {
          setBoard(r, c, 'R');
          return true;
        } else
          return false;
      }

    } else
      return false;
  }
};

int main() {
  boardInit();
  printBoard();
  return 0;
}

/* For initializing board array and white/black_pieces structs
 * in the boardInit() function */
void nameInit(char name, int index, int row_black, int row_white, int col) {
  black_pieces[index].name = name;
  board[row_black][col] = name;
  white_pieces[index].name = name;
  board[row_white][col] = name;
}
// Initialize the board array for starting chess positions
void boardInit() {
  // Put in spaces from A6 to H3
  fill(&board[2][0], &board[6][0], ' ');

  // Pawns
  int i;
  for (i = 0; i < 8; i++) {
    // Row and Column variables
    white_pieces[i].row = 6;
    white_pieces[i].col = i;
    black_pieces[i].row = 1;
    black_pieces[i].col = i;

    // Name variables
    nameInit('P', i, 1, 6, i);
  }

  // Rest of the Pieces
  for (i = 8; i < 16; i++) {
    // Row/Col
    int col = i - 8;
    black_pieces[i].row = 0;
    black_pieces[i].col = col;
    white_pieces[i].row = 7;
    white_pieces[i].col = col;

    // Names
    if (col == 0 || col == 7) {
      nameInit('R', i, 0, 7, col); // Rooks
    } else if (col == 1 || col == 6) {
      nameInit('N', i, 0, 7, col); // Knights
    } else if (col == 2 || col == 5) {
      nameInit('B', i, 0, 7, col); // Bishops
    } else if (col == 3) {
      nameInit('Q', i, 0, 7, col); // Queen
    } else if (col == 4) {
      nameInit('K', i, 0, 7, col); // King
    }
  }
}
void printBoard() {
  /*
      A   B   C   D   E   F   G   H
    |‾‾‾|‾‾‾|‾‾‾|‾‾‾|‾‾‾|‾‾‾|‾‾‾|‾‾‾|
  8 | R | N | B | Q | K | B | N | R |
    |‾‾‾|‾‾‾|‾‾‾|‾‾‾|‾‾‾|‾‾‾|‾‾‾|‾‾‾|
  7 | P | P | P | P | P | P | P | P |
    |‾‾‾|‾‾‾|‾‾‾|‾‾‾|‾‾‾|‾‾‾|‾‾‾|‾‾‾|
  6 |   |   |   |   |   |   |   |   |
    |‾‾‾|‾‾‾|‾‾‾|‾‾‾|‾‾‾|‾‾‾|‾‾‾|‾‾‾|
  5 |   |   |   |   |   |   |   |   |
    |‾‾‾|‾‾‾|‾‾‾|‾‾‾|‾‾‾|‾‾‾|‾‾‾|‾‾‾|
  4 |   |   |   |   |   |   |   |   |
    |‾‾‾|‾‾‾|‾‾‾|‾‾‾|‾‾‾|‾‾‾|‾‾‾|‾‾‾|
  3 |   |   |   |   |   |   |   |   |
    |‾‾‾|‾‾‾|‾‾‾|‾‾‾|‾‾‾|‾‾‾|‾‾‾|‾‾‾|
  2 | P | P | P | P | P | P | P | P |
    |‾‾‾|‾‾‾|‾‾‾|‾‾‾|‾‾‾|‾‾‾|‾‾‾|‾‾‾|
  1 | R | N | B | Q | K | B | N | R |
     ‾‾‾ ‾‾‾ ‾‾‾ ‾‾‾ ‾‾‾ ‾‾‾ ‾‾‾ ‾‾‾
  */

  // Display the above commented board
  cout << "    A   B   C   D   E   F   G   H  " << endl;
  for (int row = 0; row < 8; row++) {
    cout << "  |‾‾‾|‾‾‾|‾‾‾|‾‾‾|‾‾‾|‾‾‾|‾‾‾|‾‾‾|" << endl;
    cout << 8 - row << " |";
    for (int col = 0; col < 8; col++) {
      cout << " " << board[row][col] << " |";
    }
    cout << endl;
  }
  cout << "   ‾‾‾ ‾‾‾ ‾‾‾ ‾‾‾ ‾‾‾ ‾‾‾ ‾‾‾ ‾‾‾ " << endl;
}

// Clear Screen
void clrscr() { cout << "\e[2J\e[H"; }

// Go to another Buffer
void alternateBuffer() { printf("\e[?1049h"); }

// Return to original Buffer
void returnBuffer() { printf("\e[2J\e[H\e[?1049l"); }

// Render game
// void render();

// Promote pawn to piece
// char pawnPromotion();
