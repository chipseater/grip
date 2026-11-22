#ifndef READER
#define READER
#include "vector.h"

typedef struct Reader reader;

reader* init_reader(char* filename);
vector* read_file(reader* r);
void free_reader(reader* r);
#endif
