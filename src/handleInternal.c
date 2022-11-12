#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#include "handleInternal.h"
#include "generalFunctions.h"

int execute_cd(char *dest_dir)
{

  if (dest_dir == NULL) {
    printf("hw1shell: invalid command\n");
  } else {
    if (chdir(dest_dir) != 0) {
      system_call_err("cd");
     
    }
  }
  return 1;
}

int execute_jobs(char *cmd_params)
{

  return 1;
}

int execute_exit()
{

  return 1;
}


int execute_internal(char **cmd_args, int cmd_index){
  int return_val= 0;
    switch(cmd_index)
    {
        case 0:
            return_val = execute_cd (cmd_args[1]);
            break;

        case 1: //TODO jobs
            break;

        case 2:

            break;

        default: //TODO exit
            break;
    }

    return return_val;
}