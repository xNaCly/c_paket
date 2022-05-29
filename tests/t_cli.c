#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/core/cpak_cli.h"
#include "../src/core/cpak_utils.h"

void t_config() {
  cpak_log("running t_config", INFO);
  int r_value = c_config();
  assert(r_value == EXIT_SUCCESS && "config command failed");
  cpak_log("config cmd worked!", SUCCESS);
  cpak_log("ran t_config", INFO);
}

/* void t_init() { */
/*   cpak_log("running t_init", INFO); */
/*   int r_value = c_init("./tests/output"); */
/*   assert(r_value == EXIT_SUCCESS && "init command failed"); */
/*   cpak_log("init cmd worked!", SUCCESS); */
/*   cpak_log("ran t_help", INFO); */
/* } */

void t_help() {
  cpak_log("running t_help", INFO);
  int r_value = c_help("all");
  assert(r_value == EXIT_SUCCESS && "help all command failed");
  cpak_log("help all cmd worked!", SUCCESS);
  int r1_value = c_help("tester");
  assert(r1_value == EXIT_FAILURE && "help command failed");
  cpak_log("help cmd worked!", SUCCESS);
  cpak_log("ran t_help", INFO);
}

void t_template() {
  cpak_log("running t_template", INFO);
  int r_value = c_bootstrap("default", "./tests/output");
  assert(r_value == EXIT_SUCCESS && "bootstrap default template failed");
  cpak_log("bootstrap default template worked!", SUCCESS);
  cpak_log("ran t_template", INFO);
}

int main() {
  /* t_init(); */
  t_config();
  t_template();
  t_help();
  return EXIT_SUCCESS;
}
