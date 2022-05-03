#ifndef CPAK_CONFIG_H
#define CPAK_CONFIG_H

typedef struct {
    int colors;
    int storeModulesGlobal;
} Config;

Config *get_config(char *path);

#endif
