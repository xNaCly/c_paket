#ifndef C_P_UTIL_H
#define C_P_UTIL_H

#define ANSI_COLOR_BLACK_FG "\x1b[97m"
#define ANSI_COLOR_RED "\x1b[91m"
#define ANSI_COLOR_GREEN "\x1b[92m"
#define ANSI_COLOR_YELLOW "\x1b[93m"
#define ANSI_COLOR_BLUE "\x1b[96m" 
#define ANSI_COLOR_MAGENTA "\x1b[95m"
#define ANSI_RESET "\x1b[0m"

typedef enum {
    UNKNOWN_ARGUMENT = 1437,        //
    NOT_ENOUGH_ARGUMENTS = 1438,    // not enough arguments passed to cpak (TODO: soon deprecated in favor of displaying usage / help)
    TEMPLATE_MISSING = 1439,        // cpak can't find your specifed template
    CONF_MISSING_CONFIG = 1440,     // cpak can't find its config file CONF_UNKNOWN_KEY = 1441,        // cpak found an unknown key in its config file
    CONF_UNKNOWN_VALUE = 1442,      // cpak found an unknown value for a key in its config file
    P_MISSING_CONFIG = 1443,        // cpak can't find a project config in the current directory
    P_MISSING_NAME = 1444,          // cpak can't find a name for your project in the project config
    P_MISSING_VERSION = 1445,       // cpak can't find a version for your project in the project config
} Errors;

typedef enum {
    INFO = 0,
    SUCCESS,
    WARN,
    ERROR,
    DEBUG,
} Log_level;

/**
 * throws error and exits the program
 * @param text
 * @param error
 * @returns EXIT_FAILURE
 */
void throw_error(const char *text, Errors error);

/**
 * throws warning
 * @param text
 * @param error
 * @returns void
 */
void throw_warning(const char *text, Errors error);

/**
 * checks if string str1 is equal to str2
 * @param str1
 * @param str2
 * @return boolean as integer
 */
int s_is_equal(const char *str1, const char *str2);

/**
 * checks if string str is empty
 * @param str
 * @return boolean as integer
 */
int s_is_empty(const char *str);

/**
 * checks if string str starts with string str1
 * @param str
 * @param str1
 * @return boolean as integer
 */
int s_starts_with(const char *str, const char *str1);

/**
 * logging utility
 * @param str
 * @param log_level
 * @return void
 */
void cpak_log(const char *str, Log_level log_level);

#endif
