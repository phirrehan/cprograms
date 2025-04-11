#include <iostream>
using namespace std;

unsigned int fib(unsigned int);

int main() {
  int n;
  cout << "Enter the number of terms: ";
  cin >> n;
  if (n <= 0) {
    cout << "error: only positive numbers are allowed.\n";
    return 1;
  } else {
    for (int i = 1; i <= n; i++) {
      cout << fib(i) << " ";
    }
    cout << "\n";
    return 0;
  }
}

unsigned int fib(unsigned int n) {
  int a = 0, b = 1, hold;
  if (n == 1)
    return a;
  else if (n <= 3)
    return b;
  else {
    for (int i = 1; i < n; i++) {
      hold = b;
      b += a;
      a = hold;
    }
    return b;
  }
}
