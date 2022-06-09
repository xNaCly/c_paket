#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpak_config.h"
#include "cpak_utils.h"

int g_flag_colors = 1;
int g_flag_storeModulesGlobal = 1;

void get_config() {
  char *path = malloc(sizeof(char) * 255);
  char *config_path = get_config_path();

  snprintf(path, 254, "%s/cpak.conf", config_path);
  free(config_path);

  FILE *file = fopen(path, "r");

  if (s_is_empty(path) || file == NULL) {
    return;
  }

  char cur_line[1024];

  while (fgets(cur_line, 1023, file)) {
    if (s_is_empty(cur_line))
      continue;
    else if (s_starts_with(cur_line, "#"))
      continue;
    else if (s_starts_with(cur_line, "colors=")) {
      char temp[1024 * 4];
      sscanf(cur_line, "colors=%1024s\n", temp);
      if (s_is_equal(temp, "true")) {
        g_flag_colors = 1;
      } else if (s_is_equal(temp, "false")) {
        g_flag_colors = 0;
      } else {
        cur_line[strlen(cur_line) - 1] = '\0';
        sprintf(temp, "'%s' is not a known value for key: 'color'", cur_line);
        throw_warning(temp, ERR_CONF_UNKNOWN_VALUE);
      }
      continue;
    } else if (s_starts_with(cur_line, "storeModulesGlobal=")) {
      char temp[1024 * 4];
      sscanf(cur_line, "storeModulesGlobal=%255s\n", temp);
      if (s_is_equal(temp, "true")) {
        g_flag_storeModulesGlobal = 1;
      } else if (s_is_equal(temp, "false")) {
        g_flag_storeModulesGlobal = 0;
      } else {
        sprintf(temp, "'%s' is not a known value for key: 'color'", cur_line);
        throw_warning(temp, ERR_CONF_UNKNOWN_VALUE);
      }
      continue;
    } else {
      char temp[255 * 5];
      cur_line[strlen(cur_line) - 1] = '\0';
      sprintf(temp, "'%s' is not a known key value pair", cur_line);
      throw_warning(temp, ERR_CONF_UNKNOWN_KEY);
    }
  }
  free(path);
  fclose(file);
}
