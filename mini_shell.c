#define MAX 100
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

char *env;
char *token;

int main(){

    char command[MAX],new_command[MAX],env2[MAX];
    char *args[MAX];
    int pid, stat;

    while (true){

        printf("$ ");
        fgets(command, MAX,stdin);
        command[strlen(command) - 1] = 0; // remove \n

        if (strcmp(command, "leave") == 0) {
           exit(0); //successful leave
        }
        int i = 0;
        char *arg = strtok(command, " \t");
        while (arg != NULL && i < MAX - 1) {
            args[i++] = arg;
            arg = strtok(NULL, " \t");
        }
        args[i] = NULL;

        if ((pid = fork()) == 0) {
            // child
            env = getenv("PATH");
            strcpy(env2, env);
            token = strtok(env2, ":");
            while (token != NULL) {
                strcpy(new_command, token);
                strcat(new_command, "/");
                strcat(new_command, args[0]); //appends only the "command" part to the path
                execv(new_command, args);
                token = strtok(NULL, ":");
            }
            printf("command execution was unsuccessful\n");
            exit(1);
        } else {
            // parent
            wait(&stat);
        }
    }

    return 0;
}
