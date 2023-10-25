#include "prototypes.h"

struct Movies_By_Distinct_Year* organize_movies_by_year(struct Movie* mov_head) {
    // initialize linked list to use to keep track of pointers that correspond to the top rated movie of each year
    struct Movies_By_Distinct_Year* head = malloc(sizeof(struct Movies_By_Distinct_Year));
    struct Movies_By_Distinct_Year* curr_distinct = head;
    head->mov = mov_head;
    head->next_year = NULL;
    struct Movie* curr = mov_head->next;

    while (curr != NULL) {
        // check if curr (current movie in movie list) has the same year a movie pointed to by any node in years linked list
        check_for_same_year(curr, head);
        curr = curr->next;
    }

    // print Movies by distinct year list
    // while (curr_distinct != NULL) {
    //     print_same_year_movies(curr_distinct->mov);
    //     curr_distinct = curr_distinct->next_year;
    // }

    // free movies by distinct year list
    // free_distinct_year_list(head);

    return head;
}

void print_same_year_movies(struct Movie* node) {
    if (node != NULL) {
        printf("%d %0.1f %s\n", node->year, node->rating, node->title);
        print_same_year_movies(node->same_year_next);
    }
}

void check_for_same_year(struct Movie* curr, struct Movies_By_Distinct_Year* node) {
    int has_year = 0;
    struct Movies_By_Distinct_Year* last = node;

    // iterate through the whole list of movies by distict year
    while (node != NULL) {
        // if there is already a movie of the same year in the list
        if (curr->year == node->mov->year) {
            has_year = 1;

            // traverse the linked list of same_year_movies
            // once I reach the end, set that node's same_year_next ptr to the curr Movie
            add_same_year_movie(curr, node->mov);
        }
        // advance pointers
        if (node->next_year != NULL)
            last = node->next_year;
        node = node->next_year;
    }

    if (has_year == 0) {
        // add new node to list and have it point to the current movie
        last->next_year = malloc(sizeof(struct Movies_By_Distinct_Year));
        last = last->next_year;
        last->mov = curr;
        last->next_year = NULL;
    }
}

// curr is the Movie to be added to the same year list, mov is the movie already in the same year list
void add_same_year_movie(struct Movie* curr, struct Movie* mov) {
    if (mov->same_year_next == NULL) {
        mov->same_year_next = curr;
    }
    else {
        add_same_year_movie(curr, mov->same_year_next);
    }
}

void output_movies(struct Movies_By_Distinct_Year* head) {
    // create random number in range 0-99999 and append it to string
    // char dir_name[24];
    // memset(dir_name, '\0', 24);
    // strcat(dir_name, "./sarbers.movies.");
    // char rand_num_str[7];
    // memset(rand_num_str, '\0', 7); 
    // int rand_num = rand() % 1000000;
    // sprintf(rand_num_str, "%d", rand_num); // writes rand_num to rand_num_str
    // strcat(dir_name, rand_num_str);

    char* dir_name = make_dir_name();

    // make directory and set perms to rwxr-x---
    mkdir(dir_name, 0750);

    // for each year, create a new file and add movies from that year to it
    create_files(head, dir_name);

    // char file_path[33];
    // memset(file_path, '\0', 33);
    // strcat(file_path, dir_name);
    // strcat(file_path, "/0000.txt");
    // int file_descriptor = open(file_path, O_WRONLY | O_CREAT, 0640);
}

char* make_dir_name() {
    char* dir_name = calloc(24, sizeof(char));
    memset(dir_name, '\0', 24);
    strcat(dir_name, "./sarbers.movies.");

    // random number
    char rand_num_str[7];
    memset(rand_num_str, '\0', 7); 
    int rand_num = rand() % 1000000;
    sprintf(rand_num_str, "%d", rand_num); // writes rand_num to rand_num_str
    strcat(dir_name, rand_num_str);

    return dir_name;
}

char* make_file_name(char* dir_name, int year) {
    char* file_path = calloc(33, sizeof(char));
    memset(file_path, '\0', 33);
    strcat(file_path, dir_name);
    strcat(file_path, "/");

    char year_str[10];
    memset(year_str, '\0', 10);
    sprintf(year_str, "%d", year);
    strcat(year_str, ".txt");
    strcat(file_path, year_str);

    return file_path;
}

void create_files(struct Movies_By_Distinct_Year* node, char* dir_name) {
    int file_descriptor;
    char* file_path = NULL;
    ssize_t nwritten;
    if (node != NULL) {
        // create the name of the file
        file_path = make_file_name(dir_name, node->mov->year);

        // create the file for current year and set perms
        file_descriptor = open(file_path, O_WRONLY | O_CREAT, 0640);

        // write each movie of that year to the file
        write_movies_to_file(file_descriptor, node->mov);
        // nwritten = write(file_descriptor, node->title, strlen(node->title) * sizeof(char));
        // nwritten = write(file_descriptor, "\n", 1);

        // recursively move to the next year in list
        create_files(node->next_year, dir_name);

        free(file_path);
    }
}

void write_movies_to_file(int file_descriptor, struct Movie* node) {
    ssize_t nwritten;
    if (node != NULL) {
        nwritten = write(file_descriptor, node->title, strlen(node->title) * sizeof(char));
        nwritten = write(file_descriptor, "\n", 1);
        write_movies_to_file(file_descriptor, node->same_year_next);
    }
}