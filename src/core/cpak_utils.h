#ifndef CPAK_UTIL_H
#define CPAK_UTIL_H

#define ANSI_COLOR_BLACK_FG "\x1b[97m"
#define ANSI_COLOR_RED "\x1b[91m"
#define ANSI_COLOR_GREEN "\x1b[92m"
#define ANSI_COLOR_YELLOW "\x1b[93m"
#define ANSI_COLOR_BLUE "\x1b[96m"
#define ANSI_COLOR_MAGENTA "\x1b[95m"
#define ANSI_RESET "\x1b[0m"

typedef enum {
  // Argument is unknown to cpak
  UNKNOWN_ARGUMENT = 1437,
  // not enough arguments passed to cpak
  NOT_ENOUGH_ARGUMENTS = 1438,
  // cpak can't find your specifed template
  TEMPLATE_MISSING = 1439,
  // cpak can't find its config file
  CONF_MISSING_CONFIG = 1440,
  // cpak found an unknown key in its config file
  CONF_UNKNOWN_KEY = 1441,
  // cpak found an unknown value for a key in its config file
  CONF_UNKNOWN_VALUE = 1442,
  // cpak can't find a project config in the current directory
  P_MISSING_CONFIG = 1443,
} Errors;

typedef enum {
  INFO = 0,
  SUCCESS,
  WARN,
  ERROR,
  DEBUG,
} Log_level;

/*
 * checks if file exists
 * @returns EXIT_SUCCESS or EXIT_FAILURE
 */
int f_exists(char *path);

/*
 * @brief returns the path to the cpak config directory
 * @description scanning priority:
 *                1. 'CPAK_CONFIG_HOME' env variable
 *                2. 'XDG_CONFIG_HOME' env variable + '/cpak/'
 *                3. 'HOME' env variable + '/.config/cpak/'
 * @returns path to cpaks config
 */
char *get_cpak_config_path();

/*
 * @brief checks if cpaks config exists
 * @returns EXIT_SUCCESS or EXIT_FAILURE
 */
int conf_exists();

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
int s_is_equal(const char *str, const char *str1);

/**
 * checks if string str is empty
 * @param str
 * @return boolean as integer
 */
int s_is_empty(const char *str);

/**
 * checks if string str starts with string str1
 * @param str
 * @param start
 * @return boolean as integer
 */
int s_starts_with(const char *str, const char *start);

/**
 * logging utility
 * @param str
 * @param log_level
 * @return void
 */
void cpak_log(const char *str, Log_level log_level);

#endif
