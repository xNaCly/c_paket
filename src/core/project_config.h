#ifndef PROJECT_CONFIG_H
#define PROJECT_CONFIG_H

typedef struct project_config {
  char *name;
  char *version;
  char *cwd;
  char **deps;
  int amount_deps;
} Project_config;

Project_config *project_conf_get_config(char *path);

#endif
