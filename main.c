/* ----------
 * File: main.c
 * Author: fedya
 * Description: Shell on C(i look on dash when wrote it)
 * DaSH's GitHub: github.com/danishprakash/dash
 */

/* config */
#include "config.h"
#include "utils.h"

/* utils */
#include <utils.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

/* Some defines */
#define MAX_CMD_SIZE 1024
#define MAX_ARGS_SIZE 64
#define TOKEN_DELIMITER " \t\r\n\a" /* Thanks to DaSH */

int main() {
  greeting();

  char cmd[MAX_CMD_SIZE];
  while (1) {
    prompt();
    if (fgets(cmd, sizeof(cmd), stdin) == NULL) {
      perror("\nqsh: cannot fgets or you type EOF");
      exit(1);
    }
    cmd[strcspn(cmd, "\n")] = '\0'; /* Delete \n in end */

    if (strlen(cmd) == 0) {
      continue;
    }

    char *args[MAX_ARGS_SIZE] = {cmd, NULL};
    int i = 0;
    char *token = strtok(cmd, TOKEN_DELIMITER);

    while (token != NULL && i < MAX_ARGS_SIZE - 1) {
      args[i++] = token;
      token = strtok(NULL, TOKEN_DELIMITER);
    }
    args[i] = NULL;

    /* Builtins logic */
    if (is_builtin(args[0])) {
      execute_builtin(args);
      continue;
    }

    execute(args);
  }
  return 0;
}
