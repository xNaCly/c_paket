#ifndef CPAK_CONFIG_H
#define CPAK_CONFIG_H

typedef struct {
  int colors;
  int storeModulesGlobal;
} Config;

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
 * @brief returns the path to the cpak config directory
 * @description scanning priority:
 *                1. 'CPAK_CONFIG_HOME' env variable
 *                2. 'XDG_CONFIG_HOME' env variable + '/cpak/'
 *                3. 'HOME' env variable + '/.config/cpak/'
 * @returns path to cpaks config
 */
char* get_cpak_config_path();

/*
 * @brief parses config at given path
 * @return Config pointer
 */
Config *get_config();

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
