#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "cpak_config.h"
#include "cpak_utils.h"

Config *get_config(char *path){
  Config *c;
  c = (Config*)malloc(sizeof *c);
  FILE *file = fopen(path, "r");

  if (file == NULL)
    throw_error("Can't read or find cpak config", CONF_MISSING_CONFIG);
  
  char cur_line[255]; 

  while(fgets(cur_line, 255, file)){
    if(s_is_empty(cur_line)) continue;
    else if(s_starts_with(cur_line, "#")) continue;
    else if(s_starts_with(cur_line, "colors=")){
      char temp[255*5];
      sscanf(cur_line, "colors=%s\n", temp);
      if(s_is_equal(temp, "true")){
        c->colors = 1;
      } else if(s_is_equal(temp, "false")) {
        c->colors = 0;
      } else {
        cur_line[strlen(cur_line)-1] = '\0';
        sprintf(temp, "'%s' is not a known value for key: 'color'", cur_line);
        throw_warning(temp, CONF_UNKNOWN_VALUE);
      }
      continue;
    }
    else if(s_starts_with(cur_line, "storeModulesGlobal=")){
      char temp[255*5];
      sscanf(cur_line, "storeModulesGlobal=%s\n", temp);
      if(s_is_equal(temp, "true")){
        c->storeModulesGlobal = 1;
      } else if(s_is_equal(temp, "false")){
        c->storeModulesGlobal = 0;
      } else {
        sprintf(temp, "'%s' is not a known value for key: 'color'", cur_line);
        throw_warning(temp, CONF_UNKNOWN_VALUE);
      }
      continue;
    } else {
      char temp[255*5];
      cur_line[strlen(cur_line)-1] = '\0';
      sprintf(temp, "'%s' is not a known key value pair", cur_line);
      throw_warning(temp, CONF_UNKNOWN_KEY);
    } 
  }

  return c;
}
