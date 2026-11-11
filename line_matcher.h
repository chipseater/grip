#ifndef REV_LINE_MATCHER
#define REV_LINE_MATCHER
#include <dynarray.h>

typedef struct matchSpan {
  int begin;
  int end;
} matchspan;

matchspan* reverse_line_matcher(int index, char* text, int text_len, int* prev_begin);
intDynArray* make_occurence_list(intDynArray* indexes, char* text, int text_len);
void color_text(char* output_buffer, int output_len, char* text, int text_len, int begin, int end);
#endif
