#ifndef SV
#define SV
struct StringView {
  char* data;
  size_t length;
};

typedef struct StringView sv;

sv* sv_new(char* string, size_t length);
void sv_print(sv* stringview);
sv* sv_capture_line(vector* text, size_t index);
#endif
