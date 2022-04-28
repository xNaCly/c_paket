#include "project_config.h"
#include <stdio.h>
#include <stdlib.h>

Project_config *project_conf_get_config(char *path) {
  Project_config *pc = malloc(sizeof(Project_config));
  pc->name = "example_project";
  pc->cwd = path;
  pc->main = "main.c";
  pc->version = "v0.1";
  //  pc->deps = malloc(sizeof(char) * 5555 * 5555);
  // pc->deps[0] = "xnacly/pgme";
  return pc;
}
