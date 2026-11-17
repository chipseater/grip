#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "vector.h"
#include "mem_utils.h"

vector* vect_new(size_t item_size) {
  vector* new_dynarray = malloc(sizeof(vector));
  NULL_BUFFER_HANDLING(new_dynarray);
  new_dynarray->length = 0;
  new_dynarray->capacity = 256;
  new_dynarray->item_size = item_size;
  new_dynarray->items = malloc(new_dynarray->capacity * item_size);
  NULL_BUFFER_HANDLING(new_dynarray->items);
  return new_dynarray;
}

void vect_resize(vector* arr) {
  if (arr->capacity > 0) {
    arr->capacity *= 2;
  } else {
    arr->capacity = 1;
  }
  uint8_t* reallocated = realloc(arr->items, arr->capacity * arr->item_size);
  NULL_BUFFER_HANDLING(reallocated);
  arr->items = reallocated;
}

uint8_t* get_target_address(vector* arr, size_t index) {
  return arr->items + arr->item_size * index;
}

uint8_t vect_get(vector* arr, size_t i) {
  return *(get_target_address(arr, i));
}

void vect_set(vector* arr, size_t i, uint8_t element) {
  uint8_t* temp_buf = malloc(arr->item_size);
  *temp_buf = element;
  memcpy(get_target_address(arr, i), temp_buf, arr->item_size);
  free(temp_buf);
}

void vect_push(vector* arr, uint8_t element) {
  if (arr->capacity <= arr->length)
    vect_resize(arr);
  vect_set(arr, arr->length, element);
  arr->length++;
}

void vect_print(vector* arr, void print_fn(uint8_t), char sep) {
  if (arr->length == 0) {
    printf("∅\n");
    return;
  }
  print_fn(vect_get(arr, 0));
  for (size_t i = 1; i < arr->length; i++) {
    printf("%c", sep);
    print_fn(vect_get(arr, i));
  }
  printf("\n");
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

int main(void) {
  vector* arr = vect_new(sizeof(char*));
  vect_push(arr, (uint8_t)"string");
  vect_free(arr);
  return 0;
}
