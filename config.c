#include "config.h"

Config* load_data(){
  Config *config;
  config = malloc(sizeof(Config));
  return config;
}

char *get_config_input(){
  int size = 32;
  int inc = size;
  int len = 0;
  char in = '\0';
  char *temp = NULL;
  char *input = malloc(sizeof(char)*size);
  input[0] = '\0';
  scanf("%c", &in);
  while(!feof(stdin)){
    if (32 <= in && in <= 126){
      if (len == size-1){
        temp = malloc(sizeof(char)*(size+inc));
        if( inc != 1)
          inc = inc/2;
        size = size+inc;
        strncpy(temp, input, len);
        free(input);
        input = temp;
        temp = NULL;
      }

      input[len] = in;
      input[len+1] = '\0';
      len = len + 1;
      scanf("%c", &in);
    }
    else
      break;
  }
  if (len == 0){
    printf("Not Given\n");
    return NULL;
  }
  len = strlen(input);
  temp = malloc(sizeof(char)*(len+1));
  strncpy(temp, input, len);
  temp[len] = '\0';
  free(input);
  input = temp;
  temp = NULL;
  return input;
}

void fog_init(){
  int errnum;
  char *username;
  char *password;
  char *domain;
  char *sshkey;

  if (mkdir(".fog",0755))
    if(errno == EEXIST)
      printf("Error: Already a Fog directory\n",EEXIST);
    else if (errno == EACCES)
      printf("Error: permission denied\n");
  else{ 
    printf("Username: ");
    username = get_config_input();
    printf("password: ");
    password = get_config_input();
    printf("%s\n%s\n",username,password);
    printf("Domain name or IP Address: ");
    domain = get_config_input();
    printf("path to ssh key: ");
    sshkey = get_config_input();
  }
}
