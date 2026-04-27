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

    bool use_config = false;
    //read config
    char* config_path = expand_config_path("~/.config/file-organizer/config.ini");
    if(access(config_path, F_OK | R_OK) == 0)
      {       
	if(read_config_file(config_path) != SUCCESS)
	  {
	    fprintf(stderr,"failed to read config! fallback to defaults...");
	  }
	else use_config = true;
      }
    else
      {
	//can't access file
	fprintf(stderr,"failed to read config! fallback to defaults...");
      }

    char* path = argv[1];
    // build the extension to folder hashmap
    RETURN ret = use_config? build_extension_folder_hashmap_from_config():
      build_extension_folder_hashmap();

    if(use_config)
    {
    	free_config();
    }
    
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

    
    free_config();
    return EXIT_SUCCESS;
}
