#include "../src/core/cpak_project_config.h"
#include "../src/core/cpak_config.h"
#include "../src/core/cpak_utils.h"
#include "../src/core/cpak_cli.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void t_config() {
    cpak_log("running t_config", 0);
    char example_config_path[] = "./tests/example_config/cpak.conf";
    Config *c = get_config(example_config_path);

    assert(c->colors == 1 && "reading config key colors failed");
    cpak_log("colors value correct!", SUCCESS);

    assert(c->storeModulesGlobal == 1 && "reading config key storeModulesGlobal failed");
    cpak_log("storeModulesGlobal correct!", SUCCESS);

    free(c);
    cpak_log("ran t_config", 0);
}

void t_project_config() {
    cpak_log("running t_project_config", 0);
    char example_config_path[] = "./tests/example_project/cpak_project.conf";
    Project_config *pc = project_conf_get_config(example_config_path);

    assert(s_is_equal(pc->name, "example_app") &&
           "reading project name failed");
    cpak_log("name correct!", SUCCESS);

    assert(s_is_equal(pc->version, "v0.0.1") &&
           "reading project version failed");
    cpak_log("version correct!", SUCCESS);

    assert(s_is_equal(pc->deps[0], "xnacly/pgme") &&
           "reading project deps failed");
    assert(s_is_equal(pc->deps[1], "xnacly/xc") &&
           "reading project deps failed");
    cpak_log("all dependencies correct!", SUCCESS);

    assert(pc->amount_deps == 2 && "dependency amount incorrect");
    cpak_log("dependency amount correct!", SUCCESS);

    project_conf_free(pc);

    cpak_log("ran t_project_config", 0);
}

void t_template() {
    cpak_log("running t_template", 0);
    int r_value = bootstrap("default", "./tests/output");
    assert(r_value == 0 && "bootstraping from template dir failed");
    cpak_log("ran t_template", 0);
}

int main() {
    t_config();
    printf("\n");
    t_project_config();
    printf("\n");
    t_template();
    return EXIT_SUCCESS;
}
