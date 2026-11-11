#ifndef PTR_DYNARRAY
#define PTR_DYNARRAY
#include <stdint.h>

typedef struct Vector {
  uint8_t* items;
  size_t item_size;
  size_t length;
  size_t capacity;
} vector;

vector* new_vector(size_t item_size);
void resize_vector(vector* arr);
void push_to_vector(vector* arr, void* element);
void print_vector(const vector* arr, void print_fn(const void*), char sep);
void free_vector_with_items(vector* arr, void item_free(void*));
void free_vector(vector* arr);

#define vector_init(TYPE) new_vector(sizeof((TYPE)))
#endif
