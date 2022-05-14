#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "cpak_cli.h"
#include "cpak_utils.h"

int bootstrap(char *template_name, char *outdir) {
  char *template_path = malloc(sizeof(char) * 510);
  char *path = malloc(sizeof(char) * 510);

  char *HOME_DIR = getenv("HOME");

  if (getenv("XDG_CONFIG_DIR") == NULL) {
    sprintf(path, "%s/.config/cpak/templates/%s", HOME_DIR, template_name);
    strcpy(template_path, path);
  }

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

int help(char *command){
  char *T_CPAK = getenv("CPAK_TESTING");
  int t_flag = T_CPAK != NULL && s_is_equal(T_CPAK, "true") ? 1 : 0;
  if(s_is_equal(command, "all")){
    printf("%s", t_flag ? "" : USAGE"\n");
    return EXIT_SUCCESS;
  } else {
    printf("%s", t_flag ? "" : USAGE"\n");
    return EXIT_FAILURE;
  }
}
