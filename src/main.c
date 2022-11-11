// imports
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//defines
#define TRUE 1
#define MAX_CMD_LEN 255

// main
int main(int argc, char *argv[]){

    char input_cmd[MAX_CMD_LEN];

    while (TRUE){

        printf("hw1shell$ ");
        fgets(input_cmd, MAX_CMD_LEN, stdin);
        printf("%s", input_cmd);

        if (!strcmp(input_cmd, "exit")){
            return 1;
            // go to exit fuction
            // break;
        }
    
    }
    return 0;
}