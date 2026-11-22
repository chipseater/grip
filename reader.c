#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include "vector.h"
#include "mem_utils.h"
#include "reader.h"

struct Reader {
  vector* file_buf;
  int file;
};

typedef struct Reader reader;

// if filename is NULL, read standard input
reader* init_reader(char* filename) {
  reader* new_reader = malloc(sizeof(reader));
  NULL_BUFFER_HANDLING(new_reader);
  new_reader->file_buf = vect_new_with_capa(char, 4096);
  if (filename == NULL) {
    new_reader->file = STDIN_FILENO;
    return new_reader;
  }
  new_reader->file = open(filename, O_RDONLY, "rb");
  if (new_reader->file < 0) {
    fprintf(stderr, "%s: %s\n", filename, strerror(errno));
    exit(4);
  }
  return new_reader;
}

vector* read_file(reader* r) {
  int count = read(r->file,
                   (char*)r->file_buf->items,
                   r->file_buf->capacity);
  if (count > 0) r->file_buf->length += count;
  while (count > 0) {
    if (r->file_buf->length >= r->file_buf->capacity)
      vect_resize(r->file_buf);
    count = read(r->file,
                 r->file_buf->items + r->file_buf->length,
                 r->file_buf->capacity - r->file_buf->length);
    if (count > 0) r->file_buf->length += count;
  }
  return r->file_buf;
}

void free_reader(reader* r) {
  vect_free(r->file_buf);
  close(r->file);
  free(r);
}
