#include <iostream>
int fib(int num) {
  if (num == 0 || num == 1)
    return num;
  else
    return fib(num - 1) + fib(num - 2);
}
int main() {
  int num;
  std::cout << "Enter a number: ";
  std::cin >> num;
  for (int i = 0; i <= num; i++)
    std::cout << fib(i) << " ";
  std::cout << '\n';
  return 0;
}
