#ifndef PROTOTYPES_H
#define PROTOTYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>

// for displaying top rated movie for each year
struct Movies_By_Distinct_Year {
    struct Movie* mov;
    struct Movies_By_Distinct_Year* next_year;
};

struct Language {
    char* lang;
    struct Language* next;
};

struct Movie {
    char* title;
    int year;
    struct Language* langs_head;
    double rating;
    struct Movie* next;
    struct Movie* same_year_next;
};

// process file functions
struct Movie* process_file(char*);
struct Movie* create_movie(char*);
struct Language* process_languages(char*);
struct Language* create_language(char*);

// helpers
int get_initial_choice();
int get_file_choice();
char* get_file_path();
char* select_files_to_process();
int check_file_path(char*);

// search for files
char* find_largest_file();
char* find_smallest_file();

// output movies by year functions
struct Movies_By_Distinct_Year* organize_movies_by_year(struct Movie*);
void check_for_same_year(struct Movie*, struct Movies_By_Distinct_Year*);
void add_same_year_movie(struct Movie*, struct Movie*);
void print_same_year_movies(struct Movie*);
void output_movies(struct Movies_By_Distinct_Year*);
char* make_dir_name();
char* make_file_name(char*, int);
void create_files(struct Movies_By_Distinct_Year*, char*);
void write_movies_to_file(int, struct Movie*);

// free memory functions
void free_movie_list(struct Movie*);
void free_languages(struct Language*);
void free_distinct_year_list(struct Movies_By_Distinct_Year*);

#endif