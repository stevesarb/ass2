#include "prototypes.h"

char* find_largest_file() {
    char* file_path = NULL;



    return file_path;
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

