#ifndef SV
#define SV
#include <stdbool.h>

struct StringView {
  char* data;
  size_t length;
};

typedef struct StringView sv;

sv* sv_new(char* string, size_t length);
void sv_print(sv* stringview);
sv* sv_capture_line(vector* text, size_t index);
bool sv_compare_deep(sv* sv1, sv* sv2);
bool sv_compare_deep_no_case(sv* sv1, sv* sv2);
bool sv_compare_shallow(sv* sv1, sv* sv2);
#endif
