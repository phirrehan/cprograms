#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

enum menu_options { RECTANGLE = 1, TRIANGLE, CIRCLE, EXIT };
class shapes_2D {
protected:
  float area;
  float perimeter;
};

class rectangle : public shapes_2D {
private:
  float a;
  float b;

public:
  float Area() {
    area = a * b;
    return area;
  }
  float Perimeter() {
    perimeter = 2 * (a + b);
    return perimeter;
  }
  void setLength(float length1, float length2) {
    a = length1;
    b = length2;
  }

  float getLength1() { return a; }
  float getLength2() { return b; }
};

class triangle : public shapes_2D {
private:
  float a;
  float b;
  float c;

public:
  float Area() {
    float s = (a + b + c) / 2;
    area = sqrt(s * (s - a) * (s - b) * (s - c));
    return area;
  }
  float Perimeter() {
    perimeter = (a + b + c);
    return perimeter;
  }
  void setSides(float length1, float length2, float length3) {
    a = length1;
    b = length2;
    c = length3;
  }

  float getLength1() { return a; }
  float getLength2() { return b; }
  float getLength3() { return c; }
};

class circle : public shapes_2D {
private:
  float r;

public:
  float Area() {
    area = 3.141593 * r * r;
    return area;
  }
  float Perimeter() {
    perimeter = 2 * 3.141593 * r;
    return perimeter;
  }
  void setRadius(float radius) { r = radius; }
  float getRadius() { return r; }
};

void switchBuffer();
void returnToBuffer();
void clrscr();
void printMenu();
void getInput(void *, unsigned long, const string);
void getAllInputs(menu_options, void (*)(void *, unsigned long, const string),
                  float *, float *, float *);
void printOutput(float, float);

int main(int argc, char *argv[]) {
  rectangle myRect;
  triangle myTri;
  circle myCircle;
  menu_options option;
  unsigned short input;
  bool x = true;
  float a, b, c;
  switchBuffer();

  do {
    clrscr();
    printMenu();
    getInput(&input, sizeof(input), "Enter a number: ");
    clrscr();

    option = (menu_options)input;
    switch (option) {
    case RECTANGLE: {
      getAllInputs(option, getInput, &a, &b, &c);
      clrscr();
      myRect.setLength(a, b);
      printOutput(myRect.Area(), myRect.Perimeter());
      break;
    }

    case TRIANGLE: {
      getAllInputs(option, getInput, &a, &b, &c);
      clrscr();
      myTri.setSides(a, b, c);
      printOutput(myTri.Area(), myTri.Perimeter());
      break;
    }

    case CIRCLE: {
      getAllInputs(option, getInput, &a, &b, &c);
      clrscr();
      myCircle.setRadius(a);
      printOutput(myCircle.Area(), myCircle.Perimeter());
      break;
    }

    case EXIT:
      x = false;
      break;

    default:
      string anyKey;
      cout << "Invalid input. Try again" << "\n\n";
      cout << "Press any key to retry: ";
      getline(cin, anyKey);
    }
  } while (x == true);
  returnToBuffer();
  return 0;
}

void switchBuffer() { cout << "\e[?1049h"; }

void returnToBuffer() {
  cout << "\e[2J\e[H";
  cout << "\e[?1049l";
}

void clrscr() { cout << "\e[2J\e[H" << endl; }

void printMenu() {
  cout << "Choose one of the following shape:" << endl;
  cout << "1) Rectangle" << endl;
  cout << "2) Triangle" << endl;
  cout << "3) Circle" << endl;
  cout << "4) Exit Program" << "\n\n";
}

void getInput(void *num, unsigned long size, string message) {
  bool x = true;
  string inputInString;
  int nonNumCount, dotCount;
  do {
    nonNumCount = 0, dotCount = 0;
    cout << message;
    getline(cin, inputInString);

    // Check for short data type
    if (size == sizeof(short)) {
      /* Check if input is something other than a decimal digit or dot(.) by
         comparing its ASCII code */
      for (int i = 0; i < inputInString.length(); i++) {
        if (inputInString[i] < 48 || inputInString[i] > 57) {
          nonNumCount++;
        }
      }
      /* Get input again if it contains a non numeric character or if it's
       empty */
      if (!(inputInString.empty()) && nonNumCount == 0) {
        x = false;
      } else {
        cout << "Invalid input. Enter a positive number." << "\n\n";
      }
    }
    // Check for float data type
    else if (size == sizeof(float)) {
      /* Check if input is something other than a decimal digit or dot(.) by
         comparing its ASCII code */
      for (int i = 0; i < inputInString.length(); i++) {

        if (inputInString[i] < 48 || inputInString[i] > 57) {

          if (inputInString[i] == 46)
            dotCount++;
          else
            nonNumCount++;
        }
      }
      /* Get input again if it contains a non numeric character, if it's
       empty, or if it has more than one dots(.) */
      if (!(inputInString.empty()) && nonNumCount == 0 && dotCount <= 1) {
        x = false;
      } else {
        cout << "Invalid input. Enter a positive number." << "\n\n";
      }
    }
  } while (x == true);

  if (size == 2)
    (*(unsigned short *)num) = (unsigned short)stoi(inputInString);
  else if (size == 4)
    (*(float *)num) = stof(inputInString);
  cout << endl;
}
void getAllInputs(menu_options options,
                  void (*callback)(void *, unsigned long, const string),
                  float *a, float *b, float *c) {
  string message;
  switch (options) {
  case RECTANGLE: {

    message = "Enter the length of rectangle: ";
    callback(a, sizeof(*a), message);
    message = "Enter the width of rectangle: ";
    callback(b, sizeof(*b), message);
    break;
  }

  case TRIANGLE: {
    message = "Enter first side of triangle: ";
    callback(a, sizeof(*a), message);
    message = "Enter second side of triangle: ";
    callback(b, sizeof(*b), message);
    message = "Enter third side of triangle: ";
    callback(c, sizeof(*c), message);
    break;
  }

  case CIRCLE: {
    message = "Enter the radius of circle: ";
    callback(a, sizeof(*a), message);
    break;
  }
  case EXIT:
    break;
  }
}

void printOutput(float area, float perimeter) {
  string anyKey;
  cout << setprecision(2) << fixed;
  cout << "Area: " << area << endl;
  cout << "Perimeter: " << perimeter << "\n\n";
  cout << "Enter any key to continue: ";
  getline(cin, anyKey);
}
