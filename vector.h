#ifndef VECTOR
#define VECTOR
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <assert.h>

typedef struct Vector {
  uint8_t* items;
  size_t item_size;
  size_t capacity;
  size_t length;
} vector;

vector* _vect_new(size_t item_size);
void _vect_at(vector* arr, size_t i, void* recipient);
void _vect_push(vector* arr, void* element);
void vect_set(vector* arr, size_t i, void* element);
void vect_free_with_items(vector* arr, void item_free(void*));
void vect_free(vector* arr);

#define vect_new(type) _vect_new(sizeof(type))

#define vect_at(type, arr, i) ({ \
  size_t _i = i; \
  assert(_i < arr->length); \
  type _recipient; \
  _vect_at(arr, _i, &_recipient); \
  _recipient; \
})

#define vect_print(type, arr, print_fn, sep) do { \
  if ((arr)->length != 0) { \
    print_fn(vect_at(type, (arr), 0)); \
    for (size_t i = 1; i < (arr)->length; i++) { \
      printf("%s", sep); \
      print_fn(vect_at(type, (arr), i)); \
    } \
    printf("\n"); \
  } else { \
    printf("∅\n"); \
  } \
} while (0)

#define vect_push(type, arr, el) ({ \
    type _el = el; \
    _vect_push(arr, (void*)&_el); \
})
#endif
