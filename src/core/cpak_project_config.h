#ifndef PROJECT_CONFIG_H
#define PROJECT_CONFIG_H

typedef struct {
    char *name;
    char *version;
    char *cwd;
    char **deps;
    int amount_deps;
} Project_config;

Project_config *project_conf_get_config(char *path);
void project_conf_free(Project_config *conf);

#endif
