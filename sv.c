#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "string.h"
#include "vector.h"
#include "mem_utils.h"
#include "sv.h"

sv* sv_new(char* string, size_t length) {
  sv* new_sv = malloc(sizeof(sv));
  NULL_BUFFER_HANDLING(new_sv);
  new_sv->data = string;
  new_sv->length = length;
  return new_sv;
}

void sv_print(sv* stringview) {
  printf("%.*s", (int)stringview->length, stringview->data);
}

sv* sv_capture_line(vector* text, size_t index) {
  size_t begin = index;
  size_t end = index;
  // Scan for the beginning of the line
  while (begin > 0) {
    if (text->items[begin - 1] == '\n') break;
    begin--;
  }
  // Scan for the end of the line
  while (end < text->length) {
    if (text->items[end + 1] == '\n') break;
    end++;
  }
  return sv_new((char*)text->items + begin, begin - end);
}
