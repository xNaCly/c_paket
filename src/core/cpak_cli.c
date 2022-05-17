#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "cpak_cli.h"
#include "cpak_config.h"
#include "cpak_utils.h"

int c_bootstrap(char *template_name, char *outdir) {
  char *template_path = malloc(sizeof(char) * 255);
  char *path = get_cpak_config_path();

  snprintf(template_path, 255, "%s/templates/%s", path, template_name);

  struct stat st;
  if (stat(template_path, &st) != 0) {
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

int c_help(char *command){
  char *T_CPAK = getenv("CPAK_TESTING");
  int t_flag = T_CPAK != NULL && s_is_equal(T_CPAK, "true") ? 1 : 0;
  if(s_is_equal(command, "all")){
    printf("%s", t_flag ? "" : USAGE"\n");
  } else if(s_is_equal(command, "help")){
    printf("%s", U_HELP);
  } else if(s_is_equal(command, "init")){
    printf("%s", U_INIT);
  } else if(s_is_equal(command, "add")){
    printf("%s", U_ADD);
  } else if(s_is_equal(command, "remove")){
    printf("%s", U_REMOVE);
  } else if(s_is_equal(command, "bootstrap")){
    printf("%s", U_BOOTSTRAP);
  } else if(s_is_equal(command, "version")){
    printf("%s", U_VERSION);
  } else {
    printf("%s", t_flag ? "" : USAGE"\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

//int c_init(char *outdir){
//  return EXIT_SUCCESS;
//}
