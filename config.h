/* This is config file for qsh */
/* yeah i love suckless.org */

#include "utils.h"

#include <stdio.h>
#include <unistd.h>

#define RESET "\033[0m"
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define PURPLE "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[47m"

static char *greet[] = {"fastfetch", NULL};

void greeting() { execute(greet); }

void prompt() {
  char cwd[1024];
  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    printf(CYAN "%s" RESET " $!> ", cwd);
  } else {
    printf("$ ");
  }
}
