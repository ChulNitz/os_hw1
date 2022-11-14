#ifndef HANDLE_INTERNAL_H
#define HANDLE_INTERNAL_H

#include "shellDefs.h"

void execute_exit();
void execute_internal(char **cmd_args, int cmd_index, child_process *child_list, int *current_childs_count);

#endif
