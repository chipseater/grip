#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mem_utils.h"

struct IntDynArray {
  int* buffer;
  size_t length;
  size_t capacity;
};

typedef struct IntDynArray intDynArray;

intDynArray* new_intDynArray(void) {
  intDynArray* new_dynArray = malloc(sizeof(intDynArray));
  NULL_BUFFER_HANDLING(new_dynArray);
  new_dynArray->length = 0;
  new_dynArray->capacity = 256;
  new_dynArray->buffer = malloc(new_dynArray->capacity * sizeof(int));
  NULL_BUFFER_HANDLING(new_dynArray->buffer);
  return new_dynArray;
}

void resize_intDynArray(intDynArray* array) {
  array->capacity *= 2;
  int* new_memory = realloc(array->buffer, array->capacity * sizeof(int));
  NULL_BUFFER_HANDLING(new_memory);
  array->buffer = new_memory;

}

void push_to_intDynArray(intDynArray* array, int element) {
  if (array->capacity <= array->length)
    resize_intDynArray(array);
  array->buffer[array->length++] = element;
}

int pop_intDynArray(intDynArray* array) {
  if (array->length > 0)
    return array->buffer[--array->length];
  fprintf(stderr, "Popping an empty array, exiting\n");
  exit(5);
}

void print_intDynArray(intDynArray* array) {
  printf("[");
  if (array->length > 0)
    printf("%d", array->buffer[0]);
  for (size_t i = 1; i < array->length; i++) {
    printf("; %d", array->buffer[i]);
  }
  printf("]\n");
}

void free_intDynArray(intDynArray* array) {
  free(array->buffer);
  free(array);
}
