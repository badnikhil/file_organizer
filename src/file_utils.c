#include "include.h"

char* get_extension(const char *filename) {
    char *dot = strrchr(filename, '.');

    // no dot OR hidden file like ".bashrc"
    if (!dot || dot == filename) {
        return NULL;
    }

    char *ext = dot + 1;

    // convert to lowercase 
    for (int i = 0; ext[i]; i++) {
        if (ext[i] >= 'A' && ext[i] <= 'Z')
            ext[i] += 32;
    }

    return ext;
}

void organize(char* path) {
    struct dirent* entry;

    // Open Directory 
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    // Iterate the Directory
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Get the Full Path of File
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        struct stat st;
        if (stat(full_path, &st) == 0 && S_ISDIR(st.st_mode)) {
            printf("Skipped But Found %s\n", entry->d_name);
            continue;
        }

        char* ext = get_extension(entry->d_name);
        char* folder = get_folder(ext);

        if (!folder || !ext) {
            printf("Could not Find Folder for this Extension, Skipping for now\n");
            continue;
        }

        // get folder path
        char folder_path[1024];
        snprintf(folder_path, sizeof(folder_path), "%s/%s", path, folder);

        // create the folder if it does not exist
        mkdir(folder_path, 0755);

        char new_path[1024];
        int len = snprintf(new_path, sizeof(new_path), "%s/%s",
                           folder_path, entry->d_name);

        if (len < 0 || len >= sizeof(new_path)) {
            fprintf(stderr, "Path too long, skipping: %s\n", entry->d_name);
            continue;
        }

        if (rename(full_path, new_path) == 0) {
            printf("%s -> %s\n", entry->d_name, new_path);
        } else {
            perror("Renaming/Moving");
        }
    }

    closedir(dir);
}
