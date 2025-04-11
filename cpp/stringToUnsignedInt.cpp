#include <cstring>
#include <iostream>
#include <string>

using namespace std;

void clrscr();

int main() {
  bool x = true;
  unsigned int inputInInt;
  string inputInString;
  char buffer[50];

  // Switch to alternate terminal buffer
  cout << "\e[?1049h";

  // Input Integer
  do {
    clrscr();
    int nonNumCount = 0;
    cout << "Enter a positive number: ";
    getline(cin, inputInString);
    /* Check if input is something other than a decimal digit by
       comparing its ASCII code */
    for (int i = 0; i < inputInString.length(); i++) {
      if (inputInString[i] < 48 || inputInString[i] > 57) {
        nonNumCount++;
      }
    }

    // Get input again if it contains a non numeric character or if it's empty
    if (!inputInString.empty() && nonNumCount == 0) {
      x = false;
    }
  } while (x == true);
  inputInInt = stoi(inputInString);

  cout << "You entered: " << inputInInt << endl;

  // Prompt for exiting the program
  while (strlen(buffer) != 1 || toupper(buffer[0]) != 'Y') {
    cout << "Press Y to exit: ";
    cin >> buffer;
  }

  // Return to previous terminal buffer
  clrscr();
  cout << "\e[?1049l";
  return 0;
}

void clrscr() { cout << "\e[2J\e[H"; }
