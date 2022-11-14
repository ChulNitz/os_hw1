#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "handleExternal.h"
#include "generalFunctions.h"


void execute_external(char **args, child_process* child_list, char* raw_command, int* current_childs_count){
  pid_t pid;
  int status;

  // find if the last token is '&' (background process)
  int is_background = 0;
  int i = 0;
  while (args[i] != NULL){
    if (!strcmp(args[i], "&")){
      is_background = 1;
      args[i] = NULL; // remove '&' from args
      break;
    }
    i++;
  }

  if(is_background && (*current_childs_count) == 4){
    printf("hw1shell: cannot run more than 4 background jobs\n");
    return;
  }

  pid = fork();
  if (pid == 0) {
    // Child process
    if (execvp(args[0], args) == -1) {
       system_call_err("exec");
       return;
    }
  } 
  else if (pid < 0) {
    // Error forking
    system_call_err("fork");
    return;
  } 
  else { //parent process
    if (is_background){
      printf("hw1shell: background pid is %d\n", pid);
      add_child(child_list, pid, raw_command, current_childs_count);
      return;
    }
    else {
        waitpid(pid, &status, 0);
        return;
    }
  }
}