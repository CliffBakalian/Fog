#ifndef FOG_CONFIGRE_H
#define FOG_CONFIGRE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include "utilities.h"

struct Config{
  const char *username;
  const char *password;
  const char *keypath;
  const char *domain;
  int mode;
};

typedef struct Config Config;

void fog_init();

#endif
