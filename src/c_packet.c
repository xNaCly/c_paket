#include "core/project_config.h"
#include <stdio.h>
#include <stdlib.h>

char text[] = "example_project/config.c_paket";
int main() {
  Project_config *pc = project_conf_get_config(text);
  printf("%s\n", pc->name);
  printf("%s\n", pc->cwd);
  free(pc);
}
