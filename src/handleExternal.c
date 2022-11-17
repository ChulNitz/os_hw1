#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "handleExternal.h"
#include "generalFunctions.h"


void is_any_child_finished(child_process* child_list, int* current_childs_count){
    int status;
    pid_t pid;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0){ //TODO handle error of waitpid
        printf("hw1shell: pid %d finished\n", pid);
        remove_child(child_list, pid, current_childs_count);
        
        // need to move all children to the left of the list
        for (int i=0; i<*current_childs_count; ++i){
            if (child_list[i].pid == 0){
                child_list[i].pid = child_list[i+1].pid;
                strcpy(child_list[i].user_cmd, child_list[i+1].user_cmd);
                child_list[i+1].pid = 0;
                child_list[i+1].user_cmd[0] = '\0';
            }
        }
    } 
}


void execute_external(char **args, child_process *child_list, char *raw_command, int *current_childs_count)
{
  pid_t pid;
  int status;

  // find if the last token is '&' (background process)
  int is_background = 0;
  int i = 0;
  while (args[i] != NULL)
  {
    if (!strcmp(args[i], "&"))
    {
      is_background = 1;
      args[i] = NULL; // remove '&' from args
      break;
    }
    i++;
  }

  if (is_background && (*current_childs_count) == 4)
  {
    printf(" hw1shell: too many background commands running\n");
    return;
  }

  pid = fork();
  if (pid == 0)
  {
    // Child process
    if (execvp(args[0], args) == -1)
    {
      printf("hw1shell: invalid command\n");
      system_call_err("exec");
      return;
    }
  }
  else if (pid < 0)
  {
    // Error forking
    system_call_err("fork");
    return;
  }
  else
  { // parent process
    if (is_background)
    {
      printf("hw1shell: pid %d started\n", pid);
      add_child(child_list, pid, raw_command, current_childs_count);
      return;
    }
    else
    {
      waitpid(pid, &status, 0);
      return;
    }
  }
}