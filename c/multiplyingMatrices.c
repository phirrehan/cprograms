#include <stdio.h>

void displayMatrix(int *, int, int);
void getMatrix(int *, int, int);

int main(int argc, char *argv[]) {
  int r1, r2, c1, c2, i, j, k, dotprod;

  // Input
  printf("Enter rows and columns of first matrix:\n");
  scanf("%d %d", &r1, &c1);
  printf("Enter rows and columns of second matrix:\n");
  scanf("%d %d", &r2, &c2);
  if (c1 != r2) {
    printf(
        "Multiplication is not defined. Columns of first matrix must be "
        "equivalent to Rows of second matrix.\n");
    return 1;
  }
  int mat1[r1][c1], mat2[r2][c2], prod[r1][c2];
  printf("Enter elements of first matrix:\n");
  getMatrix(&mat1[0][0], r1, c1);
  printf("Enter elements of second matrix:\n");
  getMatrix(&mat2[0][0], r2, c2);

  // Displaying both matrices
  printf("The first matrix is:\n\n");
  displayMatrix(&mat1[0][0], r1, c1);
  printf("\nThe second matrix is:\n\n");
  displayMatrix(&mat2[0][0], r2, c2);

  // Computing product of matrices
  for (i = 0; i < r1; i++) {
    for (j = 0; j < c2; j++) {
      dotprod = 0;
      for (k = 0; k < c1; k++) {
        dotprod += mat1[i][k] * mat2[k][j];
      }
      prod[i][j] = dotprod;
    }
  }
  // Printing Product
  printf("\nThe Product of matrices is:\n\n");
  displayMatrix(&prod[0][0], r1, c2);
  printf("\n");
  return 0;
}

void getMatrix(int *ptr, int n, int m) {
  int i, j;
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      printf("Element is Row %d and Column %d is: ", i, j);
      scanf("%d", (ptr + i * m + j));
    }
  }
}

void displayMatrix(int *ptr, int n, int m) {
  int i, j;
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      printf("%d\t", *(ptr + i * m + j));
    }
    printf("\n");
  }
}
