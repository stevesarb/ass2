#include "prototypes.h"

char* find_largest_file() {
    char* file_path = NULL;
    DIR *dp;
    struct dirent *ep;
    struct stat sb;
    off_t max_file_size = 0;
    int valid_file = 0;
    char* lrgst_file = NULL;

    dp = opendir ("./");
    if (dp == NULL) {
        perror("Couldn't open current directory\n");
        return file_path;
    }

    // read every directory entry
    while (ep = readdir(dp)) {
        file_path = ep->d_name;
        valid_file = check_file_path(file_path);
        if (valid_file == 1) {
            // call stat() to check the size of the file
            if (stat(file_path, &sb) == -1) {
                perror("error with stat()\n");
                return NULL;
            }
            // check to see if current file is the largest one seen so far
            if (sb.st_size > max_file_size) {
                max_file_size = sb.st_size;
                lrgst_file = calloc(strlen(file_path) + 1, sizeof(char));
                strcpy(lrgst_file, file_path);
            }    
        }    
    }
      
    (void)closedir(dp);
    
    return lrgst_file;
}

char* find_smallest_file() {
    char* file_path = NULL;
    DIR *dp;
    struct dirent *ep;
    struct stat sb;
    off_t min_file_size = 2147483647; // max value off_t data type can hold
    int valid_file = 0;
    char* smlst_file = NULL;

    dp = opendir ("./");
    if (dp == NULL) {
        perror("Couldn't open current directory\n");
        return file_path;
    }

    // read every directory entry
    while (ep = readdir(dp)) {
        file_path = ep->d_name;
        valid_file = check_file_path(file_path);
        if (valid_file == 1) {
            // call stat() function on current file to check it's size
            if (stat(file_path, &sb) == -1) {
                perror("error with stat()\n");
                return NULL;
            }
            // check size
            if (sb.st_size < min_file_size) {
                min_file_size = sb.st_size;
                if (smlst_file != NULL) {
                    free(smlst_file);
                    smlst_file = NULL;
                }
                smlst_file = calloc(strlen(file_path) + 1, sizeof(char));
                strcpy(smlst_file, file_path);
            }    
        }
    }
      
    (void)closedir(dp);
    
    return smlst_file;
}
