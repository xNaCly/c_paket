#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../libs/libgit2/include/git2.h"

#include "cpak_cli.h"
#include "cpak_config.h"
#include "cpak_utils.h"

int c_bootstrap(char *template_name, char *outdir) {
    char *template_path = malloc(sizeof(char) * 255);
    char *path = get_cpak_config_path();

    snprintf(template_path, 255, "%s/templates/%s", path, template_name);

    if (!f_exists(template_path)) {
        printf("%s - ", template_path);
        throw_error("Can't read template", TEMPLATE_MISSING);
    }

    char *command = malloc(sizeof(char) * 510);
    sprintf(command, "cp -r %s/* %s", template_path, outdir);

    int r = system(command);

    free(template_path);
    free(path);
    free(command);

    if(r == EXIT_SUCCESS){
      cpak_log("bootstraped template", SUCCESS);
    } else {
      cpak_log("bootstraping template failed", ERROR);
    }
    return r;
}

int c_help(char *command) {
    char *T_CPAK = getenv("CPAK_TESTING");
    int t_flag = T_CPAK != NULL && s_is_equal(T_CPAK, "true") ? 1 : 0;
    if (s_is_equal(command, "all")) {
        printf("%s", t_flag ? "" : USAGE "\n");
    } else if (s_is_equal(command, "help")) {
        printf("%s", U_HELP);
    } else if (s_is_equal(command, "init")) {
        printf("%s", U_INIT);
    } else if (s_is_equal(command, "config")) {
        printf("%s", U_CONFIG);
    } else if (s_is_equal(command, "add")) {
        printf("%s", U_ADD);
    } else if (s_is_equal(command, "remove")) {
        printf("%s", U_REMOVE);
    } else if (s_is_equal(command, "bootstrap")) {
        printf("%s", U_BOOTSTRAP);
    } else if (s_is_equal(command, "version")) {
        printf("%s", U_VERSION);
    } else {
        printf("%s", t_flag ? "" : USAGE "\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int c_init(char *outdir) {
    char *T_CPAK = getenv("CPAK_TESTING");
    int t_flag = T_CPAK != NULL && s_is_equal(T_CPAK, "true") ? 1 : 0;
    if (!t_flag)
        cpak_log("Initialising new Project", INFO);
    char *file_name = "cpak_project.conf";
    char *file_path = malloc(sizeof(char) * 255);
    char *description = "";
    char *version = "v0.0.1";
    char *author = s_is_empty(getenv("USER")) ? "anon" : getenv("USER");
    char *pwd = s_is_empty(getenv("PWD")) ? "anon" : getenv("PWD");

    snprintf(file_path, 255, "%s/%s", outdir, file_name);
    FILE *file = fopen(file_path, "w");
    free(file_path);

    if (file == NULL)
        throw_error("Permission denied.", 404);

    fprintf(file, "# cpak config file\n\n\
# name of the project\n\
name=%s\n\
description=%s\n\
version=%s\n\
author=%s\n\
deps=\n",
            pwd, description, version, author);

    fclose(file);

    if (!t_flag) {
        cpak_log("Created 'cpak_project.conf'", INFO);
        int len = sizeof(char) * 1024;
        char *buf = malloc(len);
        snprintf(buf, len, "Initialised new Project in: %s", pwd);
        cpak_log(buf, SUCCESS);
        free(buf);
    }

    return EXIT_SUCCESS;
}

int c_config(int overwrite) {
    if (!overwrite) {
        int config_exists = conf_exists();
        if (config_exists)
            throw_error("Cpak config exists, consider using the 'override' keyword to override the existing config",
                        CONF_EXISTS);
    }

    char *path = get_cpak_config_path();
    char *conf_file_path = malloc(sizeof(char) * 255);
    char *command = malloc(sizeof(char) * 1042);


    sprintf(command, "mkdir -p %s", path);
    snprintf(conf_file_path, 255, "%s/cpak.conf", path);

    int r = system(command);
    if(r != EXIT_SUCCESS){
        throw_warning("Couldn't create cpak folder in config directory", -1);
    }

    FILE *file = fopen(conf_file_path, "w");

    if (!file)
        throw_error("Couldn't open config directory", -1);

    fprintf(file, "%s", CONFIG_FILE);
    fclose(file);

    free(command);
    free(path);
    free(conf_file_path);
    return (EXIT_SUCCESS);
}

int c_add(char *module){
    // extracting <repo> from input (<user>/<repo>)
    char *copy_module = malloc(sizeof(module));
    strcpy(copy_module, module);
    char *module_name = strtok(copy_module, "/");
    module_name = strtok(NULL, "\0");

    git_libgit2_init();
    git_repository *repo = NULL;
    char *cmd = "mkdir -p ./cpak_modules";
    char *url = malloc(sizeof(char) * 1024);
    char *path = malloc(sizeof(char) * 1024);

    int created = system(cmd);
    if(created != EXIT_SUCCESS) throw_error("Couldn't create modules directory, please check your permissions config", -1);

    snprintf(url, 1024, "%s%s", VSC_PREFIX, module);
    snprintf(path, 1024, "./cpak_modules/%s", module_name);
    free(copy_module);

    int error = git_clone(&repo, url, path, NULL);

    if(error != EXIT_SUCCESS) {
        throw_error("Couldn't install module using git, please verify git is installed", -1);
        return EXIT_FAILURE;
    }
    
    free(url);

    char *feedback = malloc(sizeof(char) * 1024);
    snprintf(feedback, 1024, "Installed module '%s' in %s", module, path);
    free(path);

    cpak_log(feedback, SUCCESS);

    free(feedback);

    git_libgit2_shutdown();
    return EXIT_SUCCESS;
}
