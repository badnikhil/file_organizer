#include <string.h>
#include "include.h"


int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: ./file_organizer {Folder path to organize}\n");
        return EXIT_FAILURE;
    }

    bool use_config = false;
    char* config_path = expand_config_path("~/.config/file-organizer/config.ini");

    if (access(config_path, F_OK | R_OK) == 0) {
        if (read_config_file(config_path) != SUCCESS) {
            fprintf(stderr, "failed to read config! fallback to defaults...");
        } else {
            use_config = true;
        }
    } else {
        fprintf(stderr, "failed to read config! fallback to defaults...");
    }

    char* path = argv[1];

    RETURN ret = use_config ? build_extension_folder_hashmap_from_config() : 
                              build_extension_folder_hashmap();

    switch (ret) {
        case SUCCESS:
            fprintf(stderr, "HashMap Build Success\n");
            break;
        case FAIL:
            fprintf(stderr, "Failure While building HashMap\n");
            return EXIT_FAILURE;
        case SOMETHING_WRONG:
            fprintf(stderr, "Something is wrong with hash format / config file\n");
            return EXIT_FAILURE;
        default:
            fprintf(stderr, "Unknown Return Code\n");
            return EXIT_FAILURE;
    }

    // pick every file and move it into respective folders
    organize(path);

    if (use_config) {
        free_config();
    }

    return EXIT_SUCCESS;
}
