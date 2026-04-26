#include"include.h"


char* expand_config_path(const char* path){
  wordexp_t exp;

  if(wordexp(path, &exp, WRDE_NOCMD) != 0)
    {
      return NULL;
    }

  char* expanded = strdup(exp.we_wordv[0]);
  wordfree(&exp);
  return expanded;
}
RETURN read_config_file(const char*path){
  FILE* fp = fopen(path,"r");
  if(!fp)
    {
      fprintf("failed to read config file:%s!\n");
      return FAIL;
    }

  char buf[256];
  while(fgets(line, sizeof(line), file))
    {
      
    }

  fclose(fp);

}
