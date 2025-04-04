#include <stdio.h>

float absoluteValue(float);
int getIntegerofRoot(int);
float getSquareRoot(int, int, float);

int main(int argc, char *argv[]) {
  int n;
  float root;
  printf("Enter a number:\n");
  scanf("%d", &n);
  root = getSquareRoot(n, getIntegerofRoot(n), 0.001);
  printf("\nSquare root of %d is %.3f\n", n, root);
  return 0;
}

int getIntegerofRoot(int n) {
  if (n == 2) {
    return 1;
  }
  int i;
  for (i = 0; i < n; i++) {
    if (n - i * i < 0) {
      i -= 1;
      break;
    } else if (n - i * i == 0)
      break;
  }
  return i;
}
float getSquareRoot(int n, int a, float E) {
  float root, offset = n - (a * a);
  if (offset == 0) {
    return a;
  }
  root = a + (offset / a);
  while (absoluteValue(root * root - n) > E) {
    root = a + offset / (a + root);
  }
  return root;
}

float absoluteValue(float num) {
  if (num >= 0) {
    return num;
  } else {
    return -num;
  }
}
