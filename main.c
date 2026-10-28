#include <stdio.h>
#include <stdlib.h>
#include "reader.h"


int main(int argc, char** argv) {
  if (argc != 3) {
    fprintf(stderr, "%s: The grip command needs 2 arguments, a filename and a pattern to look for\n", argv[0]);
    exit(1);
  }
  char* filename = argv[1];
  char* pattern = argv[2];
  reader* r = init_reader(filename);
  read_file(r);
  printf("%s\n", r->buffer);
  free_reader(r);
  return 0;
}
