#ifndef MEM_UTILS
#define MEM_UTILS
#include <stdlib.h>
#include <stdio.h>

#define NULL_BUFFER_HANDLING(BUFFER) do { \
  if ((BUFFER) == NULL) { \
    perror("Allocation error"); \
    exit(EXIT_FAILURE); \
  } \
} while (0)
#endif
