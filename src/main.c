#include <string.h>
#include <libgen.h>
#include "include.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: ./file_organizer {Folder path to organize}\n");
        return EXIT_FAILURE;
    }

    bool use_config = false;
    char config_file_path[1024] = {0};
    char* resolved_path = NULL;

    // 1. Try directory where the executable lies
    char exe_path[1024];
    ssize_t len = readlink("/proc/self/exe", exe_path, sizeof(exe_path) - 1);
    if (len != -1) {
        exe_path[len] = '\0';
        char* dir = dirname(exe_path);
        snprintf(config_file_path, sizeof(config_file_path), "%s/config.ini", dir);
        
        if (access(config_file_path, F_OK | R_OK) == 0) {
            resolved_path = config_file_path;
        }
    }

    // 2. Fall back to expansion of ~/.config path
    char* home_config = NULL;
    if (!resolved_path) {
        home_config = expand_config_path("~/.config/file-organizer/config.ini");
        if (home_config && access(home_config, F_OK | R_OK) == 0) {
            strncpy(config_file_path, home_config, sizeof(config_file_path) - 1);
            resolved_path = config_file_path;
        }
    }

    if (resolved_path) {
        printf("Loading configuration from: %s\n", resolved_path);
        if (read_config_file(resolved_path) == SUCCESS) {
            use_config = true;
        } else {
            fprintf(stderr, "Failed to parse config file! Falling back to defaults...\n");
        }
    } else {
        fprintf(stderr, "No config file found. Using built-in defaults.\n");
    }

    if (home_config) {
        free(home_config);
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
