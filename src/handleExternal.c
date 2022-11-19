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
    while (*current_childs_count > 0){
        pid = waitpid(-1, &status, WNOHANG);
        if (pid == -1){ //error
            system_call_err("waitpid");
        }
        else if (pid == 0){ //no child finished
            break;
        }
        else{ //child finished
            printf("hw1shell: pid %d finished\n", pid);
            remove_child(child_list, pid, current_childs_count);
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