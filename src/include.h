#ifndef INCLUDE_H
#define INCLUDE_H
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stddef.h>
#include <ctype.h>
#include"uthash.h"

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

extern struct Mapping defaults[];
extern size_t defaults_size;

extern enum RETURN build_extension_folder_hashmap();
extern char* get_folder(char* ext);
extern void organize(char* path);
#endif
