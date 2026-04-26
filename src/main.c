
#include <string.h>
#include "include.h"


int main(int argc , char** argv) {
    if(argc == 1){
      fprintf(stderr,"Target Folder Path not Provided\n");
        return EXIT_FAILURE;
    }
    if(argc != 2){
      fprintf(stderr,"Usage ./organize {Folder path to organize}\n");
        return EXIT_FAILURE;
    }
    char* path = argv[1];
    // build the extension to folder hashmap
    RETURN ret = build_extension_folder_hashmap();
    switch(ret){
    case SUCCESS :
      fprintf(stderr,"HashMap Build Success\n");
      break;
    case FAIL:
      fprintf(stderr,"Failure While building HashMap\n");
      return EXIT_FAILURE;
    case SOMETHING_WRONG:
      fprintf(stderr,"Something is wrong with hash format / config file\n");
      return EXIT_FAILURE;
    default:
      fprintf(stderr,"Unknown Return Code\n");
      return EXIT_FAILURE;
    }
    // pick every file and move it into respective folders
    organize(path);
    return EXIT_SUCCESS;
}
