#ifndef VECTOR
#define VECTOR
#include <stdint.h>

typedef struct Vector {
  uint8_t* items;
  size_t item_size;
  size_t capacity;
  size_t length;
} vector;

vector* vect_new(size_t item_size);
void vect_get(vector* arr, size_t i, void* recipient);
void vect_print(vector* arr, void print_fn(uint8_t), char sep);
void vect_free_with_items(vector* arr, void item_free(void*));
void vect_free(vector* arr);

#define vect_create(type) vect_new(sizeof(type))

#endif
