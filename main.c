#include "prototypes.h"


int main() {
    int init_choice = 0;
    FILE* file = NULL;

    do {
        init_choice = get_initial_choice();
        if (init_choice == 2)
            break;
        
        select_files_to_process();
    }
    while (init_choice == 1);


    return 0;
}