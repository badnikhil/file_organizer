#include"include.h"

struct Config* config = NULL;
size_t config_size = 7;

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
int _read_dir_name(char* dir_name, char* buffer){
  int pos = 0;
  while(buffer[pos] != ':')
    {      
      if(pos >= 64) return -1;
      if(buffer[pos] == '\0') return -1;
      
      dir_name[pos] = buffer[pos];
      ++pos;
    }
  dir_name[pos] = '\0';
  return pos;
}
RETURN read_config_file(const char*path){
  FILE* fp = fopen(path,"r");
  if(!fp)
    {
      fprintf(stderr,"failed to read config file:%s!\n");
      return FAIL;
    }

  config = malloc(config_size* sizeof(struct Config));
  char buf[256];

  size_t current_element = 0;
  while(fgets(buf, sizeof(buf), fp))
    {
      buf[strcspn(buf, "\n")] = '\0';
      
      char dir_name[64];
      int delim_pos = _read_dir_name(dir_name, buf);
      if(delim_pos == -1)
	{
	  fclose(fp);
	  return FAIL;
	}
      
      
      int ext_count = 0;
      char* ext_line = buf+delim_pos+1;
      size_t len = strlen(ext_line);
      for(int i = 0;i<len;++i)
	{
	  if(ext_line[i] == ',')ext_count++;
	}
      ext_count++; //count the last one

      char (*exts)[20] = malloc(ext_count* sizeof(*exts));
      if(exts == NULL)
	{
	  fclose(fp);
	  perror("malloc failed");
	  return FAIL;
	}

      int i = 0, j = 0;
      while(*ext_line != '\0')
	{	  
	  if(*ext_line == ',')
	    {
	      exts[i][j] = '\0';
	      i++;
	      j = 0;	      
	    }
	  else
	    {
              if(j < 19) exts[i][j++] = *ext_line;
            }
	  
	  ext_line++;
	}
      if(j > 0) exts[i][j] = '\0';

      int actual_ext_count = i + (j > 0 ? 1 : 0);
      if (actual_ext_count > 20) actual_ext_count = 20;
      
      if(current_element >= config_size)
	{
	  size_t new_size = config_size* 2;
	  struct Config* new_config = realloc(config,new_size* sizeof(struct Config));
	  if(!new_config)
	    {
	      perror("realloc failed");
	      free(exts);
	      fclose(fp);
	      return FAIL;
	    }
	  config = new_config;
	  config_size = new_size;
	}

      strcpy(config[current_element].dir,dir_name);
      config[current_element].dir[sizeof(config[current_element].dir) - 1] = '\0';

      for(int k = 0; k< actual_ext_count; k++)
	{
	  config[current_element].exts[k] = strdup(exts[k]);
	  if(!config[current_element].exts[k])
	    {
	      perror("strdup failed");
	      for (int m = 0; m < k; m++) free(config[current_element].exts[m]);
	      free(exts);
	      fclose(fp);
	      return FAIL;
	    }	
	}
      for (int k = actual_ext_count; k < 20; k++)
	{
            config[current_element].exts[k] = NULL;
        }
      free(exts);
      current_element++;
      
    }

  fclose(fp);
  return SUCCESS;
}
void free_config(void)
{
  if(config == NULL) return;

  for (size_t i = 0; i < config_size; i++)
    {
      if (config[i].dir[0] == '\0') break;
      
      for (int j = 0; j < 20 && config[i].exts[j] != NULL; j++)
	{
	  free(config[i].exts[j]);
	}
    }
  
  free(config);
  config = NULL;
  config_size = 0;
}
