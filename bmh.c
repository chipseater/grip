#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h> 
#include "dynarray.h"

#define TABLE_SIZE 256

bool compare_str(char* str1, char* str2, int size) {
  for (int i = 0; i < size; i++) {
    if (str1[i] != str2[i]) return false;
  }
  return true;
}

bool compare_str_no_case(char* str1, char* str2, int size) {
  for (int i = 0; i < size; i++) {
    if (tolower(str1[i]) != tolower(str2[i])) return false;
  }
  return true;
}

void make_skip_table(char table[TABLE_SIZE], char* pattern, int pattern_size) {
  for (int i = 0; i < TABLE_SIZE; i++) {
    table[i] = pattern_size;
  }
  for (int i = pattern_size - 1; i > 0; i--) {
    table[(int)pattern[pattern_size - i - 1]] = i;
  }
}

int find_pattern_bmh(char table[TABLE_SIZE],
                      char* pattern,
                      int pattern_size,
                      char* input_text,
                      int input_text_size,
                      bool is_case_sensitive) {
  int offset = 0;
  while (input_text_size - offset > pattern_size) {
    if ((!is_case_sensitive
      && compare_str_no_case(input_text + offset, pattern, pattern_size))
      || (is_case_sensitive
      && compare_str(input_text + offset, pattern, pattern_size)))
      return offset;
    if (!is_case_sensitive && compare_str_no_case(input_text + offset, pattern, pattern_size))
      return offset;
    offset += table[(int)input_text[offset + pattern_size - 1]];
  }
  return -1;
}

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
