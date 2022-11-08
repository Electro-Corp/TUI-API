#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
struct menu {
  char *title;
  char *option0;
  char *option1;
  char *option2;
};
int createMenu(struct menu m) {
  struct termios info;
  tcgetattr(0, &info);
  info.c_lflag &= ~ICANON;
  info.c_cc[VMIN] = 1;
  info.c_cc[VTIME] = 0;
  tcsetattr(0, TCSANOW, &info);
  int option = 0;
  char c;
  while (1) {
    c = NULL;
    system("clear");
    while (c == NULL) {
      printf("[%s]\n", m.title);
      switch (option) {
      case 0:
        printf("[==%s==]\n", m.option0);
        printf("--%s--\n", m.option1);
        printf("--%s--\n", m.option2);
        break;
      case 1:
        printf("--%s--\n", m.option0);
        printf("[==%s==]\n", m.option1);
        printf("--%s--\n", m.option2);
        break;
      case 2:
        printf("--%s--\n", m.option0);
        printf("--%s--\n", m.option1);
        printf("[==%s==]\n", m.option2);
        break;
      }
      c = getchar();
    }
    if (c == 'w' && option != 0) {
      option--;
    }
    if (c == 's' && option != 2) {
      option++;
    }
    if (c == '\n') {
      break;
    }
  }
  system("clear");
  return option;
}
char *inputBox(char *dialog) {
  char *input = malloc(100);
  int index = 0;
  char c;
  while (c != '\n') {
    c = NULL;
    system("clear");
    if (strlen(dialog) > strlen(input)) {
      for (int i = 0; i < strlen(dialog) / 2; i++) {
        printf("=");
      }
      printf("%s", dialog);
      for (int i = 0; i < strlen(dialog) / 2; i++) {
        printf("=");
      }
    } else {
      for (int i = 0; i < strlen(input) / 2; i++) {
        printf("=");
      }
      printf("%s", dialog);
      for (int i = 0; i < strlen(input) / 2; i++) {
        printf("=");
      }
    }
    printf("\n");
    for (int i = 0; i < strlen(input) / 2; i++) {
      printf("-");
    }
    printf("%s", input);
    for (int i = 0; i < strlen(input) / 2; i++) {
      printf("-");
    }
    c = getchar();
    if (c != 8 && c != 10) {
      input[index++] = c;
    } else {
      input[index--] = '\0';
      index--;
    }
  }
  system("clear");
  return input;
}
void alert(char *title, char *body) {
  system("clear");
  for (int i = 0; i < strlen(title) / 2; i++) {
    printf("=");
  }
  printf(title);
  for (int i = 0; i < strlen(title) / 2; i++) {
    printf("=");
  }
  printf("\n");
}