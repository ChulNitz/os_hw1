#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include "handleExternal.h"

int system_call_err(char* sys_call){
printf("hw1shell: %s failed, errno is %d\n", sys_call, errno); 
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
  } 
  else if (pid < 0) {
    // Error forking
    system_call_err("fork");
    return -1;
  } 
  else {
    // Parent process
    wait(NULL);
  }

  return 1;
}