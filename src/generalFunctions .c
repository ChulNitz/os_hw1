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
printf("hw1shell: %s failed. errno: %d\n", sys_call, errno); 
return -1;
}

void add_child(child_process* child_list, pid_t pid, char* raw_cmd, int* current_childs_count){
    child_list[*current_childs_count].pid = pid;
    strcpy(child_list[*current_childs_count].user_cmd, raw_cmd);
    *current_childs_count += 1;
}

void remove_child(child_process* child_list, pid_t pid, int* current_childs_count){
    for (int i=0; i<*current_childs_count; ++i){
        if (child_list[i].pid == pid){
            child_list[i].pid = 0;
            child_list[i].user_cmd[0] = '\0';
            *current_childs_count -= 1;
        }
    }
}