// imports
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include "handleInternal.h"
#include "handleExternal.h"
#include "generalFunctions.h"
#include "shellDefs.h"

// global variables
char user_input[INPUT_BUFFER_LEN+1];
char raw_input[INPUT_BUFFER_LEN+1];
char *cmd_name;
char *cmd_params;
char **cmd_args;
const char internal_cmds[NUM_INTERNAL_CMDS][MAX_CMD_LEN] = {"cd", "jobs", "exit"};


void get_input(char *pUser_input){
    fgets(pUser_input, INPUT_BUFFER_LEN, stdin);
}

void run_shell(){

    child_process child_list[MAX_CHILDS] = {0};
    int current_childs_count = 0;

    while (TRUE){

        int is_internal = 0;
        
        printf("hw1shell$: ");
        get_input(user_input);

        // check if the user entered an empty line
        if (user_input[0] == '\n'){
            continue;
        }

        strcpy(raw_input, user_input);
        cmd_args = split_cmd_line (user_input);

        // check if the cmn was exit -  if so, exit the shell and free all the allocated memory
        if (strcmp(cmd_args[0], internal_cmds[2]) == 0){
            free(cmd_args);
            execute_exit(child_list, &current_childs_count);
        }

        for (int i=0; i<NUM_INTERNAL_CMDS; ++i){
            if (!strcmp(cmd_args[0], internal_cmds[i])){
                execute_internal(cmd_args, i, child_list, &current_childs_count);
                is_internal = 1;
            }
        }

        if (is_internal){
            free(cmd_args);
            continue; // finish the loop
        }

        else {
            execute_external(cmd_args, child_list, raw_input, &current_childs_count);
        }

        // check if child processes are done
        is_any_child_finished(child_list, &current_childs_count);

        free(cmd_args); //TODO remove if malloc in generalFunctions is removed
        memset(user_input, 0, INPUT_BUFFER_LEN);
        memset(raw_input, 0, INPUT_BUFFER_LEN);
    }
}

int main(int argc, char *argv[]){

    run_shell();
    return 0;
}