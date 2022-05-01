#include <stdio.h>
#include <stdlib.h>
#include "c_p_util.h"

void throw_error(const char *text, Errors error){
    printf("Fatal Error: %s, No: %d\n", text, error);
    exit(EXIT_FAILURE);
}
