#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "cpak_config.h"
#include "cpak_utils.h"

int f_exists(char *path) {
    struct stat st;
    if (path == NULL || s_is_empty(path))
        return 0;
    return stat(path, &st) == 0;
}

char *get_module_path(){
    char* p = malloc(sizeof(char)*256);
    char* c_m_home = getenv("CPAK_MODULE_HOME");
    char* x_d_home = getenv("XDG_DATA_HOME");
    char* h = getenv("HOME");

    if(!s_is_empty(c_m_home)){
        strcpy(p, c_m_home);
    } else if(!s_is_empty(x_d_home)){
        snprintf(p, 255, "%s/.cpak", x_d_home);
    } else {
        snprintf(p, 255, "%s/.cpak", h);
    }

    return p;
}

char *get_config_path() {
    char *cpak_dir = getenv("CPAK_CONFIG_HOME");
    char *xdg_dir = getenv("XDG_CONFIG_HOME");

    if (!s_is_empty(cpak_dir)) {
        char *buf = malloc(sizeof(char) * 255);
        snprintf(buf, 254, "%s", cpak_dir);
        return buf;
    }

    if (!s_is_empty(xdg_dir)) {
        char *buf = malloc(sizeof(char) * 255);
        snprintf(buf, 254, "%s/cpak", xdg_dir);
        return buf;
    }

    char *p = NULL;
    p = malloc(sizeof(char) * 255);
    char *home = getenv("HOME");
    snprintf(p, 254, "%s/.config/cpak", home);

    return p;
}

int conf_exists() {
    char *path = get_config_path();
    int exists = f_exists(path);
    free(path);
    return exists;
}

void cpak_log(const char *str, Log_level log_level) {
    if (g_flag_colors) {
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
            case DEBUG:
                printf("%s%sdebug:%s %s\n", ANSI_COLOR_BLACK_FG, ANSI_COLOR_MAGENTA,
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
                printf("error: %s\n", str);
                break;
            case DEBUG:
                printf("debug: %s\n", str);
                break;
            case INFO:
            default:
                printf("info: %s\n", str);
        }
    }
}

void throw_error(const char *text, Errors error) {
    char error_text[2048];
    snprintf(error_text, 2047, "%s, err: %d", text, error);
    cpak_log(error_text, ERROR);
    exit(EXIT_FAILURE);
}

void throw_warning(const char *text, Errors error) {
    char error_text[2048];
    snprintf(error_text, 2047, "%s, err: %d", text, error);
    cpak_log(error_text, WARN);
}

int s_is_equal(const char *str, const char *str1) {
    if (s_is_empty(str) || s_is_empty(str1)) throw_error("string is empty", ERR_EMPTY_STR);
    return strcmp(str, str1) == 0;
}

int s_starts_with(const char *str, const char *start) {
    return strncmp(start, str, strlen(start)) == 0;
}

int s_is_empty(const char *str) {
    if (!str)
        return 1;
    return str[0] == '\0';
}
