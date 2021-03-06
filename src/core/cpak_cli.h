#ifndef CPAK_CLI_H
#define CPAK_CLI_H

#define USAGE                                                                  \
  "\
Usage: cpak <command> [arg]\n\
\
cpak is the fast and efficient source based package manager for the c programming language\n\
\n\n\
List of commands:\n\
    help        - show this screen\n\
    config      - generate config\n\
    add         - add a dependency\n\
    remove      - remove a dependency\n\
    bootstrap   - apply a template to a project\n\
    version     - display version information"

#define U_HELP                                                                 \
  "Help displays basic info and a reference about each available command.\n\n\
\thelp [command]\n\th [command]\n\nExample:\n\tcpak h help\n\tcpak h\n"


#define U_CONFIG                                                               \
  "Generates the default config in '$XDG_CONFIG_HOME'.\n\n\
\tconfig\n\tc\n\nExample:\n\tcpak c \n\nIf the config already exists, use the '-f' flag to override the current config, like so:\n\tcpak c -f\n"

#define U_ADD                                                                  \
  "Add adds a new package to the project.\n\n\
\tadd <package>\n\ta <package>\n\nExample:\n\tcpak a xnacly/xc\n"

#define U_REMOVE                                                               \
  "Remove removes a package from the project.\n\n\
\tremove <package>\n\tr <package>\n\nExample:\n\tcpak r xnacly/xc\n"

#define U_BOOTSTRAP                                                            \
  "Bootstrap bootstraps a new directory from a predefined template.\n\n\
\tbootstrap <template>\n\tb <template>\n\nExample:\n\tcpak b default\n"

#define U_VERSION                                                              \
  "Version displays version.\n\n\
\tversion\n\tv\n\nExample:\n\tcpak v\n"

#define CONFIG_FILE \
"#cpak global config\n\
#specify if the output of cpak should be colored\n\
colors=true\n\
#specify if the installed modules should be stored globally or locally\n\
storeModulesGlobal=true\n"

#define DEFAULT_TEMPLATE_GITIGNORE \
"#cpak specific\n\
cpak_modules"

/*
 * @brief bootstraps a project in 'outdir' with the name 'template_name'
 * @param *template_name
 * @param *outdir dir to copy template content to
 * @returns EXIT_SUCCESS or EXIT_FAILURE
 */
int c_bootstrap(char *template_name, char *outdir);

/*
 * @brief displays global help if param command is "none", otherwise prints help
 * for a specif command
 * @param *command
 * @returns EXIT_SUCCESS or EXIT_FAILURE
 */
int c_help(char *command);

/*
 * @brief inits a new cpak project by creating a 'cpak_project.conf' file
 * @param *outdir
 * @returns EXIT_SUCCESS or EXIT_FAILURE
 */
/* int c_init(char *outdir); */

/*
 * @brief generates the default config in '$XDG_CONFIG_HOME'
 * @returns EXIT_SUCCESS or EXIT_FAILURE
 */
int c_config();

/*
 * @brief adds a new dependency to the project
 * @returns EXIT_SUCCESS or EXIT_FAILURE
 */
int c_add(char *module);

/*
 * @brief removes a dependency from the project
 * @returns EXIT_SUCCESS or EXIT_FAILURE
 */
int c_remove(char *module);

/*
 * @brief removes a dependency from the project
 * @returns EXIT_SUCCESS or EXIT_FAILURE
 */
int c_upgrade(char *module);
#endif
