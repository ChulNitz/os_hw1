#ifndef HANDLE_INTERNAL
#define HANDLE_INTERNAL

int execute_cd(char *cmd_params);
int execute_jobs(char *cmd_params);
int execute_exit();

int execute_internal(char **cmd_args, int cmd_index);

#endif
