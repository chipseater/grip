#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "vector.h"
#include "mem_utils.h"

// Functions prefixed by _ are wrapped in a macro located in vector.h

vector* _vect_new_with_capa(size_t item_size, size_t capa) {
  vector* new_dynarray = malloc(sizeof(vector));
  NULL_BUFFER_HANDLING(new_dynarray);
  new_dynarray->length = 0;
  new_dynarray->capacity = capa;
  new_dynarray->item_size = item_size;
  new_dynarray->items = malloc(new_dynarray->capacity * item_size);
  NULL_BUFFER_HANDLING(new_dynarray->items);
  return new_dynarray;
}

vector* _vect_new(size_t item_size) {
  return _vect_new_with_capa(item_size, 8);
}

vector* string_to_vect(char* string) {
  if (string == NULL) return NULL;
  vector* vect = malloc(sizeof(vector));
  NULL_BUFFER_HANDLING(vect);
  vect->items = (uint8_t*)strdup(string);
  NULL_BUFFER_HANDLING(vect->items);
  vect->length = strlen(string);
  vect->item_size = sizeof(char);
  vect->capacity = vect->length + 1; // Accounting for the \0 at the end
  return vect;
}

// Returns a heap allocated string from the vector
char* vect_to_string(vector* vect) {
  char* recipient = malloc(sizeof(char) * (vect->length + 1));
  memcpy(recipient, vect->items, vect->length);
  recipient[vect->length] = '\0';
  return recipient;
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

void _vect_pop(vector* arr, void* element) {
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

/* Used to debug vector.c
void print_char(char str) {
  printf("%c", str);
}

#define T char

int main(void) {
  vector* arr = string_to_vect("abcd");
  vect_print(T, arr, print_char, "");
  char* str = vect_to_string(arr);
  printf("%s\n", str);
  free(str);
  vect_free(arr);
  return 0;
}
*/
