#include "utilities.h"

//taken from https://stackoverflow.com/questions/3276546/how-to-implement-getch-function-of-c-in-linux
int getch(void){
    struct termios oldattr, newattr;
    int ch;

    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

char *string_trim(char *input){
  int len = 0;
  int count = 0;
  int start = 0;
  int pos = 0;
  char *trimmed;
  len = strlen(input);
  trimmed = malloc(sizeof(char) * len + 1);
  for(pos = 0; pos < len; pos++){
    if(input[pos] != 32){
      break;
    }
    count = count + 1;
  }
  start = count;
  for(pos = len-1; pos>=0; pos--){
    if(input[pos] != 32){
      break;
    }
    count = count + 1;
  }
  len = len - count;
  trimmed = malloc(sizeof(char) * len);
  for(pos = start; pos < start + len; pos++){
    trimmed[pos] = input[pos];
  }
  free(input);
  return trimmed;
}
