#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpak_utils.h"
#include "cpak_project_config.h"

void project_conf_free(Project_config *conf){
    free(conf->name);
    free(conf->version);
    for(int i = 0; i < conf->amount_deps; i++){
        free(conf->deps[i]);
    }
    free(conf);
    conf = NULL;
}

Project_config *project_conf_get_config(char *path) {
    Project_config *pc;
    pc = malloc(sizeof *pc);
    pc->name = malloc(sizeof(char) * 255);
    pc->version = malloc(sizeof(char) * 255);
    pc->cwd = malloc(sizeof(path));
    pc->cwd = path;
    cpak_log(pc->cwd, DEBUG);
    pc->deps = malloc(sizeof(char *) * 15);
    FILE *file = fopen(path, "r");

    // TODO: needs check if file has correct file ending (.conf)

    if (file == NULL) {
        //project_conf_free(pc);
        fclose(file);
        throw_error("Can't read or find project config", P_MISSING_CONFIG);
    }

    char cur_line[255];

    while (fgets(cur_line, 255, file)) {
        if (s_is_empty(cur_line)) continue;
        if (s_starts_with(cur_line, "#")) continue;
        if (s_starts_with(cur_line, "name=")) {
            sscanf(cur_line, "name=%s\n", pc->name);
            continue;
        };
        if (s_starts_with(cur_line, "version=")) {
            sscanf(cur_line, "version=%s\n", pc->version);
            continue;
        }
        if (s_starts_with(cur_line, "deps=")) {
            sscanf(cur_line, "deps=%[^\n]", cur_line);
            char *ptr = strtok(cur_line, " ");
            int i = 0;
            while (ptr != NULL) {
                pc->deps[i] = malloc(sizeof(ptr));
                strcpy(pc->deps[i], ptr);
                i++;
                ptr = strtok(NULL, " ");
            }
            pc->amount_deps = i;
        };
    }


    if (s_is_empty(pc->name)) {
        throw_warning("Project name is undefined!", P_MISSING_NAME);
    }

    if (s_is_empty(pc->version)) {
        throw_warning("Project version is undefined!", P_MISSING_VERSION);
    }


    fclose(file);
    return pc;
}
