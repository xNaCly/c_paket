#ifndef C_P_UTIL_H
#define C_P_UTIL_H

typedef enum Errors { 
  P_MISSING_CONFIG=1443, 
  P_MISSING_NAME=1444, 
  P_MISSING_VERSION=1445
} Errors; 

void throw_error(const char *text, enum Errors error);
void throw_warning(const char *text, enum Errors error);
int s_is_equal(const char *str1, const char *str2);


#endif
