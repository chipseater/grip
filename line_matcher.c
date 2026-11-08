#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynarray.h"
#include "mem_utils.h"

#define ANSI_RED   "\033[01;31m"
#define ANSI_RESET "\x1b[0m"


struct MatchLine {
  int begin;
  int end;
};

// It returns the line that contains the index-th character of text
struct MatchLine* reverse_line_matcher(int index, char* text, int text_len, int* prev_begin) {
  int line_begin = index;
  int line_end = index;
  while (line_begin > 0 && text[line_begin - 1] != '\n') line_begin--;
  while (line_end < text_len - 1 && text[line_begin + 1] != '\n') line_end++;
  // Returns NULL if the previous match is on the same line as the current one
  if (*prev_begin == line_begin) return NULL;
  *prev_begin = line_begin;
  struct MatchLine* match = malloc(sizeof(*match));
  NULL_BUFFER_HANDLING(match);
  match->begin = line_begin;
  match->end = line_end;
  return match;
}

void color_text(char* output_buffer, int output_len, char* text,
                int text_len, int begin, int end) {
  printf("Before: %s", output_buffer);
  snprintf(output_buffer, output_len, "%.*s" ANSI_RED "%.*s" ANSI_RESET "%.*s\n",
    begin, text,
    end - begin, text + begin,
    text_len - end, text + end
  );
  printf("After: %s", output_buffer);
}

void print_lines_from_indexes(intDynArray* indexes,
                              int pattern_len, char* text, int text_len) {
  int prev_begin = -1;
  for (int i = 0; i < indexes->length; i++) {
    int begin_index = indexes->buffer[i];
    struct MatchLine* match = reverse_line_matcher(begin_index, text, text_len, &prev_begin);
    if (!match) return;
    printf("%.*s\n", match->end - match->begin, text + match->begin);
  }
}
