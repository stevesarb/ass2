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
    while (curr_distinct != NULL) {
        print_same_year_movies(curr_distinct->mov);
        curr_distinct = curr_distinct->next_year;
    }

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