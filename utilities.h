#ifndef FOG_UTIL_H
#define FOG_UTIL_H
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int getch(void);
char *string_trim(char *input);
#endif
