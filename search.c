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

    while (ep = readdir(dp)) {
        file_path = ep->d_name;
        valid_file = check_file_path(file_path);
        if (valid_file == 1) {
            if (stat(file_path, &sb) == -1) {
                perror("error with stat()\n");
                return NULL;
            }
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
    
}

// FILE* find_specific_file() {
//     printf("\nEnter the complete filename: ");

//     char* line = NULL;
//     size_t len = 0;
//     ssize_t line_size = getline(&line, &len, stdin);

//     char* file_path = (char*)calloc(strlen(line), sizeof(char));
//     strncpy(file_path, line, line_size - 1); // eliminates the newline char

//     FILE* file = fopen(file_path, "r");

//     if (file == NULL) {
//         printf("Unable to locate the file %s. Try again\n", file_path);
//     }

//     free(line);
//     free(file_path);

//     return file;
// }

