#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include "handleInternal.h"
#include "generalFunctions.h"

void execute_cd(char *dest_dir)
{

  if (dest_dir == NULL) {
    printf("hw1shell: invalid command\n");
  } else {
    if (chdir(dest_dir) != 0) {
      system_call_err("cd");
     
    }
  }
  return;
}

void execute_jobs(char *cmd_params)
{

  return;
}

void execute_exit()
{

  return;
}


void execute_internal(char **cmd_args, int cmd_index){

    switch(cmd_index)
    {
        case 0:
            execute_cd (cmd_args[1]);
            break;

        case 1: //TODO jobs
            break;

        case 2:

            break;

        default: //TODO exit
            break;
    }
    return;
}