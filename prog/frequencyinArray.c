#include <stdio.h>

int main(int argc, char *argv[]) {
  int size, i, j, count, x = 0;
  printf("Enter number of elemetns to be stored in the array:\n");
  scanf("%d", &size);
  int arr[size], check[size];
  printf("Enter the elements of the array:\n");
  for (i = 0; i < size; i++) {
    check[i] = 0;
    scanf("%d", &arr[i]);
  }
  printf("Frequencies of elements in array are:\n");
  for (i = 0; i < size; i++) {
    count = 0;
    x = 0;
    for (j = 0; j < size; j++) {
      if (arr[i] == arr[j]) {
        count++;
      }
    }
    for (j = 0; j < size; j++) {
      if (check[j] == arr[i]) {
        x++;
      }
    }
    if (x == 0) {
      printf("%d occurs %d times\n", arr[i], count);
      check[i] = arr[i];
    }
  }
  printf("\n");
  return 0;
}
