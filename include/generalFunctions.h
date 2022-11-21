#ifndef GENERAL_FUNCTIONS_H
#define GENERAL_FUNCTIONS_H

#include "shellDefs.h"

char **split_cmd_line (char* input_cmd);
int system_call_err(char* sys_call);
void add_child(child_process* child_list, pid_t pid, char* raw_cmd, int* current_childs_count);
void remove_child(child_process* child_list, pid_t pid, int* current_childs_count);
void is_any_child_finished(child_process* child_list, int* current_childs_count);


#endif