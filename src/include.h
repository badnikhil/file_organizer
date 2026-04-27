#ifndef INCLUDE_H
#define INCLUDE_H
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stddef.h>
#include <stdbool.h>
#include <wordexp.h>
#include <unistd.h>
#include <ctype.h>
#include"uthash.h"

struct Mapping {
    char ext[10];       // key
    char folder[20];    // value
    UT_hash_handle hh;
};

struct Config {
  char dir[64]; //key
  char* exts[20]; //value
  UT_hash_handle hh;
};


typedef enum{
    SUCCESS = 0,
    FAIL = 1,
    SOMETHING_WRONG = 2

} RETURN;

extern struct Mapping defaults[];
extern size_t defaults_size;

extern struct Config* config;
extern size_t config_size;

extern RETURN build_extension_folder_hashmap();
extern RETURN build_extension_folder_hashmap_from_config();
extern char* get_folder(char* ext);
extern void organize(char* path);

extern char* expand_config_path(const char* path);
extern RETURN read_config_file(const char*path);
extern void free_config(void);
#endif
