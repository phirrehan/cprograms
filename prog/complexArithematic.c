#include <stdio.h>

struct cmp {
  float real;
  float imm;
};
enum bool {
  FALSE,
  TRUE,
};

// Function Declarations
void printMenu(void);
void wait(void);
void printComplexNumber(struct cmp *, const char *);
void inputComplexNumber(struct cmp *);
void getInput(struct cmp *, void (*)(struct cmp *));
void getTwoInputs(struct cmp *, struct cmp *, void (*)(struct cmp *));
struct cmp subComplexNumbers(struct cmp *, struct cmp *);
struct cmp addComplexNumbers(struct cmp *, struct cmp *);
struct cmp multComplexNumbers(struct cmp *, struct cmp *);
struct cmp divideComplexNumbers(struct cmp *, struct cmp *,
                                struct cmp (*)(struct cmp *),
                                struct cmp (*)(struct cmp *, struct cmp *));
struct cmp conjugateComplexNumber(struct cmp *);

int main(int argc, char *argv[]) {
  struct cmp z1, z2, w;
  int x = TRUE, dump;
  int inputNum;
  printf("\e[?1049h");
  while (x == TRUE) {
    printf("\e[2J");  // Clear screen
    printf("\e[H");   // Move cursor to home position
    printMenu();
    scanf("%d", &inputNum);
    printf("\n_________________________________________________________\n");
    switch (inputNum) {
      case 1:

        getTwoInputs(&z1, &z2, inputComplexNumber);
        w = addComplexNumbers(&z1, &z2);
        printComplexNumber(&w, "Sum");
        wait();
        break;

      case 2:

        getTwoInputs(&z1, &z2, inputComplexNumber);
        w = subComplexNumbers(&z1, &z2);
        printComplexNumber(&w, "Difference");
        wait();
        break;

      case 3:

        getTwoInputs(&z1, &z2, inputComplexNumber);
        w = multComplexNumbers(&z1, &z2);
        printComplexNumber(&w, "Product");
        wait();
        break;

      case 4:

        getTwoInputs(&z1, &z2, inputComplexNumber);
        w = divideComplexNumbers(&z1, &z2, conjugateComplexNumber,
                                 multComplexNumbers);
        printComplexNumber(&w, "Division");
        wait();
        break;

      case 5:
        getInput(&z1, inputComplexNumber);
        w = conjugateComplexNumber(&z1);
        printComplexNumber(&w, "Cojugate");
        wait();
        break;

      case 6:

        x = FALSE;
        printf("\e[?1049l");
        break;

      default:

        printf("Invalid Number. Please Try Again!");
    }
  }
  return 0;
}

struct cmp addComplexNumbers(struct cmp *z1, struct cmp *z2) {
  struct cmp w;
  w.real = z1->real + z2->real;
  w.imm = z1->imm + z2->imm;
  return w;
}
struct cmp subComplexNumbers(struct cmp *z1, struct cmp *z2) {
  struct cmp w;
  w.real = z1->real - z2->real;
  w.imm = z1->imm - z2->imm;
  return w;
}
struct cmp multComplexNumbers(struct cmp *z1, struct cmp *z2) {
  struct cmp w;
  w.real = z1->real * z2->real - z1->imm * z2->imm;
  w.imm = z1->real * z2->imm + z1->imm * z2->real;
  return w;
}
struct cmp divideComplexNumbers(struct cmp *z1, struct cmp *z2,
                                struct cmp (*callback1)(struct cmp *),
                                struct cmp (*callback2)(struct cmp *,
                                                        struct cmp *)) {
  struct cmp conj = callback1(z2), w = callback2(z1, &conj);
  w.real = w.real / (z2->real * z2->real + z2->imm * z2->imm);
  w.imm = w.imm / (z2->real * z2->real + z2->imm * z2->imm);
  return w;
}
struct cmp conjugateComplexNumber(struct cmp *z) {
  struct cmp conjugate;
  conjugate.real = z->real;
  conjugate.imm = -z->imm;
  return conjugate;
}
void inputComplexNumber(struct cmp *z) {
  printf("Input the Real part: ");
  scanf("%f", &(z->real));
  printf("Input the Immaginary part: ");
  scanf("%f", &(z->imm));
  printf("Complex number is %.3f + %.3fi\n", z->real, z->imm);
}
void printComplexNumber(struct cmp *z, const char *str) {
  if (z->imm < 0)
    printf("\n\nThe %s of Complex Numbers is %.3f - %.3fi\n", str, z->real,
           -z->imm);
  else
    printf("\n\nThe %s of Complex Numbers is %.3f + %.3fi\n", str, z->real,
           z->imm);
}
void printMenu() {
  printf("            Arithematic on Complex Numbers");
  printf("\n_________________________________________________________\n");
  printf("Choose an Operation\n");
  printf("1) Add Numbers\n");
  printf("2) Subtract Numbers\n");
  printf("3) Multiply Numbers\n");
  printf("4) Divide Numbers\n");
  printf("5) Take Conjugate\n");
  printf("6) Exit Program\n\n");
  printf("Enter An Option: ");
}
void getTwoInputs(struct cmp *z1, struct cmp *z2,
                  void (*callback)(struct cmp *)) {
  printf("\nEnter the First Complex Number:\n\n");
  callback(z1);
  printf("\nEnter the Second Complex Number:\n\n");
  callback(z2);
}
void getInput(struct cmp *z, void (*callback)(struct cmp *)) {
  printf("Enter Complex number:\n");
  callback(z);
}
void wait() {
  // Clearing stdin buffer for trailing '\n'
  // Add an OR condition for checking EOF character when working with files.
  char dump[10] = {0};
  while (dump[0] != '\n') {
    dump[0] = getchar();
  }

  printf("\n\nPress any key to continue...\n");
  fgets(dump, sizeof(dump), stdin);
}
