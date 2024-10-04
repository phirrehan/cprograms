#include <stdio.h>
void printBytes(void *, unsigned long long);

int main(int argc, char *argv[]) {
  int var;
  printf("Enter an integer: ");
  scanf("%d", &var);
  printBytes(&var, sizeof(var));
  return 0;
}

void printBytes(void *ptr, unsigned long long size) {
  long long i, j;
  char byte, bit;
  for (i = 0; i < size; i++) {
    byte = ((char *)ptr)[i];
    for (j = 7; j >= 0; j--) {
      bit = (byte >> j) & 1;
      printf("%hhd", bit);
    }
    printf(" ");
  }
  printf("\n");
}
