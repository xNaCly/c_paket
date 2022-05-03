#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpak_utils.h"

// TODO: implement this in the global config as a keyword
int color = 1;

void cpak_log(const char *str, int log_level) {
    if (color) {
        switch (log_level) {
            case SUCCESS:
                printf("%s%ssuccess:%s %s\n", ANSI_COLOR_BLACK_FG, ANSI_COLOR_GREEN,
                       ANSI_RESET, str);
                break;
            case WARN:
                printf("%s%swarning:%s %s\n", ANSI_COLOR_BLACK_FG, ANSI_COLOR_YELLOW,
                       ANSI_RESET, str);
                break;
            case ERROR:
                printf("%s%serror:%s %s\n", ANSI_COLOR_BLACK_FG, ANSI_COLOR_RED,
                       ANSI_RESET, str);
                break;
            case INFO:
            default:
                printf("%s%sinfo:%s %s\n", ANSI_COLOR_BLACK_FG, ANSI_COLOR_BLUE,
                       ANSI_RESET, str);
        }
    } else {
        switch (log_level) {
            case SUCCESS:
                printf("success: %s\n", str);
                break;
            case WARN:
                printf("warning: %s\n", str);
                break;
            case ERROR:
                printf("error %s\n", str);
                break;
            case INFO:
            default:
                printf("info %s\n", str);
        }
    }
}

void throw_error(const char *text, Errors error) {
    char error_text[sizeof(text) * 50];
    sprintf(error_text, "%s, err: %d\n", text, error);
    cpak_log(error_text, ERROR);
    exit(EXIT_FAILURE);
}

void throw_warning(const char *text, Errors error) {
    char error_text[sizeof(text) * 50];
    sprintf(error_text, "%s, err: %d\n", text, error);
    cpak_log(error_text, WARN);
}

int s_is_equal(const char *str1, const char *str2) {
    return strcmp(str1, str2) == 0;
}

int s_starts_with(const char *str, const char *str1) {
    return strncmp(str1, str, strlen(str1)) == 0;
}

int s_is_empty(const char *str) { return str[0] == '\0'; }
