#include <stdio.h>
#include <stdlib.h>
#include "mem_utils.h"
#include "ptr_dynarray.h"

ptr_dynarray* new_ptr_dynarray(size_t item_size) {
  ptr_dynarray* new_dynarray = malloc(sizeof(ptr_dynarray));
  NULL_BUFFER_HANDLING(new_dynarray);
  new_dynarray->length = 0;
  new_dynarray->capacity = 256;
  new_dynarray->item_size = item_size;
  new_dynarray->items = malloc(new_dynarray->capacity * item_size);
  NULL_BUFFER_HANDLING(new_dynarray->items);
  return new_dynarray;
}

void resize_ptr_dynarray(ptr_dynarray* arr) {
  if (arr->capacity > 0) {
    arr->capacity *= 2;
  } else {
    arr->capacity = 1;
  }
  void* reallocated = realloc(arr->items, arr->capacity * arr->item_size);
  NULL_BUFFER_HANDLING(reallocated);
  arr->items = reallocated;
}

uint_8* get_target_address(ptr_dynarray* arr, size_t index) {
  return arr->items + arr->item_size * index;
}

void push_to_ptr_dynarray(ptr_dynarray* arr, void* element) {
  if (arr->capacity <= arr->length)
    resize_ptr_dynarray(arr);
  size_t target_address = arr->size + arr;
  arr->items[arr->length++] = element;
}

void print_ptr_dynarray(const ptr_dynarray* arr, void print_fn(const void*), char sep) {
  if (arr->length == 0) {
    printf("∅\n");
    return;
  }
  print_fn(arr->items[0]);
  for (size_t i = 1; i < arr->length; i++) {
    printf("%c", sep);
    print_fn(arr->items[i]);
  }
  printf("\n");
}

void free_ptr_dynarray_with_items(ptr_dynarray* arr, void item_free(void*)) {
  if (!arr) return;
  if (item_free) {
    for (size_t i = 0; i < arr->length; i++) {
      item_free(arr->items[i]);
    }
  }
  free(arr->items);
  free(arr);
}

void free_ptr_dynarray(ptr_dynarray* arr) {
  free_ptr_dynarray_with_items(arr, NULL);
}
