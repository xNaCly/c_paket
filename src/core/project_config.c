#include "project_config.h"
#include "c_p_util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Project_config *project_conf_get_config(char *path) {
  Project_config *pc;
  pc = malloc(sizeof *pc);
  pc->name = malloc(sizeof(char) * 255);
  pc->version = malloc(sizeof(char) * 255);
  pc->cwd = malloc(sizeof(path));
  pc->cwd = path;
  pc->deps = (char **)malloc(sizeof(char *) * 15);
  char *raw_temps = malloc(sizeof(char) * 510);
  FILE *file = fopen(path, "r");

  if (file == NULL)
    throw_error("cant read or cant find config");

  fscanf(file, "name=%s\nversion=%s\ndeps=%[^\n]", pc->name, pc->version,
         raw_temps);

  char *ptr = strtok(raw_temps, " ");
  int i = 0;

  while (ptr != NULL) {
    pc->deps[i] = (char *)malloc(sizeof(ptr));
    pc->deps[i] = ptr;
    i++;
    ptr = strtok(NULL, " ");
  }

  fclose(file);
  free(raw_temps);
  return pc;
}
