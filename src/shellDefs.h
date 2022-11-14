#define TRUE 1
#define INPUT_BUFFER_LEN 1024
#define MAX_CMD_LEN 100
#define MAX_ARGS 64
#define NUM_INTERNAL_CMDS 3


//enums

typedef struct {
    char num_of_jobs;
    char *user_cmds[INPUT_BUFFER_LEN];
}child_process;