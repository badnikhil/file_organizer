#pragma once
#include <uthash/src/uthash.h>
#include <stdio.h>
struct Mapping {
    char ext[10];       // key
    char folder[20];    // value
    UT_hash_handle hh;
};
enum RETURN{
    SUCCESS = 0,
    FAIL = 1,
    SOMETHING_WRONG = 2

};

enum RETURN build_extension_folder_hashmap();
char* get_folder(char* ext);
void organize(char* path);