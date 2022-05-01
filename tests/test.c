#include "../src/core/project_config.h"
#include "../src/core/c_p_util.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void t_project_config(){
  printf("Running t_project_config test...\n");
  char example_config_path[] = "example_project/config.c_paket";
  Project_config *pc = project_conf_get_config(example_config_path);

  assert(s_is_equal(pc->name, "example_app") &&
         "reading project name failed");
  printf("name correct!\n");

  assert(s_is_equal(pc->version, "v0.0.1")  &&
         "reading project version failed");
  printf("version correct!\n");

  assert(s_is_equal(pc->deps[0], "xnacly/pgme")  &&
         "reading project deps failed");
  assert(s_is_equal(pc->deps[1], "xnacly/xc")  &&
         "reading project deps failed");
  printf("dependencies correct!\n");

  assert(pc->amount_deps == 2 && "dependency amount incorrect");
  printf("dependency amount correct!\n");

  free(pc);

  printf("t_project_config ran successfully!\n");
}

int main() {
  t_project_config();
  return EXIT_SUCCESS;
}
