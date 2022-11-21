#ifndef HANDLE_EXTERNAL_H
#define HANDLE_EXTERNAL_H

#include "shellDefs.h"

void execute_external(char **args, child_process* child_list, char *raw_command, int* current_childs_count);

#endif