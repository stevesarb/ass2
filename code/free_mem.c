#include "prototypes.h"

void free_movie_list(struct Movie* node) {
    if (node->next != NULL) {
        free_movie_list(node->next);
    }
    free(node->title);
    free_languages(node->langs_head);
    free(node);
}

void free_languages(struct Language* node) {
    if (node->next != NULL) {
        free_languages(node->next);
    }
    free(node->lang);
    free(node);
}