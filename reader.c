#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include "mem_utils.h"

#define BUFFER_INIT_CAPA 4096

struct Reader {
  int length;
  int capacity;
  char* filename;
  char* buffer;
  int file;
};

typedef struct Reader reader;

reader* init_reader(char* filename) {
  reader* new_reader = malloc(sizeof(reader));
  NULL_BUFFER_HANDLING(new_reader);
  new_reader->length = 0;
  new_reader->capacity = BUFFER_INIT_CAPA;
  new_reader->filename = filename;
  new_reader->file = open(filename, O_RDONLY, "rb");
  if (new_reader->file < 0) {
    fprintf(stderr, "%s: %s\n", filename, strerror(errno));
    exit(4);
  }
  char* new_buffer = malloc(new_reader->capacity * sizeof(char));
  NULL_BUFFER_HANDLING(new_buffer);
  new_reader->buffer = new_buffer;
  return new_reader;
}

reader* init_reader_stdin() {
  reader* new_reader = malloc(sizeof(reader));
  NULL_BUFFER_HANDLING(new_reader);
  new_reader->length = 0;
  new_reader->capacity = BUFFER_INIT_CAPA;
  new_reader->filename = NULL;
  new_reader->file = STDIN_FILENO;
  char* new_buffer = malloc(new_reader->capacity * sizeof(char));
  NULL_BUFFER_HANDLING(new_buffer);
  new_reader->buffer = new_buffer;
  return new_reader;
}

void resize_buffer(reader* r) {
  r->capacity *= 2;
  char* status = realloc(r->buffer, r->capacity * sizeof(char));
  NULL_BUFFER_HANDLING(status);
}

void read_file(reader* r) {
  int count = read(r->file, r->buffer, r->capacity);
  while (r->length >= r->capacity) {
    resize_buffer(r);
    r->length += count;
    count = read(r->file, r->buffer + r->length, r->capacity);
  }
  r->length += count;
}

void free_reader(reader* r) {
  free(r->buffer);
  close(r->file);
  free(r);
}
