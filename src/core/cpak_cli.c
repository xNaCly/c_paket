#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "cpak_cli.h"
#include "cpak_utils.h"

int bootstrap(char *template_name, char *outdir) {
  char *CONFIG_HOME = malloc(sizeof(char) * 255);
  char *HOME_DIR = malloc(sizeof(char) * 255);
  char *template_path = malloc(sizeof(char) * 510);
  char *path = malloc(sizeof(char) * 510);

  CONFIG_HOME = getenv("XDG_CONFIG_HOME");
  HOME_DIR = getenv("HOME");

  if (HOME_DIR == NULL || s_is_empty(HOME_DIR)) {
    strcpy(HOME_DIR, "~");
  }

  if (CONFIG_HOME == NULL || s_is_empty(CONFIG_HOME)) {
    sprintf(path, "%s/.config", HOME_DIR);
    CONFIG_HOME = malloc(sizeof(path));
    strcpy(CONFIG_HOME, path);
  }

  sprintf(template_path, "%s/cpak/templates/%s", CONFIG_HOME, template_name);

  struct stat st;
  if (stat(template_path, &st) != 0) {
    printf("%s - ", template_path);
    throw_error("Can't read template", TEMPLATE_MISSING);
  }

  char *command = malloc(sizeof(char) * 510);
  sprintf(command, "cp -r %s/* %s", template_path, outdir);

  int r = system(command);

  if (r == EXIT_SUCCESS)
    cpak_log("Successfully bootstrapped project", SUCCESS);

  free(CONFIG_HOME);
  free(HOME_DIR);
  free(template_path);
  free(path);
  free(command);
  return r;
}
