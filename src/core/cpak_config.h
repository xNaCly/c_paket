#ifndef CPAK_CONFIG_H
#define CPAK_CONFIG_H

typedef struct {
    int colors;
    int storeModulesGlobal;
} Config;

typedef struct { char *name;
    char *version;
    char *cwd;
    char **deps;
    int amount_deps;
} Project_config;

Config *get_config(char *path);
Project_config *project_conf_get_config(char *path);
void project_conf_free(Project_config *conf);

#endif
