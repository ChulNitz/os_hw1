#include <unistd.h>

void system_call_err(char* sys_call){
printf("hw1shell: %s failed, errno is %d", sys_call, perror());
}

int execute_external(char **args){
  pid_t pid;
  int status;

  pid = fork();
  if (pid == 0) {
    // Child process
    if (execvp(args[0], args) == -1) {
       system_call_err("exec");
    }
  } else if (pid < 0) {
    // Error forking
    system_call_err("fork");
  } else {
    // Parent process
    wait(NULL);
  }

  return 1;
}