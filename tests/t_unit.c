#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/core/cpak_config.h"
#include "../src/core/cpak_utils.h"

void t_config() {
  cpak_log("running t_config", INFO);
  get_config();

  assert(g_flag_colors == 1 && "reading config key colors failed");
  cpak_log("colors value correct!", SUCCESS);

  assert(flag_storeModulesGlobal == 1 &&
         "reading config key storeModulesGlobal failed");
  cpak_log("storeModulesGlobal correct!", SUCCESS);

  cpak_log("ran t_config", INFO);
}

/* void t_project_config() { */
/*   cpak_log("running t_project_config", INFO); */
/*   char example_config_path[] = "./tests/example_project/cpak_project.conf"; */
/*   Project_config *pc = project_conf_get_config(example_config_path); */

/*   assert(s_is_equal(pc->name, "example_app") && "reading project name failed"); */
/*   cpak_log("name correct!", SUCCESS); */

/*   assert(s_is_equal(pc->version, "v0.0.1") && "reading project version failed"); */
/*   cpak_log("version correct!", SUCCESS); */

/*   assert(s_is_equal(pc->author, "https://github.com/xnacly") && */
/*          "reading project author failed"); */
/*   cpak_log("author correct!", SUCCESS); */

/*   assert(s_is_equal(pc->desc, "a very simple program to work") && */
/*          "reading project description failed"); */
/*   cpak_log("description correct!", SUCCESS); */

/*   assert(s_is_equal(pc->deps[0], "xnacly/pgme") && */
/*          "reading project deps failed"); */
/*   assert(s_is_equal(pc->deps[1], "xnacly/xc") && "reading project deps failed"); */
/*   cpak_log("all dependencies correct!", SUCCESS); */

/*   assert(pc->amount_deps == 2 && "dependency amount incorrect"); */
/*   cpak_log("dependency amount correct!", SUCCESS); */

/*   project_conf_destroy(pc); */

/*   cpak_log("ran t_project_config", INFO); */
/* } */

int main() {
  t_config();
  /* t_project_config(); */
  return EXIT_SUCCESS;
}
