#ifndef BHL
#define BHL
#include "dynarray.h"
#include <stdbool.h>
#define TABLE_SIZE 256

void make_skip_table(char table[], char* pattern, int pattern_size);
int find_pattern_bmh(char table[TABLE_SIZE],
                     char* pattern,
                     int pattern_size,
                     char* input_text,
                     int input_text_size,
                     bool is_case_sensitive);
intDynArray* find_all_patterns(char table[TABLE_SIZE],
                                char* pattern,
                                int pattern_size,
                                char* input_text,
                                int input_text_size,
                                bool is_case_sensitive);
#endif
