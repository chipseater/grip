#ifndef BHL
#define BHL
#include "dynarray.h"
#include <stdbool.h>
#define TABLE_SIZE 256

void make_skip_table(char table[], char* pattern, int pattern_size);
vector* find_pattern_bmh_offsets(char table[TABLE_SIZE],
                                  vector* pattern,
                                  vector* input_text,
                                  bool is_case_sensitive) {
#endif
