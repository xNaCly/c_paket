#ifndef CPAK_CONFIG_H
#define CPAK_CONFIG_H

extern int flag_colors;
extern int flag_storeModulesGlobal;

typedef struct {
  char *name;
  char *version;
  char *author;
  char *desc;
  char *cwd;
  char **deps;
  int amount_deps;
} Project_config;

/*
 * @brief parses config at given path
 */
void get_config();

/*
 * @brief parses project config at given path
 * @param char *path String pointing to project config
 * @return Project_config pointer
 */
Project_config *project_conf_get_config(char *path);

/*
 * @brief frees given project pointer
 * @param *conf Project_config pointer
 */
void project_conf_destroy(Project_config *conf);

#endif
