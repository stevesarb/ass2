#include "prototypes.h"

void select_files_to_process() {
    int file_choice = 0;
    char* file_path = NULL;
    FILE* file = NULL;
    do {
        file_choice = get_file_choice();

        switch (file_choice) {
            case 1:
                file_path = find_largest_file();
                break;
            case 2:
                file_path = find_smallest_file();
                break;
            case 3:
                file_path = get_file_path();
                break;
            default:
                break;
        }
        file = fopen(file_path, "r");
        if (file == NULL)
            printf("Could not locate or open the file %s\n", file_path);
    }
    while (file == NULL);

    printf("Now processing the file: %s\n", file_path);
}

int get_initial_choice() {
    printf("\nWhat would you like to do?\n");
    printf("1. Select a file to process\n");
    printf("2. Exit the program\n");

    char* line = NULL;
    size_t len = 0;
    ssize_t line_size = 0;
    int choice = 0;

    do {
        printf("\nEnter a choice 1 or 2: ");
        line_size = getline(&line, &len, stdin);
        choice = atoi(line);
        if (choice != 1 && choice != 2) {
            printf("Invalid input, try again:\n");
        }
    }
    while (choice != 1 && choice != 2);

    free(line);
    
    return choice;
}

int get_file_choice() {
    printf("\nWhich file would you like to process?\n");
    printf("1. Process largest file\n");
    printf("2. Process smallest file\n");
    printf("3. Specify name of file to process\n");

    char* line = NULL;
    size_t len = 0;
    ssize_t line_size = 0;
    int choice = 0;

    do {
        printf("\nEnter a choice 1-3: ");
        line_size = getline(&line, &len, stdin);
        choice = atoi(line);
        if (choice < 1 || choice > 3) {
            printf("Invalid input, try again:\n");
        }
    }
    while (choice < 1 || choice > 3);

    free(line);
    
    return choice;
}

char* get_file_path() {
    printf("\nEnter the complete filename: ");

    char* line = NULL;
    size_t len = 0;
    ssize_t line_size = getline(&line, &len, stdin);

    char* file_path = (char*)calloc(strlen(line), sizeof(char));
    strncpy(file_path, line, line_size - 1); // eliminates the newline char

    free(line);

    return file_path;
}

int check_file_path(char* file_path) {
    char* file_prefix = "movies_";
    char* file_suffix = ".csv";
    char* last_4_chars = NULL;

    int len = strlen(file_path);

    if (len < 11)
        return 0;

    if (len >= 4)
        last_4_chars = &file_path[len - 4];
    else 
        return 0;

    int prefix_ret = strncmp(file_path, file_prefix, 7);
    int suffix_ret = strcmp(last_4_chars, file_suffix);

    if (prefix_ret == 0 && suffix_ret == 0)
        return 1;
    return 0;
}