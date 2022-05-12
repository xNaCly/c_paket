#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./core/cpak_utils.h"

typedef enum {
    INIT = 0,
    INSTALL,
    REMOVE,
    UPGRADE,
    BOOTSTRAP,
} command;

typedef struct {
    command cmd; // primary argument
    char* c_cmd; // child argument
} Cli_arguments;

Cli_arguments *parse_arguments(int arguments_amount, char** arguments){
    Cli_arguments *ca;
    ca = malloc(sizeof(ca));

    if(arguments_amount == 1){
        // TODO: return usage or help
        free(ca);
        throw_error("Not enough Arguments", NOT_ENOUGH_ARGUMENTS);
    }

    char* cmd = arguments[1];

    if(s_is_equal(cmd, "help")){
        ca->cmd = -1;
    } else if(s_is_equal(cmd, "bootstrap") || s_is_equal(cmd, "bo")){
        ca->cmd = BOOTSTRAP;
    }
    ca->c_cmd = malloc(sizeof(arguments[2]));

    return ca;
}

int main(int argc, char *argv[]) {
    Cli_arguments *arg = parse_arguments(argc, argv);
    //cpak_log((char *) arg->cmd, DEBUG);
    //cpak_log(arg->c_cmd, DEBUG);
    switch(arg->cmd){
        case BOOTSTRAP:
            cpak_log("BOOTSTRAP!", DEBUG);
            break;
        default:
            // TODO: see core/cpak_utils.c_l.13
            throw_error("Unknown Argument", UNKNOWN_ARGUMENT);
    }
    free(arg);
}
