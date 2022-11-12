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

//defines
#define TRUE 1
#define MAX_INPUT_LEN 255
#define MAX_CMD_LEN 100


// main
int main(int argc, char *argv[]){

    char user_input[MAX_CMD_LEN];
    char *cmd_name;
    char *cmd_params;
    char internal_cmds[][MAX_CMD_LEN] = {"cd", "jobs", "exit"};
    int len_int = sizeof(internal_cmds)/MAX_CMD_LEN;
    int i;
    int return_value = 0;
 


    while (TRUE){

        char **cmd_args;
        int int_cmd_match =0;

        printf("hw1shell$ ");
        fgets(user_input, MAX_INPUT_LEN, stdin);


        //parsing command, cmd_args[0] is the command name
        cmd_args = split_cmd_line (user_input);

        //TODO add background cmd logic

        //check if the cmd is internal
        for (i=0; i<len_int; ++i){
            if (!strcmp(cmd_args[0], internal_cmds[i])){
                int_cmd_match= 1;
                return_value= execute_internal(cmd_args, i);
            }
        }

        //if the cmd was internal - startover loop
        if (int_cmd_match == 1){ //TODO should reap all child process before new loop
            continue;
        }

        //external cmd handling
        else {
            return_value= execute_external(cmd_args);
        }

        free(cmd_args); //TODO remove if malloc in generalFunctions is removed
       }
    return return_value;
}