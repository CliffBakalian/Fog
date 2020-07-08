#include "config.h"

Config* load_data(){
  Config *config;
  config = malloc(sizeof(Config));
  return config;
}

char *get_config_input(int use){
  int size = 32;
  int inc = size;
  int len = 0;
  char in = '\0';
  char *temp = NULL;
  char *input = malloc(sizeof(char)*size);
  input[0] = '\0';
  if(use == 1)
    in = getch();
  else
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
      if(use == 1)
        in = getch();
      else
        scanf("%c", &in);
    }
    else
      break;
  }
  if (len == 0){
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

int getPolicy(){
  char *mode;

  while(1){
    printf("1) Trusted\t2) Secure\n(1 by default): ");
    mode = get_config_input(0);
    if(mode == NULL)
      return 1;
    mode = string_trim(mode);
    if(strlen(mode) == 0 || mode[0] == 49 || mode[0] == 116)
      return 1;
    else if(mode[0] == 50||mode[0] == 115)
      return 2;
    else
      printf("Mode not valid\n");  
  } 
}

void fog_init(){
  char *username;
  char *password;
  char *domain;
  char *sshkey;
  int policy;

  if (mkdir(".fog",0755)){
    if(errno == EEXIST){
      printf("Error: Already a Fog directory\n",EEXIST);
      exit(EXIT_FAILURE);
      return;
    }else if (errno == EACCES){
      printf("Error: permission denied\n");
      exit(EXIT_FAILURE);
      return;
    }
  }
  policy = getPolicy();
  if(policy == 1){
    printf("Username: ");
    username = get_config_input(0);
    printf("password: ");
    password = get_config_input(1);
    if(username== NULL){
      username= malloc(sizeof(char));
      username[0] = '\0';
    }
    if(password== NULL){
      password = malloc(sizeof(char));
      password[0] = '\0';
    }
  }
  else{
    username = malloc(sizeof(char));
    password = malloc(sizeof(char));
    username[0] = '\0';
    password[0] = '\0';
  }
  printf("\nDomain name or IP Address: ");
  domain = get_config_input(0);
  if(domain == NULL){
    domain = malloc(sizeof(char));
    domain[0] = '\0';
  }
  printf("path to ssh key: ");
  sshkey = get_config_input(0);
  if(sshkey== NULL){
    sshkey = malloc(sizeof(char));
    sshkey[0] = '\0';
  }
  //need to encrypt password first
  //password = encrypt(password);
  FILE *conf = fopen(".fog/config", "w"); 
  fprintf(conf,"MODE: %d\n",policy); 
  fprintf(conf,"USER: %s\n",username); 
  fprintf(conf,"PASS: %s\n",password); 
  fprintf(conf,"DEST: %s\n",domain); 
  fprintf(conf,"KEY : %s",sshkey); 
  fclose(conf);
}
