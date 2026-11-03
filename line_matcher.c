#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynarray.h"

#define ANSI_RED   "\033[01;31m"
#define ANSI_RESET "\x1b[0m"

struct MatchLine {
  char* line;
  int begin;
  int end;
};

void free_match(struct MatchLine* match) {
  free(match->line);
  free(match);
}

// It returns the line that contains the index-th character of text
struct MatchLine* reverse_line_matcher(int index, char* text, int text_len) {
  int line_begin = index;
  int line_end = index;
  while (line_begin > 0 && text[line_begin - 1] != '\n') line_begin--;
  while (line_end < text_len - 1 && text[line_begin + 1] != '\n') line_end++;
  int line_len = line_end - line_begin;
  // Make line allocations long enough to be able to insert whatever I want inside
  char* line = malloc(3 * (line_len + 1));
  memcpy(line, text + line_begin, line_len);
  line[line_len] = '\0';
  struct MatchLine* match = malloc(sizeof(*match));
  match->line = line;
  match->begin = line_begin;
  match->end = line_end;
  return match;
}

void print_lines_from_indexes(intDynArray* indexes,
                              int pattern_len, char* text, int text_len) {
  for (int i = 0; i < indexes->length; i++) {
    int begin_index = indexes->buffer[i];
    struct MatchLine* match = reverse_line_matcher(begin_index, text, text_len);
    char* line = match->line;
    printf("%.*s" ANSI_RED "%.*s" ANSI_RESET "%s\n",
      begin_index - match->begin, line,
      pattern_len, line + begin_index - match->begin,
      line + begin_index + pattern_len - match->begin
    );
    free_match(match);
  }
}
