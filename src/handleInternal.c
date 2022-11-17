#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "handleInternal.h"
#include "generalFunctions.h"
#include "handleExternal.h"

void execute_cd(char *dest_dir)
{
    if (dest_dir== NULL) {
    printf("hw1shell: invalid command\n");
  } else {
    if (chdir(dest_dir) != 0) {
      system_call_err("cd");
     
    }
  }
  return;
}

void execute_jobs(child_process *child_list, int *current_childs_count)
{
  is_any_child_finished(child_list, current_childs_count);

  // print all the background jobs that are still running
  for (int i = 0; i < *current_childs_count; i++)
  {
    if (child_list[i].pid != 0)
    {
      printf("%d\t%s\n", child_list[i].pid, child_list[i].user_cmd);
    }
  }
}


void execute_exit()
{
  // wait for all the background jobs to finish
  int status;
  pid_t pid;
  while ((pid = waitpid(-1, &status, 0)) > 0)
  {
    printf("hw1shell: pid %d finished\n", pid);
  }
  // exit the shell
  exit(0);
}


void execute_internal(char **cmd_args, int cmd_index, child_process *child_list, int *current_childs_count){

    switch(cmd_index)
    {
        case 0:
            execute_cd (cmd_args[1]);
            break;
            
        case 1:
            execute_jobs(child_list, current_childs_count);
            break;

        case 2:
            execute_exit();
            break;

        default:
            break;
    }
    return;
}