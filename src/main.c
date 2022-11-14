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
        
        printf("hw1shell$ ");
        get_input(user_input);
        strcpy(raw_input, user_input);
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
            execute_external(cmd_args, child_list, raw_input, &current_childs_count);
        }

        free(cmd_args); //TODO remove if malloc in generalFunctions is removed

        // check if child processes are done
        for (int i=0; i<current_childs_count; ++i){
            if (child_list[i].pid != 0){
                int status;
                pid_t pid = waitpid(child_list[i].pid, &status, WNOHANG);
                if (pid == -1){
                    system_call_err("waitpid");
                }
                else if (pid == 0){
                    continue;
                }
                else {
                    printf("hw1shell: process %d exited with status %d", pid, status);
                    remove_child(child_list, pid, &current_childs_count);
                }
            }
        }

    }
}
int main(int argc, char *argv[]){

    run_shell();
    return 0;
}