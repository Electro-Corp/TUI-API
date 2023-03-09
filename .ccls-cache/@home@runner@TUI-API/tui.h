/*
  Small TUI header for linux systems
*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

int WIDTH = 10;
int HEIGHT = 19;
struct menu {
  char *title;
  char *option0;
  char *option1;
  char *option2;
};
int createMenu(struct menu m) {
  printf("\e[?25l");
  struct termios info;
  tcgetattr(0, &info);
  info.c_lflag &= ~ICANON;
  info.c_cc[VMIN] = 1;
  info.c_cc[VTIME] = 0;
  tcsetattr(0, TCSANOW, &info);
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  WIDTH = w.ws_col;
  HEIGHT = w.ws_row;
  int option = 0;
  char c;
  printf("\e[97m\e[40m");
  while (1) {
    c = NULL;
    system("clear");
    while (c == NULL) {
      printf("[%s]\n", m.title);
      // for(int y = 0; y < HEIGHT; y++){
      //   for(int x = 0; x < WIDTH; x++){
      //     if(y == (HEIGHT/2) - 3 && x < (WIDTH/2) - strlen(m.title) / 2){
      //       printf("[%s]", m.title);
      //       x+=strlen(m.title)+2;
      //     }else if(y == (HEIGHT/2) - 2 && x < (WIDTH/2) - strlen(m.option0) / 2){
      //       if(option == 0){
      //         printf("[==%s==]", m.option0);
      //         x+= strlen(m.option0)+6;
      //       }else{
      //         printf("==%s==", m.option0);
      //         x+= strlen(m.option0)+4;
      //       }
      //     }else if(y == (HEIGHT/2) - 1){
      //       if(option == 1){
      //         printf("[==%s==]", m.option1);
      //         x+= strlen(m.option1)+6;
      //       }else{
      //         printf("==%s==", m.option1);
      //         x+= strlen(m.option1)+4;
      //       }
      //     }
      //     else if(y == (HEIGHT/2)){
      //       if(option == 2){
      //         printf("[==%s==]", m.option2);
      //         x+= strlen(m.option2)+6;
      //       }else{
      //         printf("==%s==", m.option2);
      //         x+= strlen(m.option2)+4;
      //       }
      //     }else{
      //       printf(" ");
      //     }
      //   }
      //   printf("\n");
      // }
      switch (option) {
      case 0:
        printf("[==%s==]\n", m.option0);
        printf("|--%s--|\n", m.option1);
        printf("|--%s--|\n", m.option2);
        break;
      case 1:
        printf("|--%s--|\n", m.option0);
        printf("[==%s==]\n", m.option1);
        printf("|--%s--|\n", m.option2);
        break;
      case 2:
        printf("|--%s--|\n", m.option0);
        printf("|--%s--|\n", m.option1);
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
char *inputBox(char *dialog, int letBlash, char esckey) {
  system("clear");
  //
  int topLine = 0;
  //printf("%s\n", body);
  char* key = (char*)malloc(sizeof(char)*1000);
  if(key[0] == '\n')
      key = "Backspace";
  if(key[0] == '\t')
      key = "Tab";
  
  int bot = 0;
  int rn = -1;
  char c;
  char* g = malloc(sizeof(char)*100);
  int gc = 0;
  while ((c != '\n' && letBlash == 0) || c != esckey) {
    c = NULL;
    system("clear");
    rn = -1;
    int y = 0;
    while(y < topLine){
      if(g[rn++] == '\n')
        y++;
    }
    for (int i = 0; i < (WIDTH / 2) - strlen(dialog) /2; i++) {
    printf("=");
    }
    printf("%s",dialog);
    for (int i = 0; i < (WIDTH / 2) - strlen(dialog) /2; i++) {
      printf("=");
    }
    printf("\n");
    for(int y = 1; y < HEIGHT - 1; y++){
      if(y != 1)printf("\n");
      for(int x = 0; x < WIDTH; x++){
        rn++;
        if(g[rn] == '\n'){
          break;
        } 
        printf("%c",g[rn]);
      }
    }
    printf("\e[37m\e[41m");
    printf("\nLine = %d | Press %c to exit",topLine,key);
    printf("\e[97m\e[40m");
    c = getchar();
    if(c != '\n' || letBlash == 1)
      g[gc++] = c;
  }
  return g;
}
void alert(char *title, char *body) {
  system("clear");
  for (int i = 0; i < strlen(body) / 2; i++) {
    printf("=");
  }
  printf(title);
  for (int i = 0; i < strlen(body) / 2; i++) {
    printf("=");
  }
  printf("\n");
  //
  int topLine = 0;
  //printf("%s\n", body);
  int bot = 0;
  int rn = -1;
  char c;
  while (c != '\n') {
    c = NULL;
    system("clear");
    rn = -1;
    int y = 0;
    while(y < topLine){
      if(body[rn++] == '\n')
        y++;
    }
    rn--;
    for (int i = 0; i < (WIDTH / 2) - strlen(title) /2; i++) {
    printf("=");
    }
    printf(title);
    for (int i = 0; i < (WIDTH / 2) - strlen(title) /2; i++) {
      printf("=");
    }
    printf("\n");
    for(int y = 1; y < HEIGHT - 1; y++){
      if(y != 1)printf("\n");
      for(int x = 0; x < WIDTH; x++){
        rn++;
        if(body[rn] == '\n'){
          break;
        }
        printf("%c",body[rn]);
      }
    }
    printf("\e[37m\e[41m");
    printf("\nLine = %d | Chars in text = %d",topLine,strlen(body));
    printf("\e[97m\e[40m");
    c = getchar();
    if(c == 's')
        topLine++;
    if(c == 'w'){
      if(topLine != 0)
        topLine--;
    }
  }
  getchar();
}