#ifndef SHELL_DEFS_H
#define SHELL_DEFS_H


#define TRUE 1
#define INPUT_BUFFER_LEN 1024
#define MAX_CMD_LEN 100
#define MAX_ARGS 64
#define NUM_INTERNAL_CMDS 3
#define MAX_CHILDS 4


//enums
typedef struct process_child{
    char user_cmd[INPUT_BUFFER_LEN];
    int pid;
}child_process;


#endif