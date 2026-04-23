
#include <string.h>
#include "include.h"
#include <dirent.h>
void organize(char* path){
   struct dirent* entry;
   DIR *dir = opendir(path);
   if(dir == NULL){
    perror("opendir");
    return;
   }
   while((entry = readdir(dir)) != NULL){
    printf("Found %s\n",entry->d_name);
   }




   closedir(dir);
}
int main(int argc , char** argv) {
    if(argc == 1){
        printf("Target Folder Path not Provided\n");
        return EXIT_FAILURE;
    }
    if(argc != 2){
        printf("Usage ./organize {Folder path to organize}\n");
        return EXIT_FAILURE;
    }
    char* path = argv[1];
    // build the extension to folder hashmap
    enum RETURN ret = build_extension_folder_hashmap();
    switch(ret){
        case SUCCESS : printf("Success\n");break;
        case FAIL : printf("Failure While building HashMap\n");return EXIT_FAILURE;
        case SOMETHING_WRONG: printf("Something is wrong with hash format / config file\n");return EXIT_FAILURE;
        default: printf("Unknown Return Code\n");return EXIT_FAILURE;
    }
    // pick every file and move it into respective folders
    organize(path);
    return EXIT_SUCCESS;
}