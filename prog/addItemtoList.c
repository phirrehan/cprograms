#include <stdio.h>
#include <stdlib.h>
struct list {
  int *data;
  int size;
  int numItems;
};

void addItemtoList(struct list *myList, int Item);

int main() {
  struct list myList;
  myList.size = 10;
  myList.numItems = 0;
  myList.data = malloc(myList.size * sizeof(int));
  if (myList.data == NULL) {
    printf("Memory Allocation failed.\n");
    return 1;
  }
  int amount;
  printf("Enter number of integers to add to list:\n");
  scanf("%d", &amount);
  for (int i = 0; i < amount; i++) addItemtoList(&myList, i + 1);
  printf("Items inside list are:\n");
  for (int j = 0; j < myList.size; j++) printf("%d\n", myList.data[j]);
  free(myList.data);
  myList.data = NULL;
  return 0;
}

void addItemtoList(struct list *myList, int Item) {
  if (myList->numItems == myList->size) {
    myList->size += 10;
    myList->data = realloc(myList->data, myList->size * sizeof(int));
  }
  myList->data[myList->numItems] = Item;
  myList->numItems++;
}
