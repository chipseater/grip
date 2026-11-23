#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "sv.h"
#include "vector.h"

#define TABLE_SIZE 256

void make_skip_table(char table[TABLE_SIZE], vector* pattern) {
  for (int i = 0; i < TABLE_SIZE; i++) {
    table[i] = pattern_size;
  }
  for (int i = pattern_size - 1; i > 0; i--) {
    table[(int)vect_at(pattern_size - i - 1)] = i;
  }
}

vector* find_pattern_bmh_offsets(char table[TABLE_SIZE],
                                  vector* pattern,
                                  vector* input_text,
                                  bool is_case_sensitive) {
  vector* offset_vect = vect_new(size_t);
  size_t pattern_size = pattern->length;
  size_t offset = 0;
  sv* pattern_sv = sv_new(pattern->data, pattern_size);
  sv* input_text_sv = sv_new(input_text->data, pattern_size);
  while (input_text->length - offset > pattern_size) {
    if (is_case_sensitive
        && sv_compare_deep(pattern_sv, input_text_sv))
        || !is_case_sensitive
        && sv_compare_deep_no_case(pattern_sv, input_text_sv))
      vect_push(size_t, offset_vect, offset);
    char table_entry = vect_at(char, input_text, offset + pattern_size - 1);
    pattern_sv->data += table[(size_t)table_entry];
    offset += table[(size_t)table_entry];
  }
  free(pattern_sv);
  free(input_text_sv);
  return offset_vect;
}

/*
intDynArray* find_all_patterns(char table[TABLE_SIZE],
                                char* pattern,
                                int pattern_size,
                                char* input_text,
                                int input_text_size,
                                bool is_case_sensitive) {
  intDynArray* occurences = new_intDynArray();
  int occurence = find_pattern_bmh(table, pattern, pattern_size,
    input_text, input_text_size, is_case_sensitive);
  int offset = 0;
  while (occurence >= 0) {
    push_to_intDynArray(occurences, occurence + offset);
    offset += occurence + pattern_size;
    occurence = find_pattern_bmh(
      table, pattern, pattern_size, input_text + offset,
      input_text_size - offset, is_case_sensitive);
  }
  return occurences;
}
*/
