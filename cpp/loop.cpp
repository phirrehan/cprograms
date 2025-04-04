#include <iostream>

using namespace std;

int main() {
  // b = 2, p = 3
  int b, p, ans = 1;
  cout << "Enter the base and power: ";
  cin >> b >> p;
  int i = 1;
  while( i <= p) {
    ans *= b;
    i++;
  }
  cout << " b^p = " << ans << endl;
}
