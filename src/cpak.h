#ifndef CPAK_H
#define CPAK_H

#define CPAK_VERSION __VERSION__ 


typedef enum {
  INIT = 0,
  ADD,
  REMOVE,
  UPGRADE,
  BOOTSTRAP,
  VERSION,
  HELP,
  CONFIG,
  UNDEF,
  UNKNOWN,
} command;

typedef struct {
  command cmd; // primary argument
  char *c_cmd; // child argument
} Cli_arguments;

#endif
