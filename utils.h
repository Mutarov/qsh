#ifndef utils_h
#define utils_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int builtin_cd(char **args);
int builtin_exit(char **args);

/* Structions */
typedef int (*builtin_func)(char **args);

typedef struct {
  const char *name;
  builtin_func func;
  const char *help;
} builtin_command;

/* Global Variables */
int status;
builtin_command builtins[] = {{"cd", builtin_cd, "cd <dir> - change directory"},
                              {"exit", builtin_exit, "exit - exit the shell"},
                              {NULL, NULL, NULL}};

int is_builtin(char *cmd) {
  for (int i = 0; builtins[i].name; i++) {
    if (strcmp(cmd, builtins[i].name) == 0) {
      return 1;
    }
  }
  return 0;
}

int execute_builtin(char **args) {
  for (int i = 0; builtins[i].name; i++) {
    if (strcmp(args[0], builtins[i].name) == 0) {
      return builtins[i].func(args);
    }
  }
  return 0;
}

int builtin_cd(char **args) {
  if (args[1] == NULL) {
    fprintf(stderr, "cd: missing argument\n");
  } else {
    if (chdir(args[1])) {
      perror("cd");
    }
  }
  return 1;
}

int builtin_exit(char **args) {
  exit(0);
  return 0;
}

/* Execution */
void execute(char **args) {
  pid_t pid = fork();
  if (pid == -1) {
    perror("qsh: fork failed");
    exit(1);
  } else if (pid == 0) {
    if (execvp(args[0], args) == -1) {
      perror("qsh: execvp failed");
      exit(1);
    }
  } else {
    waitpid(pid, &status, 0);
  }
}

#endif
