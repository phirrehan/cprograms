#include <stdio.h>
int main() {
  int i, j, x = 1, center, length;
  while (x == 1) {
    printf("Enter height of diamond:\n");
    scanf("%d", &length);
    // Check if length is even or not.
    if (length % 2 == 0)
      printf("Please enter an odd number.\n");
    else
      x = 0;
  }
  center = length / 2 + 1;
  // Writing upper half of diamond.
  for (i = 0; i <= length; i += 2) {
    for (j = center; j > 1 + i / 2; j--) {
      printf(" ");  // Writing spaces
    }
    for (j = 0; j <= i; j++) {
      printf("*");  // Writing asterisks.
    }
    printf("\n");
  }
  // Writing bottom half of diamond.
  for (i = length - 1; i > 1; i -= 2) {
    for (j = center; j > i / 2; j--) {
      printf(" ");  // Writing spaces
    }
    for (j = 1; j < i; j++) {
      printf("*");  // Writing asterisks.
    }
    printf("\n");
  }
  return 0;
}
