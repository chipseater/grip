#ifndef READER
#define READER

struct Reader {
  int length;
  int capacity;
  char* filename;
  char* buffer;
  int file;
};

typedef struct Reader reader;

reader* init_reader(char* pattern);
void read_file(reader* r);
void free_reader(reader* r);
void resize_buffer(reader* r);
#endif
