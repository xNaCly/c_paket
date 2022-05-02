#include "../src/core/cpak_project_config.h"
#include "../src/core/cpak_utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void t_project_config(){
  cpak_log("running t_project_config", 0);
  char example_config_path[] = "example_project/cpak_project.conf";
  Project_config *pc = project_conf_get_config(example_config_path);

  assert(s_is_equal(pc->name, "example_app") &&
         "reading project name failed");
  cpak_log("name correct!", SUCCESS);

  assert(s_is_equal(pc->version, "v0.0.1")  &&
         "reading project version failed");
  cpak_log("version correct!", SUCCESS);

  assert(s_is_equal(pc->deps[0], "xnacly/pgme")  &&
         "reading project deps failed");
  assert(s_is_equal(pc->deps[1], "xnacly/xc")  &&
         "reading project deps failed");
  cpak_log("all dependencies correct!",SUCCESS);

  assert(pc->amount_deps == 2 && "dependency amount incorrect");
  cpak_log("dependency amount correct!", SUCCESS);

  for(int i = 0; i < pc->amount_deps; i++){
    free(pc->deps[i]);
  }
  free(pc->deps);
  free(pc);

  cpak_log("t_project_config ran successfully!", SUCCESS);
}

int main() {
  t_project_config();
  return EXIT_SUCCESS;
}
