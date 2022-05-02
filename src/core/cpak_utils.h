#ifndef C_P_UTIL_H
#define C_P_UTIL_H

#define ANSI_COLOR_BLACK_FG "\x1b[97m"
#define ANSI_COLOR_RED "\x1b[91m"
#define ANSI_COLOR_GREEN "\x1b[92m"
#define ANSI_COLOR_YELLOW "\x1b[93m"
#define ANSI_COLOR_BLUE "\x1b[96m"
#define ANSI_RESET "\x1b[0m"

typedef enum Errors {
  CONF_MISSING_CONFIG=1440,
  CONF_UNKNOWN_KEY=1441,
  CONF_UNKNOWN_VALUE=1442,
  P_MISSING_CONFIG = 1443,
  P_MISSING_NAME = 1444,
  P_MISSING_VERSION = 1445,
} Errors;

typedef enum Log_status {
  INFO = 0,
  SUCCESS,
  WARN,
  ERROR,
} Log_level;

void throw_error(const char *text, enum Errors error);
void throw_warning(const char *text, enum Errors error);
int s_is_equal(const char *str1, const char *str2);
int s_is_empty(const char *str);
int s_starts_with(const char *str, const char *str1);
void cpak_log(const char *str, int log_level);

#endif
