#include "core/project_config.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char text[] = "example_project/config.c_paket";
int main() {
  Project_config *pc = project_conf_get_config(text);
  printf("c_paket\nname=%s\nversion=%s\n", pc->name, pc->version);
  assert(strcmp(pc->name, "example_app") == 0 &&
         "Project name couldnt be read!");

  free(pc);
}
