#include <iostream>

using namespace std;

// Function Prototypes
void setPiecePos(int, char, int, int, int);
void init();
void setBoard();
void alternateBuffer();
void printBoard();
void clrscr();
void returnBuffer();

// Structure for position of a piece in board
struct piecePos {
  char name;
  int  row;
  int  col;
};

// Global Arrays
char     board[8][8];
piecePos white_pieces[16];
piecePos black_pieces[16];

int main() {
  string var;
  bool isGameEnded = false;
  init();
  setBoard();
  alternateBuffer();
  while (! isGameEnded) {
    printBoard();
    cin >> var;
    clrscr();
    isGameEnded = true;
  }
  returnBuffer();
  return 0;
}

void setPiecePos(int index, char name, int wRow, int bRow, int col) {
  white_pieces[index].name = name;
  white_pieces[index].row = wRow;
  white_pieces[index].col = col;
  black_pieces[index].name = name;
  black_pieces[index].row = bRow;
  black_pieces[index].col = col;
}

void init() {
  for (int i = 0; i < 16; i++) {
    int j = i - 8;
    switch (i) {
      case 0 ... 7:
        setPiecePos(i, 'P', 6, 1, i); break;
      case 8:
      case 15:
        setPiecePos(i, 'R', 7, 0, j);
        break;
      case 9:
      case 14:
        setPiecePos(i, 'N', 7, 0, j);
        break;
      case 10:
      case 13:
        setPiecePos(i, 'B', 7, 0, j);
        break;
      case 11:
        setPiecePos(i, 'Q', 7, 0, j);
        break;
      case 12:
        setPiecePos(i, 'K', 7, 0, j);
    }
  }
}

void setBoard() {
  // set black pieces
  for (int j = 0; j < 2; j++)
    for (int i = 0; i < 8; i++) {
      if (j == 0)
        board[j][i] = black_pieces[i+8].name;
      else
        board[j][i] = black_pieces[i].name;
    }

  // set empty spaces
  for (int j = 2; j < 6; j++)
    for (int i = 0; i < 8; i++)
      board[j][i] = ' ';

  // set white pieces
  for (int j = 6; j < 8; j++)
    for (int i = 0; i < 8; i++) {
      if (j == 6)
        board[j][i] = white_pieces[i].name;
      else
        board[j][i] = white_pieces[i+8].name;
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
