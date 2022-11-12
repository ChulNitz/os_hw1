// imports
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
//#include "handleInternal.h"
#include "handleExternal.h"

//defines
#define TRUE 1
#define MAX_INPUT_LEN 255
#define MAX_CMD_LEN 100

/*
//handle external
int system_call_err(char* sys_call){
printf("hw1shell: %s failed, errno is %d\n", sys_call, errno); //TODO find errno
return -1;
}


int execute_external(char **args){
  pid_t pid;
  int status;

  pid = fork();
  if (pid == 0) {
    // Child process
    if (execvp(args[0], args) == -1) {
       system_call_err("exec");
       return -1;
    }
  } else if (pid < 0) {
    // Error forking
    system_call_err("fork");
    return -1;
  } else {
    // Parent process
    wait(NULL);
  }

  return 1;
}*/

// main
int main(int argc, char *argv[]){

    char user_input[MAX_CMD_LEN];
    char *cmd_name;
    char *cmd_params;
    char internal_cmds[][MAX_CMD_LEN] = {"cd", "exit", "jobs"};
    int len_int = sizeof(internal_cmds)/MAX_CMD_LEN;
    int i;
    int return_value = 0;
 


    while (TRUE){

        char *cmd_args[MAX_CMD_LEN] = {"\0"};
        int int_cmd_match =0;

        printf("hw1shell$ ");
        fgets(user_input, MAX_INPUT_LEN, stdin);


        //extracting the command and parameters
        cmd_name = strtok(user_input, " \n");
        cmd_params = strtok(NULL, "\n");

        for (i=0; i<len_int; ++i){
            if (!strcmp(cmd_name, internal_cmds[i])){
                int_cmd_match=1;
                // execute_internal();
            }
        }

        if (int_cmd_match == 1){
            continue;
        }

        else {
            cmd_args[0] = cmd_name;
            cmd_args[1] = cmd_params;
            cmd_args[2] = NULL;
            return_value = execute_external(cmd_args);
        }
   
    }
    return return_value;
}