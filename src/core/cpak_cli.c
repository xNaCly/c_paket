#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpak_cli.h"
#include "cpak_config.h"
#include "cpak_utils.h"

int c_bootstrap(char *template_name, char *outdir) {
    char *template_path = malloc(sizeof(char) * 255);
    char *path = get_config_path();

    snprintf(template_path, 254, "%s/templates/%s", path, template_name);

    if (!f_exists(template_path)) {
        printf("%s - ", template_path);
        throw_error("Can't read template", ERR_TEMPLATE_MISSING);
    }

    char *command = malloc(sizeof(char) * 510);
    snprintf(command, 509, "cp -r %s/. %s", template_path, outdir);

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
    }
    /* else if (s_is_equal(command, "init")) { */
    /*     printf("%s", U_INIT); */
    /* } */
    else if (s_is_equal(command, "config")) {
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

/* int c_init(char *outdir) { */
/*     char *T_CPAK = getenv("CPAK_TESTING"); */
/*     int t_flag = T_CPAK != NULL && s_is_equal(T_CPAK, "true") ? 1 : 0; */
/*     if (!t_flag) */
/*         cpak_log("Initialising new Project", INFO); */
/*     char *file_name = "cpak_project.conf"; */
/*     char *file_path = malloc(sizeof(char) * 255); */
/*     char *description = ""; */
/*     char *version = "v0.0.1"; */
/*     char *author = s_is_empty(getenv("USER")) ? "anon" : getenv("USER"); */
/*     char *pwd = s_is_empty(getenv("PWD")) ? "anon" : getenv("PWD"); */

/*     snprintf(file_path, 255, "%s/%s", outdir, file_name); */
/*     FILE *file = fopen(file_path, "w"); */
/*     free(file_path); */

/*     if (file == NULL) */
/*         throw_error("Permission denied.", 404); */

/*     fprintf(file, "# cpak config file\n\n\ */
/* # name of the project\n\ */
/* name=%s\n\ */
/* description=%s\n\ */
/* version=%s\n\ */
/* author=%s\n\ */
/* deps=\n", */
/*             pwd, description, version, author); */

/*     fclose(file); */

/*     if (!t_flag) { */
/*         cpak_log("Created 'cpak_project.conf'", INFO); */
/*         int len = sizeof(char) * 1024; */
/*         char *buf = malloc(len); */
/*         snprintf(buf, len, "Initialised new Project in: %s", pwd); */
/*         cpak_log(buf, SUCCESS); */
/*         free(buf); */
/*     } */

/*     return EXIT_SUCCESS; */
/* } */

int c_config(int overwrite) {
    if (!overwrite) {
        int config_exists = conf_exists();
        if (config_exists)
            throw_error("Cpak config exists, consider using the '-f' flag to override the existing config",
                        ERR_CONF_EXISTS);
    }

    char *path = get_config_path();
    char *conf_file_path = malloc(sizeof(char) * 255);
    char *template_file_path = malloc(sizeof(char) * 255);
    char *command = malloc(sizeof(char) * 1042);


    sprintf(command, "mkdir -p %s/templates/default", path);
    snprintf(conf_file_path, 254, "%s/cpak.conf", path);

    int r = system(command);
    if(r != EXIT_SUCCESS){
        throw_warning("Couldn't create cpak folder in config directory", -1);
    }

    FILE *config_FILE = fopen(conf_file_path, "w");

    if (!config_FILE)
        throw_error("Couldn't open config directory", -1);

    fprintf(config_FILE, "%s", CONFIG_FILE);
    fclose(config_FILE);

    snprintf(template_file_path, 254, "%s/templates/default/.gitignore", path);
    FILE *template_default_FILE = fopen(template_file_path, "w");

    if (!template_default_FILE)
        throw_error("Couldn't open template directory", ERR_CANT_ACCESS);

    fprintf(template_default_FILE, "%s", DEFAULT_TEMPLATE_GITIGNORE);
    fclose(template_default_FILE);

    free(command);
    free(path);
    free(conf_file_path);
    free(template_file_path);
    return (EXIT_SUCCESS);
}

int c_add(char *module){
    // check if git is installed:
    int is_git_installed = system("which git > /dev/null");
    if(is_git_installed != EXIT_SUCCESS){
        throw_error("Git can't be found on your system, please install it", ERR_GIT_MISSING);
    }

    // extracting <repo> from input (<user>/<repo>)
    char *copy_module = malloc(sizeof(char)*1024);
    char *url = malloc(sizeof(char) * 1024);
    char *command = malloc(sizeof(char)*1024);

    strcpy(copy_module, module);
    char *module_name = strtok(copy_module, "/");
    module_name = strtok(NULL, "\0");

    char *modules_path = malloc(sizeof(char)*256);
    if(g_flag_storeModulesGlobal){
        char *m = get_module_path();
        strcpy(modules_path, m);
        free(m);
    } else {
        strcpy(modules_path, "./cpak_modules");
    }

    char *abs_m_path = malloc(sizeof(char)*256);
    snprintf(abs_m_path, 255, "%s/%s", modules_path, module_name);

    char *cmd = malloc(sizeof(char)*510);
    snprintf(cmd, 510, "mkdir -p %s", modules_path);


    // TODO: create custom error codes
    int created = system(cmd);
    int created_m = system("mkdir -p ./cpak_modules");
    if(created != EXIT_SUCCESS || created_m != EXIT_SUCCESS) throw_error("Couldn't create modules directory, please check your permissions config", ERR_CANT_ACCESS);

    snprintf(url, 1023, "%s%s", VSC_PREFIX, module);
    snprintf(command, 1023, "git clone %s %s > /dev/null", url, abs_m_path);

    int error = system(command);

    if(error != EXIT_SUCCESS) {
        char *path = malloc(sizeof(char)*256);
        snprintf(path, 255, "%s", abs_m_path);
        if(f_exists(path)){
            free(path);
            throw_error("Module already installed", ERR_MODULE_EXISTS);
        }
        free(path);
        throw_error("Couldn't install module using git, please verify git is installed", ERR_GIT_MISSING);
        return EXIT_FAILURE;
    }

    char *feedback = malloc(sizeof(char) * 1024);
    snprintf(feedback, 1023, "Installed module '%s' in %s", module, abs_m_path);
    cpak_log(feedback, SUCCESS);

    if(g_flag_storeModulesGlobal){
        char *c = malloc(sizeof(char) * 1024);
        snprintf(c, 1023, "ln -s %s ./cpak_modules/%s", abs_m_path, module_name);
        if(system(c) != EXIT_SUCCESS){
            free(c);
            throw_error("Couldn't link to globally installed module, consider adding a soft link yourself", ERR_CANT_ACCESS);
        }
        free(c);
    }

    free(url);
    free(command);
    free(feedback);
    free(cmd);
    free(copy_module);
    free(abs_m_path);
    return EXIT_SUCCESS;
}

int c_remove(char *module){
    char *path = malloc(sizeof(char) * 255);

    if(g_flag_storeModulesGlobal){
        char *m = get_module_path();
        strcpy(path, m);
        free(m);
    } else {
        strcpy(path, "./cpak_modules");
    }

    if(!f_exists(path)){
        free(path);
        throw_error("Can't remove module - Module doesn't exist", ERR_MODULE_DOESNT_EXIST);
    }

    char *cmd = malloc(sizeof(char) * 1024);
    snprintf(cmd, 1023, "rm -rf %s", path);

    int error = system(cmd);
    if(error != EXIT_SUCCESS){
        throw_error("Can't remove module", ERR_MODULE_DOESNT_EXIST);
    } else {
      cpak_log("Uninstalled module", SUCCESS);
    }

    if(g_flag_storeModulesGlobal){
        char *c = malloc(sizeof(char) * 1024);
        snprintf(c, 1023, "unlink ./cpak_modules/%s", module);
        if(system(c) != EXIT_SUCCESS){
            free(c);
            throw_error("Couldn't unlink globally installed module, consider removing the soft link yourself", ERR_CANT_ACCESS);
        }
        free(c);
    }

    char *feedback = malloc(sizeof(char)*1024);
    snprintf(feedback, 1023, "Removed module '%s' from '%s'", module, path);
    cpak_log(feedback, SUCCESS);

    free(feedback);
    free(path);
    free(cmd);

    return EXIT_SUCCESS;
}

int c_upgrade(char *module){
    char *path = malloc(sizeof(char) * 256);
    char *modules_path = malloc(sizeof(char)*256);

    if(g_flag_storeModulesGlobal){
        char *m = get_module_path();
        strcpy(modules_path, m);
        free(m);
    } else {
        strcpy(modules_path, "./cpak_modules");
    }

    snprintf(path, 255, "%s/%s", modules_path, module);

    if(!f_exists(path)){
        free(path);
        throw_error("Can't update module - Module doesn't exist, consider installing it", ERR_MODULE_DOESNT_EXIST);
    }

    char *cmd = malloc(sizeof(char) * 1024);
    snprintf(cmd, 1023, "cd %s && git pull", path);

    int error = system(cmd);
    if(error != EXIT_SUCCESS){
        throw_error("Can't update module", -1);
    }

    char *feedback = malloc(sizeof(char)*1024);
    snprintf(feedback, 1023, "Upgraded module: '%s' in '%s'", module, path);
    cpak_log(feedback, SUCCESS);

    free(feedback);
    free(path);
    free(cmd);
    return EXIT_SUCCESS;
}
