#include <stdio.h>
#include <stdlib.h>
#include "core/project_config.h"

char text[] = "test.c_paket";
int main() {
  Project_config *pc = project_conf_get_config(text);
  printf("%s\n", pc->name);
  free(pc);
}
