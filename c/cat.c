#include <stdio.h>
#include <string.h>
#include <unistd.h>

char cwd[1024];
void concatenate(char *, int);
int strRead(char *, int);

int main(int argc, char *argv[]) {
  int x;
  char path[1024];
  if (argc == 1) {
    printf("No arguments provided\n");
    return 1;
  }
  for (int i = 1; i < argc; i++) {
    strcpy(path, argv[i]);
    concatenate(path, sizeof(path));
    x = strRead(path, i);
    if (x != 0) {
      return 1;
    }
  }
  return 0;
}

int strRead(char *pathtoFile, int index) {
  FILE *fptr;
  fptr = fopen(pathtoFile, "r");
  char line[1024];
  if (fptr != NULL)  // When a file does not exist fptr contains NULL
  {
    while (fgets(line, 1024, fptr)) {
      printf("%s", line);
    }
    return 0;
  } else {
    printf("\nFile with argument number %d does not exist.\n", index);
    return 1;
  }
  fclose(fptr);
}

void concatenate(char *path, int size) {
  int i;
  char str[1024] = "/home/rehan";
  if (path[0] == '~' && path[1] == '/') {
    path[0] = 0;
    for (i = 0; i < size; i++) {
      path[i] = path[i + 1];
      if (path[i + 1] == 0) break;
    }
    strcat(str, path);
    strcpy(path, str);

  } else if (path[0] == '.' && path[1] == '/') {
    getcwd(cwd, sizeof(cwd));
    path[0] = 0;
    for (i = 0; i < size; i++) {
      path[i] = path[i + 1];
      if (path[i + 1] == 0) break;
    }
    strcat(cwd, path);
    strcpy(path, cwd);

  } else if (path[0] == '.' && path[1] == '.' && path[2] == '/') {
    getcwd(cwd, sizeof(cwd));
    int lastIndex = strlen(cwd);
    for (i = lastIndex; i >= 0; i--) {
      cwd[i] = 0;
      if (cwd[i - 1] == '/') {
        cwd[i - 1] = 0;
        break;
      }
    }
    path[0] = path[1] = 0;
    strcat(cwd, path);
    strcpy(path, cwd);

  } else if (path[0] != '/') {
    getcwd(cwd, sizeof(cwd));
    strcat(cwd, "/");
    strcat(cwd, path);
    strcpy(path, cwd);
  }
}
