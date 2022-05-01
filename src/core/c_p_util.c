#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "c_p_util.h"

void throw_error(const char *text, Errors error){
    printf("Fatal Error: %s, No: %d\n", text, error);
    exit(EXIT_FAILURE);
}

void throw_warning(const char *text, Errors error){
    printf("Warning: %s, No: %d\n", text, error);
}

int s_is_equal(const char *str1, const char *str2){
    return strcmp(str1, str2) == 0;
}
