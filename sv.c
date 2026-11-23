#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <ctype.h> 
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
  printf("%.*s\n", (int)stringview->length, stringview->data);
}

sv* sv_capture_line(vector* text, size_t index) {
  size_t begin = index;
  size_t end = index;
  // Scan for the beginning of the line
  while (begin > 0) {
    if (text->items[--begin] == '\n') break;
  }
  // Scan for the end of the line
  while (end < text->length) {
    if (text->items[++end] == '\n') break;
  }
  return sv_new((char*)text->items + begin, end - begin);
}

bool sv_compare_deep(sv* sv1, sv* sv2) {
  if (sv1->length != sv2->length) return false;
  for (size_t i = 0; i < sv1->length; i++) {
    if (sv1->data[i] != sv2->data[i]) return false;
  }
  return true;
}

bool sv_compare_deep_no_case(sv* sv1, sv* sv2) {
  if (sv1->length != sv2->length) return false;
  for (size_t i = 0; i < sv1->length; i++) {
    if (tolower(sv1->data[i]) != tolower(sv2->data[i])) return false;
  }
  return true;
}

bool sv_compare_shallow(sv* sv1, sv* sv2) {
  return sv1->length == sv2->length && sv1->data == sv2->data;
}
