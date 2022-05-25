#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./core/cpak_cli.h"
#include "./core/cpak_config.h"
#include "./core/cpak_utils.h"
#include "cpak.h"

void help_wrapper() {
    printf("cpak-%s\n", CPAK_VERSION);
    c_help("all");
}

Cli_arguments *parse_arguments(int arguments_amount, char **arguments) {
    Cli_arguments *ca;
    ca = malloc(sizeof(*ca));

    if (arguments_amount == 1) {
        ca->cmd = UNDEF;
        return ca;
    }
    char *cmd = arguments[1];

    if (s_is_equal(cmd, "help") || s_is_equal(cmd, "h")) {
        ca->cmd = HELP;
    } else if (s_is_equal(cmd, "bootstrap") || s_is_equal(cmd, "b")) {
        ca->cmd = BOOTSTRAP;
    } else if (s_is_equal(cmd, "config") || s_is_equal(cmd, "c")) {
        ca->cmd = CONFIG;
    } else if (s_is_equal(cmd, "init") || s_is_equal(cmd, "i")) {
        ca->cmd = INIT;
    } else if (s_is_equal(cmd, "add") || s_is_equal(cmd, "a")) {
        ca->cmd = ADD;
    } else if (s_is_equal(cmd, "remove") || s_is_equal(cmd, "r")) {
        ca->cmd = REMOVE;
    } else if (s_is_equal(cmd, "upgrade") || s_is_equal(cmd, "u")) {
        ca->cmd = UPGRADE;
    } else if (s_is_equal(cmd, "version") || s_is_equal(cmd, "v")) {
        ca->cmd = VERSION;
    } else {
        ca->cmd = UNKNOWN;
    }

    if (ca->cmd != VERSION) {
        if (arguments_amount >= 2) {
            ca->c_cmd = malloc(sizeof(arguments[2]));
            ca->c_cmd = arguments[2];
        } else {
            ca->c_cmd = "";
            // throw_error("Not enough arguments, use help <command> to view in-depth
            // "
            //             "information about <command>",
            //             NOT_ENOUGH_ARGUMENTS);
        }
    }

    return ca;
}

int main(int argc, char *argv[]) {
    int does_conf_exists = conf_exists();
    Cli_arguments *arg = parse_arguments(argc, argv);
    if (!does_conf_exists && arg->cmd != CONFIG)
        throw_warning("can't find cpak's config file, consider generating the "
                      "default config using: 'cpak config'",
                      CONF_MISSING_CONFIG);
    get_config();

    switch (arg->cmd) {
        case BOOTSTRAP:
            c_bootstrap(arg->c_cmd, ".");
            break;
        case INIT:
            if (!s_is_empty(arg->c_cmd)) {
                c_init(arg->c_cmd);
            } else {
                throw_warning("Not enough Arguments providen", NOT_ENOUGH_ARGUMENTS);
                c_help("init");
            }
            break;
        case CONFIG: {
            int o = 0;
            if (!s_is_empty(arg->c_cmd) && s_is_equal(arg->c_cmd, "override")) {
                o = 1;
            }
            c_config(o);
            break;
        }
        case ADD:
            cpak_log("ADD!", DEBUG);
            break;
        case REMOVE:
            cpak_log("REMOVE!", DEBUG);
            break;
        case UPGRADE:
            cpak_log("UPGRADE!", DEBUG);
            break;
        case VERSION:
            cpak_log("cpak-" CPAK_VERSION, INFO);
            exit(EXIT_SUCCESS);
        case UNDEF:
            throw_warning("Not enough Arguments providen", NOT_ENOUGH_ARGUMENTS);
            help_wrapper();
            break;
        case HELP:
            if (!s_is_empty(arg->c_cmd)) {
                c_help(arg->c_cmd);
            } else {
                help_wrapper();
            }
            break;
        case UNKNOWN:
            throw_warning("Unknown Argument", UNKNOWN_ARGUMENT);
            help_wrapper();
            break;
        default:
            help_wrapper();
            break;
    }

    free(arg);
}
