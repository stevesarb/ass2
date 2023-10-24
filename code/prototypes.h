#ifndef PROTOTYPES_H
#define PROTOTYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

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

// free memory functions
void free_movie_list(struct Movie*);
void free_languages(struct Language*);

#endif