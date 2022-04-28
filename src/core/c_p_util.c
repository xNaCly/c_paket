#include <stdio.h>
#include <stdlib.h>

void throw_error(const char *text){
    printf("Fatal Error: %s", text);
    exit(EXIT_FAILURE);
}
