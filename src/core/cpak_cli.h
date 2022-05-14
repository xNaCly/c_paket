#ifndef CPAK_CLI_H
#define CPAK_CLI_H

#define USAGE "\
Usage: cpak <command> [arg]\n\
\
cpak is the fast and efficient package manager for the c programming language\n\
\n\n\
List of commands:\n\
    help        - show this screen\n\
    init        - initialise a new project\n\
    add         - add a dependency\n\
    remove      - remove a dependency\n\
    bootstrap   - apply a template to a project\n\
    version     - display version information"


/*
 * @brief bootstraps a project in 'outdir' with the name 'template_name'
 * @param *template_name
 * @param *outdir dir to copy template content to
 * @returns EXIT_SUCCESS or EXIT_FAILURE
 */
int bootstrap(char *template_name, char *outdir);

/*
 * @brief displays global help if param command is "none", otherwise prints help for a specif command
 * @param *command
 */
void help(char *command);

#endif
