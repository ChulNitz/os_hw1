#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "generalFunctions.h"
#include "shellDefs.h"

//parsing command line input
char **split_cmd_line (char* input_cmd){
    int index = 0;
    char **tokens = malloc(INPUT_BUFFER_LEN * sizeof(char*)); //TODO re-think malloc
    char *token;

    if (!tokens) { 
        fprintf(stderr, "lsh: allocation error\n");
        exit(-1);
    }

    token = strtok(input_cmd, " \n");
    while (token != NULL) {
        tokens[index] = token;
        index++;

        token = strtok(NULL,  " \n");
    }
    tokens[index] = NULL; //args list must be finished with NULL
    return tokens;
}

//handling error in system call
int system_call_err(char* sys_call){
printf("hw1shell: %s failed, errno is %d\n", sys_call, errno); 
return -1;
}