#include <stdio.h>

int main(int argc, char *argv[]) {
  int size, i, j, sub;
  // Input
  printf("Enter number of elements to be stored in the array:\n");
  scanf("%d", &size);
  int arr[size];
  printf("Enter the elements of the array:\n");
  for (i = 0; i < size; i++) {
    printf("element - %d: ", i);
    scanf("%d", &arr[i]);
  }

  // Sort
  for (i = 0; i < size; i++) {
    for (j = i + 1; j < size; j++) {
      if (arr[j] > arr[i]) {
        sub = arr[i];
        arr[i] = arr[j];
        arr[j] = sub;
      }
    }
    printf("%d ", arr[i]);
  }
  printf("\n");
  return 0;
}
