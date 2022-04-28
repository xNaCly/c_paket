#include "project_config.h"
#include "c_p_util.h"
#include <stdio.h>
#include <stdlib.h>

Project_config *project_conf_get_config(char *path) {
  Project_config *pc;
  pc = malloc(sizeof *pc);
  FILE *file = fopen(path, "r");
  char name[255];

  if (file == NULL)
    throw_error("cant read or cant find config");

  fscanf(file, "name:%s\n", name);
  printf("test\n");
  fclose(file);

  pc->name = name;
  pc->cwd = path;
  pc->main = "main.c";
  pc->version = "v0.1";
  //  pc->deps = malloc(sizeof(char) * 5555 * 5555);
  // pc->deps[0] = "xnacly/pgme";
  return pc;
}
