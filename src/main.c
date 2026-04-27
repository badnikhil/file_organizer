#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <stdlib.h>
#include "include.h"

int main(int argc, char** argv) {
    char* custom_config_path = NULL;
    char* path = NULL;

    // Manual argument parsing
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
            custom_config_path = argv[++i];
        } else {
            path = argv[i];
        }
    }

    if (!path) {
        fprintf(stderr, "Usage: %s [-c config_path] <directory>\n", argv[0]);
        return EXIT_FAILURE;
    }
    bool use_config = false;
    char config_file_path[1024] = {0};
    char* resolved_path = NULL;

    // 1. Prioritize custom path if provided
    if (custom_config_path) {
        if (access(custom_config_path, F_OK | R_OK) == 0) {
            resolved_path = custom_config_path;
        } else {
            fprintf(stderr, "Error: Custom config file not found or not readable: %s\n", custom_config_path);
            return EXIT_FAILURE;
        }
    } else {
        // 2. Try directory where the executable lies
        char exe_path[1024];
        ssize_t len = readlink("/proc/self/exe", exe_path, sizeof(exe_path) - 1);
        if (len != -1) {
            exe_path[len] = '\0';
            
            // Manual dirname implementation
            char *last_slash = strrchr(exe_path, '/');
            if (last_slash) {
                *last_slash = '\0'; // Truncate at last slash to get directory
            }
            
            snprintf(config_file_path, sizeof(config_file_path), "%s/config.ini", exe_path);
            
            if (access(config_file_path, F_OK | R_OK) == 0) {
                resolved_path = config_file_path;
            }
        }

        // 3. Fall back to ~/.config/file-organizer/config.ini
        if (!resolved_path) {
            const char* home = getenv("HOME");
            if (home) {
                snprintf(config_file_path, sizeof(config_file_path), "%s/.config/file-organizer/config.ini", home);
                if (access(config_file_path, F_OK | R_OK) == 0) {
                    resolved_path = config_file_path;
                }
            }
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
