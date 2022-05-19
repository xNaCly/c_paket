#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  char *description = malloc(sizeof(char) * 255);
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

  if (!t_flag)
    cpak_log("Created 'cpak_project.conf'", INFO);

  free(description);

  if (!t_flag) {
    int len = sizeof(char) * 1024;
    char *buf = malloc(len);
    snprintf(buf, len, "Initialised new Project in: %s", pwd);
    cpak_log(buf, SUCCESS);
    free(buf);
  }

  return EXIT_SUCCESS;
}

int c_config() { 
  cpak_log("generate config here!", DEBUG);
  return (EXIT_SUCCESS); }
