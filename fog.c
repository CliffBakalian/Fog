#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fog.h"


int main(int argc, char** argv){
  if(strcmp(argv[1], "init") == 0)
    fog_init();
  return(0);
}

