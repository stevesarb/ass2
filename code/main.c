#include "prototypes.h"


int main() {
    int init_choice = 0;
    char* file_path = NULL;
    struct Movie* head = NULL;

    do {
        init_choice = get_initial_choice();
        if (init_choice == 2)
            break;
        
        file_path = select_files_to_process();

        printf("Now processing the file: %s\n", file_path);
        head = process_file(file_path);

    
        free_movie_list(head);
    }
    while (init_choice == 1);


    return 0;
}