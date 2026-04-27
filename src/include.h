#ifndef INCLUDE_H
#define INCLUDE_H

// Must be defined before any system headers to expose POSIX extensions
#ifndef _WIN32
    #define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #include <windows.h>
    #include <io.h>       // _access
    #include <direct.h>   // _mkdir
    #include <dirent.h>   // MinGW provides this
    #include <sys/stat.h>
    #define mkdir(p, m) _mkdir(p)
    #define access      _access
    #define PATH_SEP    '\\'
    #define ACCESS_OK   0
    typedef int ssize_t;
#else
    #include <unistd.h>
    #include <dirent.h>
    #include <sys/stat.h>
    #define PATH_SEP    '/'
    #define ACCESS_OK   (F_OK | R_OK)
#endif

#include "uthash.h"

typedef char bool;
#define true  1
#define false 0

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

extern RETURN read_config_file(const char*path);
extern void free_config(void);
#endif
