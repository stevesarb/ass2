#ifndef PROTOTYPES_H
#define PROTOTYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

// helpers
int get_initial_choice();
int get_file_choice();
char* get_file_path();
void select_files_to_process();
int check_file_path(char*);

// search for files
char* find_largest_file();
char* find_smallest_file();

#endif