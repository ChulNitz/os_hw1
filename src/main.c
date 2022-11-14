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
char *cmd_name;
char *cmd_params;
char **cmd_args;
const char internal_cmds[NUM_INTERNAL_CMDS][MAX_CMD_LEN] = {"cd", "jobs", "exit"};



void get_input(char *pUser_input){
    fgets(pUser_input, INPUT_BUFFER_LEN, stdin);
}

void run_shell(){

    
    while (TRUE){

        int is_internal = 0;
        
        printf("hw1shell$ ");
        get_input(&user_input);

        //parsing command, cmd_args[0] is the command name
        cmd_args = split_cmd_line (user_input);

        //TODO add background cmd logic

        //check if the cmd is internal
        
        for (int i=0; i<NUM_INTERNAL_CMDS; ++i){
            if (!strcmp(cmd_args[0], internal_cmds[i])){
                execute_internal(cmd_args, i);
                is_internal = 1;
            }
        }

        if (is_internal){ //TODO should reap all child process before new loop
            continue;
        }

        else {
            
            execute_external(cmd_args);
        }

        free(cmd_args); //TODO remove if malloc in generalFunctions is removed
    }
}



int main(int argc, char *argv[]){

    run_shell();
    return 0;
}