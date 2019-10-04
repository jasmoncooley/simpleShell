#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LINE_LEN 1024
#define MAX_COMMAND_LINE_ARGS 128

// [N]o [A]rguments [SH]ell, by Gerald [Nash] @02854836
char prompt[] = "nash > ";
char delimiters[] = " \t\r\n";
char **environ;

int main() {
    char command_line[MAX_COMMAND_LINE_LEN];
    char *arguments[MAX_COMMAND_LINE_ARGS];
    
    while (true) {
        printf("%s", prompt);
        fflush(stdout);
        
        if ((fgets(command_line, MAX_COMMAND_LINE_LEN, stdin) == NULL) && ferror(stdin)) {
            fprintf(stderr, "fgets error");
            exit(0);
        }
        
        if (feof(stdin)) {
            printf("\n");
            fflush(stdout);
            fflush(stderr);
            return 0;
        }

        int i = 0;
        arguments[i] = strtok(command_line, delimiters);
        while (arguments[i] != NULL)
        {
          arguments[i] = strtok(command_line, delimiters);
          i++;
        }
        int isChild = fork();
        if(isChild == 0) {
          if(execve(arguments[0], arguments, environ) == -1){
            printf("%s: Command not found.\n", arguments[0]);
            return -1;
          }
          return 0;
        } else if(isChild > 0){
          wait(NULL);
        } else {
          return -1;
        }
    }
    return -1;
}
