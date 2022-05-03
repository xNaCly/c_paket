#include "cpak_cli.h"
#include "cpak_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int bootstrap(char *template, char *outdir) {
    char *CONFIG_HOME = getenv("XDG_CONFIG_HOME");

    if (s_is_empty(CONFIG_HOME))
        strcpy(CONFIG_HOME, "$HOME/.config");

    char template_path[strlen(CONFIG_HOME)];
    sprintf(template_path, "%s/cpak/templates/%s", CONFIG_HOME, template);

    struct stat st;
    if (stat(template_path, &st) != 0) {
        printf("%s - ", template_path);
        throw_error("Can't read template", TEMPLATE_MISSING);
    }

    char command[strlen(template_path) * 2];
    sprintf(command, "cp -r %s/* %s", template_path, outdir);
    int r = system(command);
    if (r == EXIT_SUCCESS)
        cpak_log("Successfully bootstrapped project", SUCCESS);

    return r;
}