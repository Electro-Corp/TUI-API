#include <stdio.h>
#include "tui.h"
int main(void) {
  struct menu mainMen = {"Main Menu","Read","Write","Quit"};
  while(1){
    int re = createMenu(mainMen);
    if(re == 2)
      exit(0);
    else if(re == 0){
      char* fileName = inputBox("File Name:");
      FILE* fp = fopen(fileName,"r");
      if(!fp){
        printf("File %s does not exist!\n",fileName);
        exit(1);
      }
      char buffer[10000];
      fread(buffer,sizeof(buffer),1,fp);
      //printf("%s\n",buffer);
      alert("File",buffer);
    }
    else if(re == 1){
      char* fileName = inputBox("File Name:");
      FILE* fp = fopen(fileName,"w");
      if(!fp){
        printf("File %s does not exist!\n",fileName);
        exit(1);
      }
      char* toAdd = inputBox("Text to append: ");
      fwrite(toAdd,1, sizeof(toAdd)*30,fp);
    }
  }
  return 0;
}