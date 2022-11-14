#ifndef HANDLE_INTERNAL
#define HANDLE_INTERNAL

void execute_cd(char *cmd_params);
void execute_jobs(char *cmd_params);
void execute_exit();

void execute_internal(char **cmd_args, int cmd_index);

#endif
