#include "include.h"
struct Mapping *map = NULL;

RETURN build_extension_folder_hashmap(){

    // build up the hashmap
    for(int i = 0 ; i < defaults_size ; i++){
        HASH_ADD_STR(map , ext , &defaults[i]);
    }
    //Verify entries
    struct Mapping *temp;
    for(int i = 0 ; i < defaults_size ; i++){
        HASH_FIND_STR(map , defaults[i].ext , temp);
    }

    return SUCCESS;
}
RETURN build_extension_folder_hashmap_from_config(){
  for(size_t i = 0;i<config_size;++i)
    {
      if(config[i].dir[0] == '\0') break;

      for(int j = 0;j< 20 && config[i].exts[j] != NULL;++j)
	{
	  struct Mapping* m = malloc(sizeof(struct Mapping));
	  if(!m) return FAIL;

	  strcpy(m->ext, config[i].exts[j]);
	  m->ext[sizeof(m->ext)-1] = '\0';

	  strcpy(m->folder,config[i].dir);
	  m->folder[sizeof(m->folder)-1] = '\0';

	  HASH_ADD_STR(map,ext,m);
	}
    }

  return SUCCESS;
}
char* get_folder(char* ext){
    struct Mapping *temp;
    HASH_FIND_STR(map , ext , temp);
    if(temp == NULL){
      fprintf(stderr,"Something Went Wrong , at %s",ext);
      return NULL;
    }
    return temp->folder;
    }
