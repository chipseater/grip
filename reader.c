#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

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
  if (new_reader == NULL) {
    perror("Allocation error");
    exit(1);
  }
  new_reader->length = 0;
  new_reader->capacity = 16;
  new_reader->filename = filename;
  new_reader->file = open(filename, O_RDONLY, "r");
  if (new_reader->file < 0) {
    fprintf(stderr, "%s: %s\n", filename, strerror(errno));
    exit(1);
  }
  char* new_buffer = malloc(new_reader->capacity * sizeof(char));
  if (new_buffer == NULL) {
    perror("Allocation error");
    exit(1);
  }
  new_reader->buffer = new_buffer;
  return new_reader;
}

void resize_buffer(reader* r) {
  r->capacity *= 2;
  char* new_buffer = malloc(r->capacity);
  memcpy(new_buffer, r->buffer, r->capacity);
  r->buffer = new_buffer;
}

void read_file(reader* r) {
  int count = read(r->file, r->buffer, r->capacity);
  int offset = 0;
  while (count == r->capacity) {
    offset += count;
    resize_buffer(r);
    count = read(r->file, r->buffer+offset, r->capacity);
  }
}

void free_reader(reader* r) {
  free(r->buffer);
  close(r->file);
  free(r);
}
