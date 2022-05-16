#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpak_config.h"
#include "cpak_utils.h"

Config *get_config(char *path) {
  Config *c;
  c = (Config *)malloc(sizeof *c);
  FILE *file = fopen(path, "r");

  if (file == NULL) {
    throw_error("Can't read or find cpak config", CONF_MISSING_CONFIG);
  }

  char cur_line[255];

  while (fgets(cur_line, 255, file)) {
    if (s_is_empty(cur_line))
      continue;
    else if (s_starts_with(cur_line, "#"))
      continue;
    else if (s_starts_with(cur_line, "colors=")) {
      char temp[255 * 5];
      sscanf(cur_line, "colors=%s\n", temp);
      if (s_is_equal(temp, "true")) {
        c->colors = 1;
      } else if (s_is_equal(temp, "false")) {
        c->colors = 0;
      } else {
        cur_line[strlen(cur_line) - 1] = '\0';
        sprintf(temp, "'%s' is not a known value for key: 'color'", cur_line);
        throw_warning(temp, CONF_UNKNOWN_VALUE);
      }
      continue;
    } else if (s_starts_with(cur_line, "storeModulesGlobal=")) {
      char temp[255 * 5];
      sscanf(cur_line, "storeModulesGlobal=%s\n", temp);
      if (s_is_equal(temp, "true")) {
        c->storeModulesGlobal = 1;
      } else if (s_is_equal(temp, "false")) {
        c->storeModulesGlobal = 0;
      } else {
        sprintf(temp, "'%s' is not a known value for key: 'color'", cur_line);
        throw_warning(temp, CONF_UNKNOWN_VALUE);
      }
      continue;
    } else {
      char temp[255 * 5];
      cur_line[strlen(cur_line) - 1] = '\0';
      sprintf(temp, "'%s' is not a known key value pair", cur_line);
      throw_warning(temp, CONF_UNKNOWN_KEY);
    }
  }
  fclose(file);

  return c;
}

void project_conf_free(Project_config *conf) {
  for (int i = 0; i < conf->amount_deps; i++) {
    free(conf->deps[i]);
  }
  free(conf->name);
  free(conf->version);
  free(conf->author);
  free(conf->desc);
  free(conf);
}

Project_config *project_conf_get_config(char *path) {
  Project_config *pc;
  pc = malloc(sizeof *pc);
  pc->name = malloc(sizeof(char) * 510);
  pc->version = malloc(sizeof(char) * 510);
  pc->author = malloc(sizeof(char) * 510);
  pc->desc = malloc(sizeof(char) * 1024);
  pc->cwd = malloc(sizeof(path));
  pc->deps = malloc(sizeof(char *) * 15);
  pc->cwd = path;

  FILE *file = fopen(path, "r");

  // TODO: needs check if file has correct file ending (.conf)

  if (file == NULL) {
    project_conf_free(pc);
    throw_error("Can't read or find project config", P_MISSING_CONFIG);
  }

  char cur_line[255];

  while (fgets(cur_line, 255, file)) {
    if (s_is_empty(cur_line))
      continue;
    else if (s_starts_with(cur_line, "#")) {
      continue;
    } else if (s_starts_with(cur_line, "name=")) {
      sscanf(cur_line, "name=%s\n", pc->name);
      continue;
    } else if (s_starts_with(cur_line, "author=")) {
      sscanf(cur_line, "author=%s\n", pc->author);
      continue;
    } else if (s_starts_with(cur_line, "description=")) {
      sscanf(cur_line, "description=%[^\n]", pc->desc);
      continue;
    } else if (s_starts_with(cur_line, "version=")) {
      sscanf(cur_line, "version=%s\n", pc->version);
      continue;
    } else if (s_starts_with(cur_line, "deps=")) {
      sscanf(cur_line, "deps=%[^\n]", cur_line);
      char *ptr = strtok(cur_line, " ");
      int i = 0;
      while (ptr != NULL) {
        pc->deps[i] = malloc(sizeof(*ptr));
        strcpy(pc->deps[i], ptr);
        i++;
        ptr = strtok(NULL, " ");
      }
      pc->amount_deps = i;
    };
  }


  fclose(file);
  return pc;
}
