#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/core/cpak_cli.h"
#include "../src/core/cpak_utils.h"

int t_tests = 0;
int s_tests = 0;
int f_tests = 0;

void t_add(){
  printf("\n");
  t_tests += 1;
  cpak_log("running t_add", INFO);
  int r_value = c_add("xnacly/xutils");
  if(r_value != EXIT_SUCCESS){
    throw_warning("add command failed", -1);
    f_tests += 1;
    return;
  }
  cpak_log("add cmd worked!", SUCCESS);
  cpak_log("ran t_add", INFO);
  s_tests += 1;
}

void t_upgrade(){
  printf("\n");
  t_tests += 1;
  cpak_log("running t_upgrade", INFO);
  int r_value = c_upgrade("xutils");
  if(r_value != EXIT_SUCCESS){
    throw_warning("upgrade command failed", -1);
    f_tests += 1;
    return;
  }
  cpak_log("upgrade cmd worked!", SUCCESS);
  cpak_log("ran t_upgrade", INFO);
  s_tests += 1;
}

void t_remove(){
  printf("\n");
  t_tests += 1;
  cpak_log("running t_remove", INFO);
  int r_value = c_remove("xutils");
  if(r_value != EXIT_SUCCESS){
    throw_warning("remove command failed", -1);
    f_tests += 1;
    return;
  }
  cpak_log("remove cmd worked!", SUCCESS);
  cpak_log("ran t_remove", INFO);
  s_tests += 1;
}

void t_config() {
  printf("\n");
  t_tests += 1;
  cpak_log("running t_config", INFO);
  int r_value = c_config();
  if(r_value != EXIT_SUCCESS){
    throw_warning("remove command failed", -1);
    f_tests += 1;
    return;
  }
  cpak_log("config cmd worked!", SUCCESS);
  cpak_log("ran t_config", INFO);
  s_tests += 1;
}

/* void t_init() { */
/*   cpak_log("running t_init", INFO); */
/*   int r_value = c_init("./tests/output"); */
/*   assert(r_value == EXIT_SUCCESS && "init command failed"); */
/*   cpak_log("init cmd worked!", SUCCESS); */
/*   cpak_log("ran t_help", INFO); */
/* } */

void t_help() {
  printf("\n");
  t_tests += 2;
  cpak_log("running t_help", INFO);
  int r_value = c_help("all");
  if(r_value != EXIT_SUCCESS){
    throw_warning("help command failed", -1);
    f_tests += 1;
  } else {
    s_tests += 1;
  }
  cpak_log("help all cmd worked!", SUCCESS);
  int r1_value = c_help("tester");
  if(r1_value == EXIT_SUCCESS){
    throw_warning("help command failed", -1);
    f_tests += 1;
    return;
  } else {
    s_tests += 1;
  }

  cpak_log("help cmd worked!", SUCCESS);
  cpak_log("ran t_help", INFO);
}

void t_template() {
  t_tests += 1;
  cpak_log("running t_template", INFO);
  int r_value = c_bootstrap("default", "./tests/output");
  if(r_value != EXIT_SUCCESS){
    throw_warning("bootstrap command failed", -1);
    f_tests += 1;
    return;
  }
  cpak_log("bootstrap default template worked!", SUCCESS);
  cpak_log("ran t_template", INFO);
  s_tests += 1;
  printf("\n");
}

void t_clean_up(){
  printf("\n");
  cpak_log("Overview:", INFO);
  char *success_tests = malloc(sizeof(char)*1024);
  char *failed_tests = malloc(sizeof(char)*1024);
  double success_test_percent = s_tests*100 / (double)t_tests;
  double failed_test_percent = f_tests*100 / (double)t_tests;
  snprintf(success_tests, 1023, "successful tests: %d/%d [%f%%]", s_tests, t_tests, success_test_percent);
  snprintf(failed_tests, 1023, "failed tests: %d/%d [%f%%]", f_tests, t_tests, failed_test_percent);
  cpak_log(success_tests, SUCCESS);
  cpak_log(failed_tests, ERROR);
  free(success_tests);
  free(failed_tests);
}

int main() {
  /* t_init(); */
  t_add();
  t_upgrade();
  t_remove();
  t_config();
  t_template();
  t_help();
  t_clean_up();
  if(f_tests != 0) return EXIT_FAILURE;
  return EXIT_SUCCESS;
}
