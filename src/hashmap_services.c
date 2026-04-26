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

char* get_folder(char* ext){
    struct Mapping *temp;
    HASH_FIND_STR(map , ext , temp);
    if(temp == NULL){
      fprintf(stderr,"Something Went Wrong , at %s",ext);
      return NULL;
    }
    return temp->folder;
    }
