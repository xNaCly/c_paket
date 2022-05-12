#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/core/cpak_cli.h"
#include "../src/core/cpak_utils.h"

void t_template() {
  cpak_log("running t_template", INFO);
  int r_value = bootstrap("default", "./tests/output");
  assert(r_value == 0 && "bootstraping from template dir failed");
  cpak_log("ran t_template", INFO);
}

int main() {
  t_template();
  return EXIT_SUCCESS;
}
