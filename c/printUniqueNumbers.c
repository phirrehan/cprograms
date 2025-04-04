#include <stdio.h>

int main(int argc, char *argv[]) {
  int size, i, j, x, count = 0;
  printf("Enter number of elemetns to be stored in the array:\n");
  scanf("%d", &size);
  int arr[size];
  printf("Enter the elements of the array:\n");
  for (i = 0; i < size; i++) {
    scanf("%d", &arr[i]);
  }
  printf("Unique numbers in array are:\n");
  for (i = 0; i < size; i++) {
    x = 0;
    for (j = 0; j < size; j++) {
      if (i != j) {
        if (arr[i] == arr[j]) {
          x++;
          break;
        }
      }
    }
    if (x == 0) {
      count++;
      printf("%d ", arr[i]);
    }
  }
  printf("\nTotal number of unique elements are: %d\n", count);
  return 0;
}
