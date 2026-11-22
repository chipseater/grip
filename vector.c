#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "vector.h"
#include "mem_utils.h"

vector* _vect_new(size_t item_size) {
  vector* new_dynarray = malloc(sizeof(vector));
  NULL_BUFFER_HANDLING(new_dynarray);
  new_dynarray->length = 0;
  new_dynarray->capacity = 8;
  new_dynarray->item_size = item_size;
  new_dynarray->items = malloc(new_dynarray->capacity * item_size);
  NULL_BUFFER_HANDLING(new_dynarray->items);
  return new_dynarray;
}

static void vect_resize(vector* arr) {
  if (arr->capacity > 0) {
    arr->capacity *= 2;
  } else {
    arr->capacity = 1;
  }
  uint8_t* reallocated = realloc(arr->items, arr->capacity * arr->item_size);
  NULL_BUFFER_HANDLING(reallocated);
  arr->items = reallocated;
}

static uint8_t* get_target_address(vector* arr, size_t index) {
  return arr->items + arr->item_size * index;
}

void _vect_at(vector* arr, size_t i, void* recipient) {
  memcpy(recipient, get_target_address(arr, i), arr->item_size);
}

void vect_set(vector* arr, size_t i, void* element) {
  memcpy(get_target_address(arr, i), element, arr->item_size);
}

void _vect_push(vector* arr, void* element) {
  if (arr->capacity <= arr->length)
    vect_resize(arr);
  vect_set(arr, arr->length, element);
  arr->length++;
}

void vect_free_with_items(vector* arr, void item_free(void*)) {
  if (!arr) return;
  if (item_free) {
    for (size_t i = 0; i < arr->length; i++) {
      item_free(get_target_address(arr, i));
    }
  }
  free(arr->items);
  free(arr);
}

void vect_free(vector* arr) {
  vect_free_with_items(arr, NULL);
}

void print_int(int i) {
  printf("%d", i);
}

#define T int

int main(void) {
  vector* arr = vect_new(T);
  vect_push(T, arr, 1);
  vect_push(T, arr, 2);
  vect_push(T, arr, 3);
  vect_push(T, arr, 4);
  vect_push(T, arr, 5);
  vect_print(T, arr, print_int, "");
  vect_free(arr);
  return 0;
}
