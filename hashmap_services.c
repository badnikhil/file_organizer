#include "include.h"
#include "extensions.c"
struct Mapping *map = NULL;

enum RETURN build_extension_folder_hashmap(){

    int size = sizeof(defaults) / sizeof(defaults[0]);
    // build up the hashmap
    for(int i = 0 ; i < size ; i++){
        HASH_ADD_STR(map , ext , &defaults[i]);
    }
    //Verify entries
    struct Mapping *temp;
    for(int i = 0 ; i < size ; i++){
        HASH_FIND_STR(map , defaults[i].ext , temp);
    }

    return SUCCESS;
    }

char* get_folder(char* ext){
    struct Mapping *temp;
    HASH_FIND_STR(map , ext , temp);
    if(temp == NULL){
        printf("Something Went Wrong , at %s",ext);
        return NULL;
    }
    return temp->folder;
    }