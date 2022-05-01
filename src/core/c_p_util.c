#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "c_p_util.h"

void cpak_log(const char *str, int log_level){
    switch(log_level){
        case SUCCESS:
            printf("%s %s SUCCESS %s %s\n",ANSI_COLOR_BLACK_FG, ANSI_COLOR_GREEN, ANSI_RESET, str);
            break;
        case WARN:
            printf("%s %s WARN %s %s\n",ANSI_COLOR_BLACK_FG, ANSI_COLOR_YELLOW, ANSI_RESET, str);
            break;
        case ERROR:
            printf("%s %s ERROR %s %s\n",ANSI_COLOR_BLACK_FG, ANSI_COLOR_RED, ANSI_RESET, str);
            break;
        case INFO:
        default:
            printf("%s %s INFO %s %s\n",ANSI_COLOR_BLACK_FG, ANSI_COLOR_BLUE, ANSI_RESET, str);
    }
}

void throw_error(const char *text, Errors error){
    char error_text[sizeof(text)*50];
    sprintf(error_text,"Fatal Error: %s, err: %d\n", text, error);
    cpak_log(error_text, ERROR);
    exit(EXIT_FAILURE);
}

void throw_warning(const char *text, Errors error){
    char error_text[sizeof(text)*50];
    sprintf(error_text,"Warning: %s, err: %d\n", text, error);
    cpak_log(error_text, WARN);
}

int s_is_equal(const char *str1, const char *str2){
    return strcmp(str1, str2) == 0;
}

int s_is_empty(const char *str){
    return str[0] == '\0';
}
