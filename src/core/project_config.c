#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "project_config.h"
#include "c_p_util.h"

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
    throw_error("cant read or cant find config", P_MISSING_CONFIG);

  fscanf(file, "name=%s\nversion=%s\ndeps=%[^\n]", pc->name, pc->version,
         raw_temps);

  if(s_is_empty(pc->name) || pc->name[0] == ';'){
    throw_warning("Project name is undefined!", P_MISSING_NAME);
  }

  pc->name[strlen(pc->name)-1] = '\0';
  pc->version[strlen(pc->version)-1] = '\0';
  raw_temps[strlen(raw_temps)-1] = '\0';

  if(s_is_empty(pc->version) || pc->name[0] == ';'){
    throw_warning("Project version is undefined!", P_MISSING_VERSION);
  }

  char *ptr = strtok(raw_temps, " ");
  int i = 0;
  while (ptr != NULL) {
    pc->deps[i] = (char *)malloc(sizeof(ptr));
    strcpy(pc->deps[i], ptr);
    i++;
    ptr = strtok(NULL, " ");
  }
  pc->amount_deps = i;

  fclose(file);
  free(raw_temps);
  return pc;
}
