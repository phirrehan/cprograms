#include <ctype.h>
#include <stdio.h>

enum bool {
  FALSE,
  TRUE,
};
enum game_state {
  INPROGRESS = 1,
  DRAW,
  X_WINS,
  O_WINS,
};

// markers will contain information provided by players
int state;
char markers[10];

// Function Declarations
void printGrid(void);
void printRules(void (*)(void));
void alternateBuffer(void);
void returnBuffer(void);
void clrscr(void);
void checkGameState(void);
void getInput(int);
int endGameMessage(void);

int main() {
  int x = TRUE;
  alternateBuffer();
  clrscr();
  printRules(printGrid);
  while (x == TRUE) {
    state = INPROGRESS;

    // Set all values(except for last) of array markers with spaces
    for (int i = 0; i < 9; i++) markers[i] = ' ';

    int j = 0;
    while (state == INPROGRESS) {
      clrscr();
      printGrid();
      checkGameState();
      getInput(j);
      j++;
    }
    x = endGameMessage();
  }
  returnBuffer();
  return 0;
}

void printGrid() {
  printf("\n");
  printf("        %c | %c | %c    \n", markers[0], markers[1], markers[2]);
  printf("      ----o---o----     \n");
  printf("        %c | %c | %c    \n", markers[3], markers[4], markers[5]);
  printf("      ----o---o----     \n");
  printf("        %c | %c | %c  \n\n", markers[6], markers[7], markers[8]);
  printf("");
}

void printRules(void (*callback)(void)) {
  printf("");
  printf("o-----------------------o\n");
  printf("|      Tic Tac Toe      |\n");
  printf("o-----------------------o\n");
  printf("");

  // Initialize Array markers with '1', '2', '3',..., '9'
  for (int i = 0; i < 9; i++)
    markers[i] =
        i + 1 + 48;  // ASCII code of digit 0 and 9 is 48 and 57 respectively

  callback();  // printGrid()
  printf(
      "Player 1 is X and Player "
      "two "
      "is O.\n\n");

  // Continue only if y/Y is pressed
  char buffer[50] = {0};
  while (toupper(buffer[0]) != 'Y') {
    printf("Press Y to continue: ");
    fgets(buffer, sizeof(buffer), stdin);
  }
}

void alternateBuffer() {
  printf("\e[?1049h");
  fflush(stdout);
}

void returnBuffer() {
  printf("\e[?1049l");
  fflush(stdout);
}

void clrscr() {
  printf("\e[2J");  // Clears screen
  printf("\e[H");   // Move cursor to home position
}
void checkGameState() {
  // Variable count keeps track of slots filled by players
  int count = 0, i;
  char str[2] = {'X', 'O'};

  for (i = 0; i < sizeof(markers); i++) {
    if (markers[i] == 'X' || markers[i] == 'O') count++;
  }

  // Check Win States
  for (i = 0; i < sizeof(str); i++) {
    if ((str[i] == markers[0] && str[i] == markers[1] &&
         str[i] == markers[2]) ||
        (str[i] == markers[3] && str[i] == markers[4] &&
         str[i] == markers[5]) ||
        (str[i] == markers[6] && str[i] == markers[7] &&
         str[i] == markers[8]) ||
        (str[i] == markers[0] && str[i] == markers[3] &&
         str[i] == markers[6]) ||
        (str[i] == markers[1] && str[i] == markers[4] &&
         str[i] == markers[7]) ||
        (str[i] == markers[2] && str[i] == markers[5] &&
         str[i] == markers[8]) ||
        (str[i] == markers[0] && str[i] == markers[4] &&
         str[i] == markers[8]) ||
        (str[i] == markers[6] && str[i] == markers[4] &&
         str[i] == markers[2])) {
      if (i == 0)
        state = X_WINS;
      else
        state = O_WINS;
    }
  }

  if (count == 9 && state != X_WINS && state != O_WINS)
    state = DRAW;
  else if (count != 9 && state != X_WINS && state != O_WINS)
    state = INPROGRESS;
}

// variable counter is used to keep track of players' turns
void getInput(int counter) {
  int x = TRUE;
  char buffer[50];
  if (state == INPROGRESS) {
    buffer[0] = 0;
    if (counter % 2 == 0) {
      while (x == TRUE) {
        printf("Player 1 to Move: ");
        fgets(buffer, sizeof(buffer), stdin);
        // Check if buffer[0] is a non-zero digit by comparing its ASCII code
        if ((int)buffer[0] > 48 && (int)buffer[0] <= 57) {
          // Check if if slot is already filled or not
          if (markers[(buffer[0] - '0') - 1] != 'X' &&
              markers[(buffer[0] - '0') - 1] != 'O') {
            x = FALSE;
          } else
            printf("The slot is already filled. \n\n");
        }
      }
      markers[(buffer[0] - '0') - 1] = 'X';
    } else {
      while (x == TRUE) {
        printf("Player 2 to Move: ");
        fgets(buffer, sizeof(buffer), stdin);
        // Check if buffer[0] is a non-zero digit by comparing its ASCII code
        if ((int)buffer[0] > 48 && (int)buffer[0] <= 57) {
          // Check if if slot is already filled or not
          if (markers[buffer[0] - '0' - 1] != 'X' &&
              markers[buffer[0] - '0' - 1] != 'O') {
            x = FALSE;
          } else
            printf("The slot is already filled.\n\n");
        }
      }
      markers[(buffer[0] - '0') - 1] = 'O';
    }
  }
}

int endGameMessage() {
  char buffer[50] = {0};
  switch (state) {
    case DRAW:
      printf("The Game is a Draw\n\n");
      break;

    case X_WINS:
      printf("Player 1 Wins!\n\n");
      break;

    case O_WINS:
      printf("Player 2 Wins!\n\n");
      break;
  }

  // Get Input
  int x = TRUE;
  while (x == TRUE) {
    printf("Press Y to play again or N to exit: ");
    fgets(buffer, sizeof(buffer), stdin);
    if (toupper(buffer[0]) == 'Y')
      x = FALSE;
    else if (toupper(buffer[0]) == 'N')
      x = FALSE;
  }

  // Return Boolean Expression
  if (toupper(buffer[0]) == 'Y')
    return TRUE;
  else
    return FALSE;
}
